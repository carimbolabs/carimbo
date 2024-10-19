#pragma once

#include "common.hpp"

namespace framework {
class resourcemanager {
public:
  resourcemanager(
      const std::shared_ptr<graphics::renderer> renderer,
      const std::shared_ptr<audio::audiodevice> audiodevice
  );

  ~resourcemanager() = default;

  void prefetch(const std::vector<std::string> &filenames);

  void update(double_t delta);

  bool busy() const;

  std::shared_ptr<graphics::renderer> renderer() const;

  std::shared_ptr<graphics::pixmappool> pixmappool();

  std::shared_ptr<audio::soundmanager> soundmanager();

private:
  std::map<std::string, std::function<void(const std::string &)>> _handlers;

  std::list<std::string> _filenames;
  std::shared_ptr<graphics::renderer> _renderer;
  std::shared_ptr<audio::audiodevice> _audiodevice;
  std::shared_ptr<graphics::pixmappool> _pixmappool;
  std::shared_ptr<audio::soundmanager> _soundmanager;
};
}
