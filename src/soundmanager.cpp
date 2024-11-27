#include "soundmanager.hpp"

using namespace audio;

soundmanager::soundmanager(std::shared_ptr<audiodevice> audiodevice) noexcept
    : _audiodevice(std::move(audiodevice)) {}

std::shared_ptr<soundfx> soundmanager::get(const std::string &filename) {
  auto [it, added] = _soundmap.try_emplace(filename, nullptr);

  if (added) {
    std::cout << "[soundmanager] cache miss: " << filename << std::endl;

    assert(_audiodevice);

    it->second = std::make_shared<soundfx>(_audiodevice, filename);
  }

  return it->second;
}

void soundmanager::play(const std::string &filename, bool loop) noexcept {
  get(fmt::format("blobs/{}.ogg", filename))->play(loop);
}

void soundmanager::stop(const std::string &filename) noexcept {
  get(filename)->stop();
}

void soundmanager::flush() noexcept {
  for (auto it = _soundmap.begin(); it != _soundmap.end();) {
    switch (it->second.use_count()) {
    case 1:
      it = _soundmap.erase(it);
      break;

    default:
      ++it;
      break;
    }
  }
}
