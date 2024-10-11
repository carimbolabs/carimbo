#pragma once

#include "common.hpp"
#include "point.hpp"

namespace graphics {
class effect {
public:
  geometry::point point;
  uint32_t rows;
  std::vector<uint8_t> yuv;
};
}
