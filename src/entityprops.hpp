#pragma once

#include "common.hpp"

namespace framework {
struct entityprops {
  std::unique_ptr<graphics::pixmap> spritesheet;
  geometry::rect frame;
  geometry::point position;
  geometry::point pivot;
  float_t angle;
  graphics::flip flip;
  uint8_t alpha;
  std::string_view id;
};
}
