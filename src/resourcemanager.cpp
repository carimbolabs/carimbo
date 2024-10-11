#include "resourcemanager.hpp"

#include "helpers.hpp"
#include "pixmappool.hpp"
#include "renderer.hpp"
#include "soundmanager.hpp"
#include <cmath>

using namespace framework;

resourcemanager::resourcemanager(
    const std::shared_ptr<graphics::renderer> renderer,
    const std::shared_ptr<audio::audiodevice> audiodevice)
    : _pixmappool(std::make_shared<graphics::pixmappool>(renderer)),
      _soundmanager(std::make_shared<audio::soundmanager>(audiodevice)) {
  _handlers[".png"] = [this](const std::string_view filename) {
    _pixmappool->get(filename);
  };

  _handlers[".ogg"] = [this](const std::string_view filename) {
    _soundmanager->get(filename);
  };
}

void resourcemanager::prefetch(const std::vector<std::string> &filenames) {
  _filenames.insert(_filenames.end(), filenames.begin(), filenames.end());
}

void resourcemanager::update(double_t delta) {
  UNUSED(delta);

  if (_filenames.empty()) {
    return;
  }

  if (const auto filename = std::move(_filenames.front());
      !_filenames.empty()) {
    _filenames.pop_front();

    if (const auto position = filename.rfind('.');
        position != std::string::npos) {
      const auto extension = filename.substr(position);
      if (const auto it = _handlers.find(extension); it != _handlers.end()) {
        it->second(filename);
      }
    }
  }
}

bool resourcemanager::busy() const {
  return !_filenames.empty();
}

std::shared_ptr<graphics::pixmappool> resourcemanager::pixmappool() {
  return _pixmappool;
}

std::shared_ptr<audio::soundmanager> resourcemanager::soundmanager() {
  return _soundmanager;
}
