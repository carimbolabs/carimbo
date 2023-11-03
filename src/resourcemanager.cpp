#include "resourcemanager.hpp"

resourcemanager::resourcemanager(const std::shared_ptr<renderer> renderer) : _pixmappool(std::make_shared<pixmappool>(renderer)), _soundmanager(std::make_shared<soundmanager>()) {
}

void resourcemanager::preload(const std::list<std::string> &filenames) {
  _filenames.insert(_filenames.end(), filenames.begin(), filenames.end());
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

  if (filename.find(".aac") != std::string::npos) {
    _soundmanager->get(filename);
  }
}

bool resourcemanager::busy() const {
  return !_filenames.empty();
}
