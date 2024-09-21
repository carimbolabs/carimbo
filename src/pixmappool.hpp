#pragma once

#include "common.hpp"

namespace graphics {
class pixmappool {
public:
  explicit pixmappool(const std::shared_ptr<renderer> renderer);
  ~pixmappool() = default;

  void preload(const std::vector<std::string> &filenames);

  const std::shared_ptr<pixmap> get(const std::string &filename);

  void flush();

private:
  std::shared_ptr<renderer> _renderer;

  std::unordered_map<std::string, std::shared_ptr<pixmap>,
                     std::hash<std::string>>
      _pool;
};
}
