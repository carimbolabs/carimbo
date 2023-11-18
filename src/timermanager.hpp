#pragma once
#ifndef _timer_hpp
#define _timer_hpp

#include "common.hpp"

namespace framework {
class timermanager {
public:
  timermanager() = default;
  virtual ~timermanager();

  void set(int32_t interval, const std::function<void()> &fn);

  void clear(int32_t id);

private:
  std::map<int32_t, std::function<void()>> _timers;
};
}

#endif