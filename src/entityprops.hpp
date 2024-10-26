#pragma once

#include "common.hpp"
#include "flip.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"
#include "vector2d.hpp"

namespace framework {
struct keyframe {
  geometry::rect frame;
  uint64_t duration{};
  bool singleshoot{};
  geometry::point offset;

  keyframe() noexcept = default;
  keyframe(const geometry::rect &rect, uint64_t duration, bool singleshoot, const geometry::point &offset) noexcept
      : frame(rect), duration(duration), singleshoot(singleshoot), offset(offset) {}
};

struct entityprops {
  uint64_t id{};
  std::string kind;
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> animations;
  geometry::point position;
  geometry::point pivot;
  geometry::size size;
  float_t angle{};
  double_t scale{1.0};
  graphics::flip flip{graphics::flip::none};
  uint8_t alpha{255};
  bool gravitic{};
  std::string action;
  uint32_t frame{};
  uint32_t last_frame{};
  math::vector2d velocity;
  bool visible{true};

  entityprops() noexcept = default;
};
}
