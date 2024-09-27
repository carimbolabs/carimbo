#pragma once

namespace framework {
class loopable {
public:
  virtual ~loopable() noexcept = default;

  virtual void loop(uint32_t delta) = 0;
};
} // namespace framework
