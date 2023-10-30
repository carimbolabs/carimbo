#pragma once
#ifndef _frames_hpp
#define _frames_hpp

#include "common.hpp"
#include "loopable.hpp"

class frames : public loopable {
public:
  frames() = default;
  virtual ~frames() = default;

  uint64_t per_second() const;

  void loop() override;

private:
  uint64_t _frames;
  uint64_t _elapsed;
};

#endif
