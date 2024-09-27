#pragma once

#include "common.hpp"

#include "loopable.hpp"

namespace framework {
class framerate : public loopable {
public:
  framerate() = default;
  virtual ~framerate() = default;

  uint64_t per_second() const;

  void loop(uint32_t delta) override;

private:
  uint64_t _frames;
  uint32_t _elapsed;
  uint32_t _start;
};
}
