#include "resourcemanager.hpp"

resourcemanager::resourcemanager(const std::shared_ptr<renderer> renderer) : _pixmappool(std::make_shared<pixmappool>(renderer)) {
}

void resourcemanager::preload(const std::vector<std::string> &filenames) {
  std::for_each(filenames.begin(), filenames.end(), [](const std::string &filename) {
    if (filename.find(".avif") != std::string::npos) {
      _pixmappool::preload(filename);
    }
  });
}