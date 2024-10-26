#pragma once

#include "common.hpp"
#include "size.hpp"

namespace framework {
class scenemanager {
public:
  scenemanager(std::shared_ptr<graphics::pixmappool> pixmappool) noexcept;

  void load(const std::string_view name);
  void update(double_t delta) noexcept;
  void draw() noexcept;

private:
  std::shared_ptr<graphics::pixmappool> _pixmappool;
  std::shared_ptr<graphics::pixmap> _background;
  geometry::size _size;
};
}
