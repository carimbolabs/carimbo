#include "pixmappool.hpp"

using namespace graphics;

pixmappool::pixmappool(const std::shared_ptr<renderer> renderer) noexcept
    : _renderer(std::move(renderer)) {}

const std::shared_ptr<pixmap> pixmappool::get(const std::string &filename) {
  auto [it, added] = _pool.insert_or_assign(filename, nullptr);

  if (added) [[unlikely]] {
    fmt::println("[pixmappool] cache miss {}", filename);

    assert(_renderer);

    it->second = std::make_shared<pixmap>(_renderer, filename);
  }

  return it->second;
}

void pixmappool::flush() noexcept {
  fmt::println("[pixmappool] actual size {}", _pool.size());

  const auto count = std::erase_if(_pool, [](const auto &pair) { return pair.second.use_count() == MINIMAL_USE_COUNT; });
  fmt::println("[pixmappool] {} objects have been flushed", count);
}

void pixmappool::update(float_t delta) noexcept {
  UNUSED(delta);
}
