#include "resourcemanager.hpp"

#include "pixmappool.hpp"
#include "renderer.hpp"
#include "soundmanager.hpp"

using namespace framework;

resourcemanager::resourcemanager(
    const std::shared_ptr<graphics::renderer> renderer,
    const std::shared_ptr<audio::audiodevice> audiodevice)
    : _pixmappool(std::make_shared<graphics::pixmappool>(renderer)),
      _soundmanager(std::make_shared<audio::soundmanager>(audiodevice)) {
  _handlers[".avif"] = [this](const std::string &filename) {
    _pixmappool->get(filename);
  };

  _handlers[".ogg"] = [this](const std::string &filename) {
    _soundmanager->get(filename);
  };
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

  const auto pos = filename.rfind('.');
  if (pos != std::string::npos) {
    const auto extension = filename.substr(pos);

    const auto it = _handlers.find(extension);
    if (it != _handlers.end()) {
      it->second(filename);
    }
  }
}

bool resourcemanager::busy() const { return !_filenames.empty(); }

std::shared_ptr<graphics::pixmappool> resourcemanager::pixmappool() {
  return _pixmappool;
}

std::shared_ptr<audio::soundmanager> resourcemanager::soundmanager() {
  return _soundmanager;
}
