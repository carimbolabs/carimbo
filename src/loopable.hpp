#pragma once
#ifndef _loopable_hpp
#define _loopable_hpp

namespace framework {
class loopable {
public:
  virtual ~loopable() noexcept = default;

  virtual void loop(uint32_t delta) = 0;
};
}

#endif