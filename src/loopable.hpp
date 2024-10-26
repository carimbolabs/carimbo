#pragma once

namespace framework {
class loopable {
public:
  loopable() = default;
  virtual ~loopable() = default;

  virtual void loop(uint32_t delta) noexcept = 0;
};
}
