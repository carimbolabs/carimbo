#pragma once

#include "common.hpp"
#include "flip.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"
#include <chipmunk/chipmunk.h>
#include <cstdint>

namespace framework {

using body_ptr = std::unique_ptr<cpBody, void (*)(cpBody *)>;

using shape_ptr = std::unique_ptr<cpShape, void (*)(cpShape *)>;

enum bodytype : int8_t {
  stationary = 0,
  dynamic = 1,
  kinematic = 2,
};

NLOHMANN_JSON_SERIALIZE_ENUM(bodytype, {{stationary, "stationary"}, {dynamic, "dynamic"}, {kinematic, "kinematic"}})

enum collisiontype : uint8_t {
  player = 1,
  enemy = 2,
  playerbullet = 3,
  enemybullet = 4,
  wall = 5
};

struct collision {
  collisiontype type;
  std::optional<std::string> from;
};

void from_json(const nlohmann::json &j, collision &c);

struct keyframe {
  geometry::rect frame;
  geometry::point offset;
  uint64_t duration{};
  bool singleshoot{};

  keyframe() noexcept = default;
  keyframe(const geometry::rect &rect, uint64_t duration, bool singleshoot, const geometry::point &offset) noexcept
      : frame(rect), offset(offset), duration(duration), singleshoot(singleshoot) {}
};

struct entityprops {
  uint64_t id{};
  uint32_t frame{};
  uint32_t last_frame{};
  double_t angle{};
  uint8_t alpha{255};
  bool visible{true};
  geometry::point position{};
  geometry::point pivot{};
  geometry::size size{};
  std::string kind{};
  std::string action{};
  graphics::flip flip{graphics::flip::none};
  std::shared_ptr<graphics::pixmap> spritesheet{};
  std::map<std::string, std::vector<keyframe>> animations{};
  body_ptr body{nullptr, [](cpBody *) {}};
  shape_ptr shape{nullptr, [](cpShape *) {}};

  entityprops(const entityprops &) = delete;
  entityprops &operator=(const entityprops &) = delete;
  entityprops(entityprops &&) noexcept = default;
  entityprops &operator=(entityprops &&) noexcept = default;
};

}
