#include "pixmappool.hpp"

pixmappool::pixmappool(const std::shared_ptr<renderer> renderer) : _renderer(renderer) {
}

const std::shared_ptr<pixmap> pixmappool::get(const std::string &filename) {
  if (_pool.find(filename) == _pool.end()) {
    _pool.emplace(filename, std::make_shared<pixmap>(_renderer, filename));
  }

  return _pool.at(filename);
}

void pixmappool::flush() {
  auto it = _pool.begin();

  while (it != _pool.end()) {
    if (it->second.unique()) {
      it = _pool.erase(it);
    } else {
      ++it;
    }
  }
}