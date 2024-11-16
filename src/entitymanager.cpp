#include "entitymanager.hpp"

#include "entity.hpp"
#include "entityprops.hpp"
#include "io.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "size.hpp"

using namespace framework;

using json = nlohmann::json;

entitymanager::entitymanager(std::shared_ptr<world> world)
    : _world(world) {}

entitymanager::~entitymanager() {
}

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept {
  _resourcemanager = std::move(resourcemanager);
}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string>());

  const auto size = j["size"].get<geometry::size>();

  std::map<std::string, std::vector<keyframe>> animations;
  for (const auto &[key, frames] : j["animations"].items()) {
    std::vector<keyframe> keyframes;
    for (const auto &fl : frames) {
      for (const auto &f : fl) {
        const auto rect = f["rect"].get<geometry::rect>();
        const auto duration = f.at("duration").get<uint64_t>();
        const auto singleshoot = f.value("singleshoot", false);
        const auto offset = j.value("offset", geometry::point{});

        keyframes.emplace_back(rect, duration, singleshoot, offset);
      }
    }
    animations.emplace(key, std::move(keyframes));
  }

  body_ptr body{nullptr, cpBodyFree};
  shape_ptr shape{nullptr, cpShapeFree};
  const auto resized = size.resized();
  cpVect vertices[] = {
      cpv(0, 0),
      cpv(resized.width(), 0),
      cpv(resized.width(), resized.height()),
      cpv(0, resized.height())
  };

  const int n = sizeof(vertices) / sizeof(vertices[0]);

  std::unordered_map<bodytype, std::function<void()>> mapping = {
      {bodytype::stationary, [&]() {
         body = body_ptr(cpBodyNewStatic(), [](cpBody *body) { cpBodyFree(body); });
         shape = shape_ptr(cpPolyShapeNew(body.get(), n, vertices, cpTransformIdentity, 0.0), [](cpShape *shape) { cpShapeFree(shape); });
       }},
      {bodytype::kinematic, [&]() {
         body = body_ptr(cpBodyNewKinematic(), [](cpBody *body) { cpBodyFree(body); });
         shape = shape_ptr(cpPolyShapeNew(body.get(), n, vertices, cpTransformIdentity, 0.0), [](cpShape *shape) { cpShapeFree(shape); });
       }},
      {bodytype::dynamic, [&]() {
         body = body_ptr(cpBodyNew(1.0, cpMomentForBox(1.0, size.width(), size.height())), [](cpBody *body) { cpBodyFree(body); });
         shape = shape_ptr(cpPolyShapeNew(body.get(), n, vertices, cpTransformIdentity, 0.0), [](cpShape *shape) { cpShapeFree(shape); });
         cpShapeSetFriction(shape.get(), 0.7);
         cpShapeSetElasticity(shape.get(), 0.3);
         cpSpaceAddBody(_world->space().get(), body.get());
       }}
  };

  const auto p = j["physics"];

  mapping[p["type"].get<bodytype>()]();

  cpShapeSetFriction(shape.get(), p.value("friction", 0.5f));
  cpShapeSetElasticity(shape.get(), p.value("elasticity", 0.3f));
  cpSpaceAddShape(_world->space().get(), shape.get());

  entityprops props{
      _counter++,
      0,
      SDL_GetTicks(),
      0.0,
      255,
      true,
      {},
      {},
      size,
      kind,
      "",
      graphics::flip::none,
      std::move(spritesheet),
      std::move(animations),
      std::move(body),
      std::move(shape)
  };

  const auto e = entity::create(std::move(props));
  std::cout << "[entitymanager] spawn " << e->id() << " kind " << kind << std::endl;
  _entities.emplace_back(std::move(e));
  return e;
}

void entitymanager::destroy(const std::weak_ptr<entity> entity) noexcept {
  if (auto e = entity.lock()) {
    _entities.remove(e);
  }
}

std::shared_ptr<entity> entitymanager::find(uint64_t id) const noexcept {
  const auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::shared_ptr<entity> &entity) { return entity->id() == id; });
  return (it != _entities.end()) ? *it : nullptr;
}

void entitymanager::update(float_t delta) {
  UNUSED(delta);

  for (const auto &entity : _entities) {
    entity->update();
  }
}

void entitymanager::draw() noexcept {
  for (const auto &entity : _entities) {
    entity->draw();
  }
}

void entitymanager::on_mail(const input::mailevent &event) noexcept {
  if (const auto entity = find(event.to); entity) {
    entity->on_email(event.body);
  }
}
