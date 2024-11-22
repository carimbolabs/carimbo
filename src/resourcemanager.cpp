#include "resourcemanager.hpp"

using namespace framework;

resourcemanager::resourcemanager(std::shared_ptr<graphics::renderer> renderer, std::shared_ptr<audio::audiodevice> audiodevice) noexcept
    : _renderer(std::move(renderer)),
      _audiodevice(std::move(audiodevice)),
      _pixmappool(std::make_shared<graphics::pixmappool>(_renderer)),
      _soundmanager(std::make_shared<audio::soundmanager>(_audiodevice)),
      _fontfactory(std::make_shared<graphics::fontfactory>(_renderer)) {
  _handlers[".png"] = [this](const std::string &filename) {
    _pixmappool->get(filename);
  };

  _handlers[".ogg"] = [this](const std::string &filename) {
    _soundmanager->get(filename);
  };

  _handlers[".json"] = [this](const std::string &filename) {
    _fontfactory->get(filename);
  };
}

void resourcemanager::prefetch(const std::vector<std::string> &filenames) {
  _filenames.insert(_filenames.end(), filenames.begin(), filenames.end());
}

void resourcemanager::update(float_t delta) noexcept {
  UNUSED(delta);

  if (_filenames.empty()) {
    return;
  }

  const auto filename = std::move(_filenames.front());
  _filenames.pop_front();

  if (const auto position = filename.rfind('.'); position != std::string::npos) {
    const auto extension = filename.substr(position);
    if (const auto it = _handlers.find(extension); it != _handlers.end()) {
      it->second(filename);
    }
  }
}

bool resourcemanager::busy() const noexcept {
  return !_filenames.empty();
}

std::shared_ptr<graphics::renderer> resourcemanager::renderer() const noexcept {
  return _renderer;
}

std::shared_ptr<graphics::pixmappool> resourcemanager::pixmappool() noexcept {
  return _pixmappool;
}

std::shared_ptr<audio::soundmanager> resourcemanager::soundmanager() noexcept {
  return _soundmanager;
}

std::shared_ptr<graphics::fontfactory> resourcemanager::fontfactory() noexcept {
  return _fontfactory;
}
