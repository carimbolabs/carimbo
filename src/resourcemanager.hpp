#pragma once
#ifndef _resourcemanager_hpp
#define _resourcemanager_hpp

#include "common.hpp"
#include "pixmappool.hpp"
#include "renderer.hpp"
#include "soundmanager.hpp"

class resourcemanager {
public:
  resourcemanager(const std::shared_ptr<renderer> renderer);
  ~resourcemanager() = default;

  void preload(const std::list<std::string> &filenames);

  void update();

  bool busy() const;

  std::shared_ptr<pixmappool> get_pixmappool();

  std::shared_ptr<soundmanager> get_soundmanager();

private:
  std::list<std::string> _filenames;
  std::shared_ptr<pixmappool> _pixmappool;
  std::shared_ptr<soundmanager> _soundmanager;
};

#endif
