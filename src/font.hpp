#pragma once

#include "common.hpp"
#include "point.hpp"

namespace graphics {
using glyphmap = std::map<uint8_t, geometry::rect>;

class font {
public:
  font() = default;
  font(const glyphmap &glyphs, std::shared_ptr<pixmap> pixmap);
  ~font() = default;

  void draw(const std::string &text, const geometry::point &position) const noexcept;

private:
  glyphmap _glyphs;
  std::shared_ptr<pixmap> _pixmap;
};
}
