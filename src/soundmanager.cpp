#include "soundmanager.hpp"

soundmanager::soundmanager(std::shared_ptr<audiodevice> audiodevice) : _audiodevice(audiodevice) {
}

void soundmanager::prefetch(const std::vector<std::string> &filenames) {
  for (const auto &filename : filenames) {
    get(filename);
  }
}

const std::shared_ptr<soundfx> soundmanager::get(const std::string &filename) {
  if (_soundmap.find(filename) == _soundmap.end()) {
    std::cout << "[soundmanager] cache miss: " << filename << std::endl;
    assert(_audiodevice);
    const auto p = std::make_shared<soundfx>(_audiodevice, filename);
    _soundmap.emplace(filename, p);
    return p;
  }

  std::cout << "[soundmanager] cache hit: " << filename << std::endl;
  return _soundmap[filename];
}

void soundmanager::play(const std::string &filename) {
  get(filename)->play();
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
