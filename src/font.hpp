#pragma once

#include "common.hpp"

#include "glyph.hpp"
#include "pixmap.hpp"

namespace graphics {
class font {
  font() = delete;
  font(const std::shared_ptr<pixmappool> pixmappool, const std::string &filename, const std::string &alphabet);
  ~font() = default;

  // void update(double_t delta);

  // void draw() const;

private:
  std::map<uint8_t, glyph> _glyphs;
  std::shared_ptr<pixmap> _pixmap;
};
}
