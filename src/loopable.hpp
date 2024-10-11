#pragma once

namespace framework {
class loopable {
public:
  virtual ~loopable() = default;

  virtual void loop(uint32_t delta) = 0;
};
}
