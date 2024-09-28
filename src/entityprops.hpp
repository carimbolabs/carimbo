#pragma once

#include "common.hpp"

#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"

namespace framework {
struct keyframe {
  geometry::rect frame;
  uint64_t duration;

  keyframe() = default;
};

struct entityprops {
public:
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> frames;
  geometry::point position;
  geometry::point pivot;
  float_t angle;
  graphics::flip flip;
  uint8_t alpha;
  std::string_view id;

  entityprops() = default;
};
}
