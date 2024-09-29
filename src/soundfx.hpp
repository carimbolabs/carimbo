#pragma once

#include "common.hpp"

namespace audio {
class soundfx {
public:
  soundfx(const std::shared_ptr<audiodevice> audiodevice, std::string_view filename);
  ~soundfx();

  void play() const;

  // std::vector<uint8_t> buffer;

private:
  std::shared_ptr<audiodevice> _audiodevice;

  // std::vector<uint8_t> data;
  ALuint buffer{};
  ALuint source{};
  ALenum format{};
  ALsizei frequency{};
};
}
