#pragma once

#include "common.hpp"

#include "font.hpp"
#include "resourcemanager.hpp"

namespace graphics {
class fontfactory {
public:
  fontfactory() = delete;
  fontfactory(const std::shared_ptr<framework::resourcemanager> _resourcemanager);
  ~fontfactory() = default;

  std::shared_ptr<font> get(const std::string &face);

  // void update(double_t delta);

  // void draw() const;

private:
  std::shared_ptr<framework::resourcemanager> _resourcemanager;

  // std::map<uint8_t, glyph> _glyphs;
  // std::shared_ptr<pixmap> _pixmap;
};
}
