#include "resourcemanager.hpp"

#include "pixmappool.hpp"
#include "renderer.hpp"
#include "soundmanager.hpp"

resourcemanager::resourcemanager(const std::shared_ptr<renderer> renderer, const std::shared_ptr<audiodevice> audiodevice) : _pixmappool(std::make_shared<pixmappool>(renderer)), _soundmanager(std::make_shared<soundmanager>(audiodevice)) {
}

void resourcemanager::prefetch(const std::vector<std::string> &filenames) {
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

  if (filename.find(".ogg") != std::string::npos) {
    _soundmanager->get(filename);
  }
}

bool resourcemanager::busy() const {
  return !_filenames.empty();
}

std::shared_ptr<pixmappool> resourcemanager::get_pixmappool() {
  return _pixmappool;
}

std::shared_ptr<soundmanager> resourcemanager::get_soundmanager() {
  return _soundmanager;
}