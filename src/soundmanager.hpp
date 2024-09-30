#pragma once

#include "common.hpp"
#include "soundfx.hpp"

namespace audio {
class soundmanager {
public:
  soundmanager(std::shared_ptr<audiodevice> audiodevice);
  ~soundmanager() = default;

  void prefetch(const std::vector<std::string_view> &filenames);

  const std::shared_ptr<soundfx> get(const std::string_view filename);

  void play(const std::string_view filename, bool loop);

  void flush();

private:
  std::shared_ptr<audiodevice> _audiodevice;

  std::unordered_map<std::string_view, std::shared_ptr<soundfx>,
                     std::hash<std::string_view>>
      _soundmap;
};
}
