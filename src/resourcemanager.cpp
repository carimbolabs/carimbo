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

bool resourcemanager::busy() const noexcept {
  return !_filenames.empty();
}

void resourcemanager::flush() noexcept {
  _pixmappool->flush();
  _soundmanager->flush();
  _fontfactory->flush();
}

void resourcemanager::prefetch(const std::vector<std::string> &filenames) noexcept {
  _filenames.insert(_filenames.cend(), filenames.cbegin(), filenames.cend());
}

void resourcemanager::update(float_t delta) noexcept {
  UNUSED(delta);

  if (_filenames.empty()) [[likely]] {
    return;
  }

  auto filename = std::move(_filenames.front());
  _filenames.pop_front();

  if (auto position = filename.rfind('.'); position != std::string::npos) {
    auto extension = filename.substr(position);
    if (auto it = _handlers.find(extension); it != _handlers.end()) {
      it->second(std::move(filename));
    }
  }
}

std::shared_ptr<graphics::renderer> resourcemanager::renderer() const noexcept {
  return _renderer;
}

std::shared_ptr<graphics::pixmappool> resourcemanager::pixmappool() const noexcept {
  return _pixmappool;
}

std::shared_ptr<audio::soundmanager> resourcemanager::soundmanager() const noexcept {
  return _soundmanager;
}

std::shared_ptr<graphics::fontfactory> resourcemanager::fontfactory() const noexcept {
  return _fontfactory;
}
