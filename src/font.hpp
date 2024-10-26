#pragma once

#include "common.hpp"

namespace graphics {
class font {
public:
  font() = default;
  ~font() = default;

private:
  std::map<uint8_t, glyph> _glyphs;
  std::shared_ptr<pixmap> _pixmap;
};
}
