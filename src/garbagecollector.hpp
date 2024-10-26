#pragma once

#include "common.hpp"

namespace framework {
class garbagecollector {
public:
  garbagecollector() = delete;
  ~garbagecollector() = delete;

  static void collect() noexcept;

private:
};
}
