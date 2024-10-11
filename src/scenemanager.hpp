#pragma once

#include "common.hpp"
#include "pixmap.hpp"
#include "pixmappool.hpp"
#include "rect.hpp"

namespace framework {
class scenemanager {
public:
  scenemanager(const std::shared_ptr<graphics::pixmappool> pixmappool);

  void load(const std::string_view name);

  void update(double_t delta);

  void draw();

private:
  std::shared_ptr<graphics::pixmappool> _pixmappool;
  std::shared_ptr<graphics::pixmap> _background;
  geometry::size _size;
};
}
