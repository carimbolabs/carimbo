#pragma once

#include "common.hpp"

#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "vector2d.hpp"

namespace framework {
struct keyframe {
  geometry::rect frame;
  uint64_t duration;

  keyframe() = default;
  keyframe(const geometry::rect &rect, uint64_t duration) : frame(rect), duration(duration) {}
};

struct entityprops {
public:
  uint64_t id;
  std::string kind;
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> animations;
  geometry::point position;
  geometry::point pivot;
  float_t angle;
  double_t scale;
  graphics::flip flip;
  uint8_t alpha;
  bool gravitic;
  std::string action;
  uint32_t frame;
  uint32_t last_frame;
  vector2d velocity;

  entityprops() = default;
};
}
