#include "soundmanager.hpp"

using namespace audio;

soundmanager::soundmanager(std::shared_ptr<audiodevice> audiodevice) noexcept
    : _audiodevice(std::move(audiodevice)) {}

std::shared_ptr<soundfx> soundmanager::get(std::string_view filename) {
  auto [it, added] = _pool.insert_or_assign(filename, nullptr);

  if (added) [[unlikely]] {
    std::cout << "[soundmanager] cache miss: " << filename << std::endl;

    assert(_audiodevice);

    it->second = std::make_shared<soundfx>(_audiodevice, filename);
  }

  return it->second;
}

void soundmanager::play(std::string_view filename) noexcept {
  std::cout << "play " << filename << std::endl;

  if (const auto &sound = get(fmt::format("blobs/{}.ogg", filename)); sound) {
    sound->play();
  }
}

void soundmanager::stop(std::string_view filename) noexcept {
  if (const auto &sound = get(filename); sound) {
    sound->stop();
  }
}

void soundmanager::flush() noexcept {
  std::erase_if(_pool, [](const auto &pair) { return pair.second.use_count() == MINIMAL_USE_COUNT; });
}

void soundmanager::update(float_t delta) noexcept {
  UNUSED(delta);
}
