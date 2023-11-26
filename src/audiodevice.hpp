#pragma once

#include "common.hpp"

namespace audio {
class audiodevice {
public:
  audiodevice();
  virtual ~audiodevice();

  uint32_t id() const;

private:
  uint32_t _id;
};
}
