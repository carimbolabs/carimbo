#include "timer.hpp"

uint32_t wrapper(uint32_t interval, void *param) {
  auto fn = static_cast<std::function<void()> *>(param);
  (*fn)();
  return interval;
}

timer::~timer() {
  SDL_RemoveTimer(_id);
}

void timer::set(int interval, const std::function<void()> fn) {
  _id = SDL_AddTimer(interval, wrapper, &const_cast<std::function<void()> &>(fn));
}
