#pragma once

#include "common.hpp"

namespace audio {
class soundfx {
public:
  soundfx(std::shared_ptr<audiodevice> audiodevice, std::string_view filename);
  ~soundfx() noexcept;

  void play(bool loop) const noexcept;
  void stop() const noexcept;

private:
  std::shared_ptr<audiodevice> _audiodevice;
  ALuint source{};
};
}
