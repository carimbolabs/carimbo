#pragma once

#include "common.hpp"

#include "pixmap.hpp"
#include "point.hpp"

namespace framework {
struct entityprops {
  std::string id;
  std::shared_ptr<graphics::pixmap> pixmap;
  geometry::point point;
  double_t angle;
  graphics::flip flip;
  uint8_t alpha;
};
}
