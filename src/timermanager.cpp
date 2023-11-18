#include "timermanager.hpp"

using namespace framework;

uint32_t wrapper(uint32_t interval, void *param) {
  auto fn = static_cast<std::function<void()> *>(param);
  (*fn)();
  return interval;
}

timermanager::~timermanager() {
  for (const auto &[id, fn] : _timers) {
    SDL_RemoveTimer(id);
  }
}

void timermanager::set(int32_t interval, const std::function<void()> &fn) {
  const auto id = SDL_AddTimer(interval, wrapper, &const_cast<std::function<void()> &>(fn));
  if (id == 0) {
    throw std::runtime_error(fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError()));
  }

  _timers[id] = fn;
}

void timermanager::clear(int32_t id) {
  if (id == 0) {
    return;
  }

  const auto it = _timers.find(id);
  if (it == _timers.end()) {
    return;
  }

  SDL_RemoveTimer(id);
  _timers.erase(it);
}