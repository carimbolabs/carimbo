#pragma once
#ifndef _soundmanager_hpp
#define _soundmanager_hpp

#include "common.hpp"
#include "soundfx.hpp"

class soundmanager {
public:
  ~soundmanager() = default;
  soundmanager() = default;

  void preload(const std::vector<std::string> &filenames);

  const std::shared_ptr<soundfx> get(const std::string &filename);

  void flush();

private:
  std::unordered_map<std::string, std::shared_ptr<soundfx>, std::hash<std::string>> _soundmap;
};

#endif