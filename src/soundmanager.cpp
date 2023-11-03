#include "soundmanager.hpp"

void soundmanager::preload(const std::vector<std::string> &filenames) {
  for (const auto &filename : filenames) {
    get(filename);
  }
}

const std::shared_ptr<soundfx> soundmanager::get(const std::string &filename) {
  if (_soundmap.find(filename) == _soundmap.end()) {
    std::cout << "[soundmanager] cache miss: " << filename << std::endl;
    const auto p = std::make_shared<soundfx>(filename);
    _soundmap.emplace(filename, p);
    return p;
  }

  std::cout << "[soundmanager] cache hit: " << filename << std::endl;
  return _soundmap[filename];
}

void soundmanager::flush() {
  auto it = _soundmap.begin();

  while (it != _soundmap.end()) {
    if (it->second.unique()) {
      it = _soundmap.erase(it);
    } else {
      ++it;
    }
  }
}