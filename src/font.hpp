#pragma once

#include "common.hpp"

namespace graphics {
using glyphmap = std::map<uint8_t, geometry::rect>;

class font {
public:
  font(const glyphmap &glyphs, std::shared_ptr<pixmap> pixmap);
  ~font() = default;

  void draw(std::string_view text) const noexcept;

private:
  glyphmap _glyphs;
  std::shared_ptr<pixmap> _pixmap;
};
}
