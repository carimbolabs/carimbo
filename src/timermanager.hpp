#pragma once

#include "common.hpp"

namespace framework {
class timermanager {
public:
  timermanager() = default;
  ~timermanager();

  void set(int32_t interval, const std::function<void()> &fn);

  void singleshot(int32_t timeout, const std::function<void()> &fn);

  void clear(int32_t id);

protected:
  void add_timer(int32_t interval, const std::function<void()> &fn, bool repeat);

private:
  std::map<int32_t, std::shared_ptr<std::function<void()>>> _timers;
};
}
