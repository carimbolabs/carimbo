#pragma once

#include "common.hpp"
#include "loopable.hpp"

namespace framework {
class framerate : public loopable {
public:
  framerate() noexcept = default;
  ~framerate() noexcept override = default;

  uint64_t per_second() const noexcept;

  void loop(uint32_t delta) noexcept override;

private:
  uint64_t _frames{0};
  uint32_t _elapsed{0};
  uint32_t _start{SDL_GetTicks()};
};
}
