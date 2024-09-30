#pragma once

#include "common.hpp"

namespace audio {
class soundfx {
public:
  soundfx(const std::shared_ptr<audiodevice> audiodevice, std::string_view filename);
  ~soundfx();

  void play(bool loop) const;

  void stop() const;

private:
  std::shared_ptr<audiodevice> _audiodevice;

  ALuint source{};
};
}
