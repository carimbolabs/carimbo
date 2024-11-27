#include "delay.hpp"

using namespace framework;

void delay(uint32_t interval) noexcept {
  SDL_Delay(interval);
}
