#include "pixmappool.hpp"

using namespace graphics;

pixmappool::pixmappool(const std::shared_ptr<renderer> &renderer) noexcept
    : _renderer(renderer) {}

const std::shared_ptr<pixmap> pixmappool::get(std::string_view filename) {
  auto [it, added] = _pool.try_emplace(filename, nullptr);

  if (added) {
    std::cout << "[pixmappool] cache miss: " << filename << std::endl;

    assert(_renderer);

    it->second = std::make_shared<pixmap>(_renderer, filename);
  }

  return it->second;
}

void pixmappool::flush() noexcept {
  for (auto it = _pool.begin(); it != _pool.end();) {
    switch (it->second.use_count()) {
    case 1:
      it = _pool.erase(it);
      break;

    default:
      ++it;
      break;
    }
  }
}
