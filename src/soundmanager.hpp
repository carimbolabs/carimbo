#pragma once

#include "common.hpp"
#include "soundfx.hpp"

namespace audio {
class soundmanager {
public:
  soundmanager(std::shared_ptr<audiodevice> audiodevice);
  ~soundmanager() = default;

  void prefetch(const std::vector<std::string> &filenames);

  const std::shared_ptr<soundfx> get(const std::string &filename);

  void play(const std::string &filename, bool loop);

  void stop(const std::string &filename);

  void flush();

private:
  std::shared_ptr<audiodevice> _audiodevice;
  std::map<std::string_view, std::shared_ptr<soundfx>> _soundmap;
};
}
