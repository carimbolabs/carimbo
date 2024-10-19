#pragma once

#include "common.hpp"

#include "glyphprops.hpp"

namespace graphics {
class glyph {
public:
  // void update(double_t delta);

  void draw(const glyphprops &props) const;

private:
  uint32_t _code;
};
}
