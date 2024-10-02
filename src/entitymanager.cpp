#include "entitymanager.hpp"

#include "entity.hpp"
#include "entityprops.hpp"
#include "io.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "size.hpp"
#include <cstdint>
#include <string_view>
#include <vector>

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

  std::map<std::string, std::vector<keyframe>> animations;
  for (const auto &[key, a] : j["animations"].get<json::object_t>()) {
    std::vector<keyframe> keyframes;
    keyframes.reserve(a.size());

    for (const auto &frame_list : a) {
      for (const auto &f : frame_list) {
        geometry::point position{f.at("x").get<int32_t>(), f.at("y").get<int32_t>()};
        geometry::size size{f.at("width").get<int32_t>(), f.at("height").get<int32_t>()};
        geometry::rect rect{position, size};
        uint64_t duration = f.at("duration").get<uint64_t>();

        keyframes.emplace_back(rect, duration);
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
  std::string action{"idle"};
  uint32_t frame{0};
  uint32_t last_frame{0};

  entityprops props{
      id,
      kind,
      spritesheet,
      animations,
      position,
      pivot,
      angle,
      scale,
      flip,
      alpha,
      gravitic,
      action,
      frame,
      last_frame};

  const auto e = entity::create(std::move(props));
  std::cout << "[entitymanager] spawn: " << e->id() << std::endl;
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(const std::shared_ptr<entity> entity) {
  _entities.remove(entity);
}

std::shared_ptr<entity> entitymanager::find(uint64_t id) const {
  const auto it = std::find_if(_entities.begin(), _entities.end(),
                               [id](const std::shared_ptr<entity> &entity) {
                                 return entity->id() == id;
                               });

  return (it != _entities.end()) ? *it : nullptr;
}

void entitymanager::update() {
  for (auto entity : _entities) {
    entity->update();
  }
}

void entitymanager::draw() {
  for (auto entity : _entities) {
    entity->draw();
  }
}
