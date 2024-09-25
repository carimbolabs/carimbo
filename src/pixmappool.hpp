#pragma once

#include "common.hpp"
#include <mutex>

namespace graphics {
class pixmappool {
public:
  explicit pixmappool(const std::shared_ptr<renderer> renderer);
  ~pixmappool() = default;

  void preload(const std::vector<std::string_view> &filenames);

  const std::shared_ptr<pixmap> get(const std::string_view filename);

  void flush();

private:
  std::shared_ptr<renderer> _renderer;

  std::unordered_map<std::string_view, std::shared_ptr<pixmap>,
                     std::hash<std::string_view>>
      _pool;
};
} // namespace graphics
