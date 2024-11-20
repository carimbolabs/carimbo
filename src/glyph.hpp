#pragma once

#include "common.hpp"

namespace graphics {
class glyph {
public:
  explicit glyph(const geometry::rect &rect) noexcept;

  void draw() const noexcept;

private:
  uint32_t _code{0};
  geometry::rect _rect{};
  double_t _angle{0.0f};
};
}
