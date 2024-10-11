#include "entitymanager.hpp"

#include "entity.hpp"
#include "entityprops.hpp"
#include "io.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "size.hpp"
#include "vector2d.hpp"

using namespace framework;

using json = nlohmann::json;

void entitymanager::set_resourcemanager(
    std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].template get<std::string_view>());
  const auto gravitic = j.value("gravitic", false);
  const auto scale = j.value("scale", 1.);
  const auto size = geometry::size{
      static_cast<int32_t>(j.value("width", 0) * scale),
      static_cast<int32_t>(j.value("height", 0) * scale)};

  std::map<std::string, std::vector<keyframe>> animations;
  for (const auto &[key, a] : j["animations"].get<json::object_t>()) {
    std::vector<keyframe> keyframes;
    keyframes.reserve(a.size());

    for (const auto &frame_list : a) {
      for (const auto &f : frame_list) {
        const auto position = geometry::point{f.at("x").get<int32_t>(), f.at("y").get<int32_t>()};
        const auto size = geometry::size{f.at("width").get<int32_t>(), f.at("height").get<int32_t>()};
        const auto rect = geometry::rect{position, size};
        const auto duration = f.at("duration").get<uint64_t>();
        const auto singleshoot = f.value("singleshoot", false);
        auto offset = geometry::point{0, 0};
        const auto o = f.value("offset", json::object());
        if (o.contains("x") || o.contains("y")) {
          offset = geometry::point{o.value("x", 0), o.value("y", 0)};
        }

        keyframes.emplace_back(rect, duration, singleshoot, offset);
      }
    }

    animations.emplace(key, std::move(keyframes));
  }

  const auto id = _counter++;
  geometry::point position;
  geometry::point pivot;
  float_t angle{.0f};
  graphics::flip flip = graphics::flip::none;
  uint8_t alpha{255};
  std::string action;
  uint32_t frame{0};
  uint32_t last_frame{0};
  vector2d velocity;
  bool visible{true};

  entityprops props{
      id,
      kind,
      spritesheet,
      animations,
      position,
      pivot,
      size,
      angle,
      scale,
      flip,
      alpha,
      gravitic,
      action,
      frame,
      last_frame,
      velocity,
      visible};

  const auto e = entity::create(std::move(props));
  std::cout << "[entitymanager] spawn: " << e->id() << std::endl;
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(const std::weak_ptr<entity> entity) {
  if (auto e = entity.lock()) {
    _entities.remove(e);
  }
}

std::shared_ptr<entity> entitymanager::find(uint64_t id) const {
  const auto it = std::find_if(_entities.begin(), _entities.end(),
                               [id](const std::shared_ptr<entity> &entity) {
                                 return entity->id() == id;
                               });

  return (it != _entities.end()) ? *it : nullptr;
}

void entitymanager::update(double delta) {
  for (auto entity : _entities) {
    entity->update(delta);
  }

  for (auto a : _entities) {
    // if (!a->collidable) continue;

    for (auto b : _entities) {
      if (a == b /* || !entityB->collidable */) continue;

      if (a->colliding_with(*b)) {
        // TODO send position of collision

        // if (!a->_props.velocity.zero() && b->_props.velocity.zero()) {
        //   std::cout << "Entity " << a->kind() << " initiated collision with Entity " << b->kind() << std::endl;
        // } else if (!b->_props.velocity.zero() && a->_props.velocity.zero()) {
        //   std::cout << "Entity " << b->kind() << " initiated collision with Entity " << a->kind() << std::endl;
        // } else {
        //   std::cout << "Entity " << a->kind() << " and Entity " << b->kind() << " are colliding (both in motion)." << std::endl;
        // }
      }
    }
  }
}

void entitymanager::draw() {
  for (auto entity : _entities) {
    entity->draw();
  }
}

void entitymanager::on_mail(const input::mailevent &event) {
  if (const auto entity = find(event.to); entity) {
    entity->dispatch(event.body);
  }
}
