#pragma once

#include "common.hpp"

namespace audio {
class audiodevice {
public:
  audiodevice();
  ~audiodevice() noexcept;

private:
  // uint32_t _id;
  std::unique_ptr<ALCdevice, void (*)(ALCdevice *)> device;
  std::unique_ptr<ALCcontext, void (*)(ALCcontext *)> context;
};
}
