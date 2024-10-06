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
  geometry::point offset;

  keyframe() = default;
  keyframe(const geometry::rect &rect, uint64_t duration, const geometry::point &offset)
      : frame(rect), duration(duration), offset(offset) {}
};

struct entityprops {
public:
  uint64_t id;
  std::string kind;
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> animations;
  geometry::point position;
  geometry::point pivot;
  geometry::size size;
  float_t angle;
  double_t scale;
  graphics::flip flip;
  uint8_t alpha;
  bool gravitic;
  std::string action;
  uint32_t frame;
  uint32_t last_frame;
  vector2d velocity;
  bool visible;

  entityprops() = default;
};
}
