#include "soundmanager.hpp"

using namespace audio;

soundmanager::soundmanager(std::shared_ptr<audiodevice> audiodevice)
    : _audiodevice(audiodevice) {}

void soundmanager::prefetch(const std::vector<std::string> &filenames) {
  for (const auto &filename : filenames) {
    get(filename);
  }
}

const std::shared_ptr<soundfx> soundmanager::get(const std::string &filename) {
  auto [it, added] = _soundmap.try_emplace(filename, nullptr);

  if (added) {
    std::cout << "[soundmanager] cache miss: " << filename << std::endl;
    assert(_audiodevice);
    it->second = std::make_shared<soundfx>(_audiodevice, std::string(filename));
  }

#ifdef DEBUG
  std::cout << "[soundmanager] cache hit: " << filename << std::endl;
#endif

  return it->second;
}

void soundmanager::play(const std::string &filename, bool loop = false) {
  get(fmt::format("blobs/{}.ogg", filename))->play(loop);
}

void soundmanager::stop(const std::string &filename) {
  get(filename)->stop();
}

void soundmanager::flush() {
  for (auto it = _soundmap.begin(); it != _soundmap.end();) {

    const auto unique = it->second.use_count() == 1;
    if (unique) {
      it = _soundmap.erase(it);
    } else {
      ++it;
    }
  }
}
