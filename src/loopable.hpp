#pragma once
#ifndef _loopable_hpp
#define _loopable_hpp

class loopable {
public:
  virtual ~loopable() noexcept = default;

  virtual void loop() = 0;
};

#endif