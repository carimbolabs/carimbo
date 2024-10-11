#pragma once

#include "common.hpp"

namespace framework {
class timermanager {
public:
  timermanager() = default;
  ~timermanager();

  void set(int32_t interval, const std::function<void()> &fn);

  void clear(int32_t id);

private:
  std::map<int32_t, std::shared_ptr<std::function<void()>>> _timers;
};
}
