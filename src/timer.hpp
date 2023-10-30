#pragma once
#ifndef _timer_hpp
#define _timer_hpp

#include "common.hpp"

class timer {
public:
  timer() = default;
  virtual ~timer();

  void set(int interval, const std::function<void()> fn);

private:
  int32_t _id;
};

#endif