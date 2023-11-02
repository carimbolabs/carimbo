#pragma once
#ifndef _resourcemanager_hpp
#define _resourcemanager_hpp

#include "common.hpp"
#include "pixmappool.hpp"
#include "renderer.hpp"

class resourcemanager {
public:
  resourcemanager(const std::shared_ptr<renderer> renderer);
  ~resourcemanager() = default;

  void preload(const std::vector<std::string> &filenames);

private:
  std::shared_ptr<pixmappool> _pixmappool;
};

#endif
