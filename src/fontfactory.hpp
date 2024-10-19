#pragma once

#include "common.hpp"

#include "font.hpp"
#include "resourcemanager.hpp"

namespace graphics {
class fontfactory {
public:
  fontfactory() = delete;
  fontfactory(const std::weak_ptr<framework::resourcemanager> _resourcemanager);
  ~fontfactory() = default;

  std::shared_ptr<font> get(const std::string &filename, const std::string &alphabet);

  // void update(double_t delta);

  // void draw() const;

private:
  std::weak_ptr<framework::resourcemanager> _resourcemanager;

  // std::map<uint8_t, glyph> _glyphs;
  // std::shared_ptr<pixmap> _pixmap;
};
}
