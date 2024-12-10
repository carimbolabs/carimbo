#include "entitymanager.hpp"

using namespace framework;

using json = nlohmann::json;

entitymanager::entitymanager(std::shared_ptr<world> world, std::shared_ptr<resourcemanager> resourcemanager) noexcept
    : _world(std::move(world)),
      _resourcemanager(std::move(resourcemanager)) {}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);

  auto spritesheet = j.contains("spritesheet")
                         ? _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string_view>())
                         : nullptr;

  const auto size = j["size"].get<geometry::size>();

  std::map<std::string, std::vector<keyframe>> animations;
  for (const auto &[key, frames] : j["animations"].items()) {
    std::vector<keyframe> keyframes;
    for (const auto &frame : frames) {
      for (const auto &f : frame) {
        keyframes.emplace_back(
            f["rect"].get<geometry::rect>(),
            f["duration"].get<uint64_t>(),
            f.value("singleshoot", false),
            j.value("offset", geometry::point{})
        );
      }
    }
    animations.emplace(key, std::move(keyframes));
  }

  const auto resized = size.resized();
  cpVect vertices[] = {
      cpv(0, 0),
      cpv(resized.width(), 0),
      cpv(resized.width(), resized.height()),
      cpv(0, resized.height())
  };

  const auto type = j["physics"]["type"].get<bodytype>();

  body_ptr body{nullptr, cpBodyFree};
  switch (type) {
  case bodytype::stationary:
    body = body_ptr(cpBodyNewStatic(), cpBodyFree);
    break;
  case bodytype::kinematic:
    body = body_ptr(cpBodyNewKinematic(), cpBodyFree);
    break;
  case bodytype::dynamic:
    body = body_ptr(
        cpBodyNew(1.0, cpMomentForBox(1.0, size.width(), size.height())),
        cpBodyFree
    );
    break;
  }

  auto shape = shape_ptr(
      cpPolyShapeNew(body.get(), std::size(vertices), vertices, cpTransformIdentity, 0.0),
      cpShapeFree
  );

  const auto &physics = j["physics"];
  cpShapeSetCollisionType(shape.get(), physics["collision"].get<collision>().type);
  cpShapeSetFriction(shape.get(), physics.value("friction", 0.5f));
  cpShapeSetElasticity(shape.get(), physics.value("elasticity", 0.3f));

  cpSpaceAddShape(_world->space().get(), shape.get());
  cpSpaceAddBody(_world->space().get(), body.get());

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

  auto e = entity::create(std::move(props));
  std::cout << "[entitymanager] spawn " << e->id() << " kind " << kind << std::endl;
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(const std::shared_ptr<entity> entity) noexcept {
  if (!entity) {
    return;
  }

  auto &props = entity->props();

  if (props.body) {
    cpSpaceRemoveBody(_world->space().get(), props.body.get());
    props.body.reset();
  }

  if (props.shape) {
    cpSpaceRemoveShape(_world->space().get(), props.shape.get());
    props.shape.reset();
  }

  _entities.remove(entity);
}

std::shared_ptr<entity> entitymanager::find(uint64_t id) const noexcept {
  auto it = std::ranges::find_if(_entities, [id](const auto &entity) {
    return entity->id() == id;
  });

  return (it != _entities.end()) ? *it : nullptr;
}

void entitymanager::update(float_t delta) noexcept {
  for (const auto &entity : _entities) {
    entity->update(delta);
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
