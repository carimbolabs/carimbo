#pragma once

#include "common.hpp"

namespace graphics {
class pixmappool {
public:
  explicit pixmappool(const std::shared_ptr<renderer> &renderer) noexcept;
  ~pixmappool() noexcept = default;

  void preload(const std::vector<std::string> &filenames) noexcept(false);

  const std::shared_ptr<pixmap> get(const std::string &filename) noexcept(false);

  void flush() noexcept;

private:
  std::shared_ptr<renderer> _renderer;
  std::map<std::string, std::shared_ptr<pixmap>> _pool;
};
}
