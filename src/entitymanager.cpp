#include "entitymanager.hpp"

#include "entity.hpp"
#include "entityprops.hpp"
#include "io.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "size.hpp"
#include "vector2d.hpp"

using namespace framework;
using json = nlohmann::json;

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept {
  _resourcemanager = std::move(resourcemanager);
}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string>());
  const auto gravitic = j.value("gravitic", false);
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
      gravitic,
      "",
      0,
      SDL_GetTicks(),
      {},
      true
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
  for (const auto &entity : _entities) {
    entity->update(delta);
  }

  for (auto itA = _entities.begin(); itA != _entities.end(); ++itA) {
    for (auto itB = std::next(itA); itB != _entities.end(); ++itB) {
      if ((*itA)->colliding_with(**itB)) {
        // Placeholder for collision handling logic
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
