#include "pixmappool.hpp"

#include "pixmap.hpp"

using namespace graphics;

pixmappool::pixmappool(const std::shared_ptr<renderer> renderer)
    : _renderer(renderer) {}

void pixmappool::preload(const std::vector<std::string> &filenames) {
  for (const auto &filename : filenames) {
    get(filename);
  }
}

const std::shared_ptr<pixmap> pixmappool::get(const std::string &filename) {
  if (_pool.find(filename) == _pool.end()) {
    std::cout << "[pixmappool] cache miss: " << filename << std::endl;
    const auto p = std::make_shared<pixmap>(_renderer, filename);
    _pool.emplace(filename, p);
    return p;
  }

  std::cout << "[pixmappool] cache hit: " << filename << std::endl;
  return _pool[filename];
}

void pixmappool::flush() {
  for (auto it = _pool.begin(); it != _pool.end();) {

    const auto unique = it->second.use_count() == 1;
    if (unique) {
      it = _pool.erase(it);
    } else {
      ++it;
    }
  }
}
