#pragma once

#include "common.hpp"
#include "glyphprops.hpp"

namespace graphics {
class glyph {
public:
  explicit glyph(uint32_t code) noexcept;

  void draw(const glyphprops &props) const noexcept;

private:
  uint32_t _code{0};
};
}
