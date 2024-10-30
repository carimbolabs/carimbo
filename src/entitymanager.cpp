#include "entitymanager.hpp"

#include "entity.hpp"
#include "entityprops.hpp"
#include "io.hpp"
#include "margin.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "size.hpp"

using namespace framework;

using json = nlohmann::json;

entitymanager::entitymanager() {
  auto def = b2DefaultWorldDef();
  def.gravity = {0.0f, -10.0f};

  _world = b2CreateWorld(&def);
}

entitymanager::~entitymanager() {
  b2DestroyWorld(_world);
}

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept {
  _resourcemanager = std::move(resourcemanager);
}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string>());
  const auto scale = j.value("scale", 1.0);
  const auto size = geometry::size{
      static_cast<int32_t>(j.value("width", 0) * scale),
      static_cast<int32_t>(j.value("height", 0) * scale)
  };

  std::map<std::string, std::vector<keyframe>> animations;
  for (const auto &[key, frames] : j["animations"].items()) {
    std::vector<keyframe> keyframes;
    for (const auto &frame_list : frames) {
      for (const auto &f : frame_list) {
        const auto rect = geometry::rect{
            {f.at("x").get<int32_t>(), f.at("y").get<int32_t>()},
            {f.at("width").get<int32_t>(), f.at("height").get<int32_t>()}
        };
        const auto duration = f.at("duration").get<uint64_t>();
        const auto singleshoot = f.value("singleshoot", false);
        const auto offset = geometry::point{f.value("offset", json::object()).value("x", 0), f.value("offset", json::object()).value("y", 0)};
        keyframes.emplace_back(rect, duration, singleshoot, offset);
      }
    }
    animations.emplace(key, std::move(keyframes));
  }

  /*
  "physics": {
    "dynamic": true,
    "margin": {
      "top": 0,
      "left": 0,
      "bottom": 0,
      "right": 0
    },
    "size": {
      "width": 32,
      "height": 32
    }
  }
  */

  static auto mapping = std::unordered_map<std::string_view, b2BodyType>{
      {"static", b2_staticBody},
      {"kinematic", b2_kinematicBody},
      {"dynamic", b2_dynamicBody},
  };

  const auto type = mapping[j["physics"]["type"].get<std::string>()];

  const auto margin = j["physics"]["margin"].get<geometry::margin>();
  // const auto top = .value("top", 0);
  // const auto left = j["physics"]["margin"].value("left", 0);
  // const auto top = j["physics"]["margin"].value("top", 0);
  // const auto top = j["physics"]["margin"].value("top", 0);

  auto bodyDef = b2DefaultBodyDef();
  bodyDef.position = {0.0f, -10.0f};
  bodyDef.type = type;

  const auto body = b2CreateBody(_world, &bodyDef);

  entityprops props{
      _counter++,
      kind,
      spritesheet,
      std::move(animations),
      {},
      {},
      size,
      0.0f,
      scale,
      graphics::flip::none,
      255,
      "",
      0,
      SDL_GetTicks(),
      {},
      true,
      body
  };

  const auto e = entity::create(std::move(props));
  std::cout << "[entitymanager] spawn: " << e->id() << std::endl;
  _entities.emplace_back(e);
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

void entitymanager::update(double_t delta) {
  b2World_Step(_world, delta, 1);

  for (const auto &entity : _entities) {
    entity->update(delta);
  }

  for (auto a = _entities.begin(); a != _entities.end(); ++a) {
    for (auto b = std::next(a); b != _entities.end(); ++b) {
      if ((*a)->colliding_with(**b)) {
      }
    }
  }
}

void entitymanager::draw() noexcept {
  for (const auto &entity : _entities) {
    entity->draw();
  }
}

void entitymanager::on_mail(const input::mailevent &event) noexcept {
  if (const auto entity = find(event.to); entity) {
    entity->dispatch(event.body);
  }
}
