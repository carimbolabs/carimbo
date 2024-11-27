#pragma once

#include "common.hpp"

namespace framework {
class resourcemanager {
public:
  resourcemanager() = delete;
  resourcemanager(std::shared_ptr<graphics::renderer> renderer, std::shared_ptr<audio::audiodevice> audiodevice) noexcept;
  ~resourcemanager() noexcept = default;

  void prefetch(const std::vector<std::string> &filenames) noexcept;
  void update(float_t delta) noexcept;
  bool busy() const noexcept;
  void flush() noexcept;

  std::shared_ptr<graphics::renderer> renderer() const noexcept;
  std::shared_ptr<graphics::pixmappool> pixmappool() noexcept;
  std::shared_ptr<audio::soundmanager> soundmanager() noexcept;
  std::shared_ptr<graphics::fontfactory> fontfactory() noexcept;

private:
  std::map<std::string, std::function<void(const std::string &)>> _handlers;
  std::list<std::string> _filenames;
  std::shared_ptr<graphics::renderer> _renderer;
  std::shared_ptr<audio::audiodevice> _audiodevice;
  std::shared_ptr<graphics::pixmappool> _pixmappool;
  std::shared_ptr<audio::soundmanager> _soundmanager;
  std::shared_ptr<graphics::fontfactory> _fontfactory;
};
}
