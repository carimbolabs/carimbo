#pragma once

#include "common.hpp"

namespace graphics {
class glyphprops {
public:
  glyphprops() noexcept = default;
  explicit glyphprops(const geometry::rect &rect, const color &color, double_t angle = 0.0f) noexcept
      : _rect(rect), _color(color), _angle(angle) {}

  geometry::rect _rect;
  color _color;
  double_t _angle{0.0f};
};
}
