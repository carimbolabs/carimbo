#include "resourcemanager.hpp"

resourcemanager::resourcemanager(const std::shared_ptr<renderer> renderer) : _pixmappool(std::make_shared<pixmappool>(renderer)) {
}

void resourcemanager::preload(const std::list<std::string> &filenames) {
  _filenames = filenames;
  //_loading = true;

  // std::for_each(filenames.begin(), filenames.end(), [this](const std::string &filename) {
  //   if (filename.find(".avif") != std::string::npos) {
  //     _pixmappool->get(filename);
  //   }
  // });
}

void resourcemanager::update() {
  if (_filenames.empty()) {
    return;
  }

  const auto filename = _filenames.front();
  _filenames.pop_front();

  if (filename.find(".avif") != std::string::npos) {
    _pixmappool->get(filename);
  }
}
