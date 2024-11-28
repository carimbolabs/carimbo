#include "pixmappool.hpp"

using namespace graphics;

pixmappool::pixmappool(const std::shared_ptr<renderer> &renderer) noexcept
    : _renderer(renderer) {}

const std::shared_ptr<pixmap> pixmappool::get(std::string_view filename) {
  auto [it, added] = _pool.insert_or_assign(filename, nullptr);

  if (added) [[unlikely]] {
    std::cout << "[pixmappool] cache miss: " << filename << std::endl;

    assert(_renderer);

    it->second = std::make_shared<pixmap>(_renderer, filename);
  }

  return it->second;
}

void pixmappool::flush() noexcept {
  std::erase_if(_pool, [](const auto &pair) { return pair.second.use_count() == MINIMAL_USE_COUNT; });
}
