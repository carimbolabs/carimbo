#pragma once

#include "common.hpp"
#include "soundfx.hpp"

namespace audio {
class soundmanager {
public:
  soundmanager(std::shared_ptr<audiodevice> audiodevice) noexcept;
  ~soundmanager() noexcept = default;

  void prefetch(const std::vector<std::string> &filenames) noexcept;
  std::shared_ptr<soundfx> get(const std::string &filename) noexcept;
  void play(const std::string &filename, bool loop) noexcept;
  void stop(const std::string &filename) noexcept;
  void flush() noexcept;

private:
  std::shared_ptr<audiodevice> _audiodevice;
  std::map<std::string, std::shared_ptr<soundfx>> _soundmap;
};
}
