#include "timermanager.hpp"

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
  std::cout << "timermanager::set interval " << interval << "fn " << &fn << std::endl;

  const auto id = SDL_AddTimer(interval, wrapper, &const_cast<std::function<void()> &>(fn));
  if (id == 0) {
    throw std::runtime_error(fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError()));
  }

  _timers[id] = fn;
}

void timermanager::shot(int32_t timeout, const std::function<void()> &fn) {
}

// void timermanager::set(int32_t interval, const sol::function &fn) {
//   const auto id = SDL_AddTimer(interval, wrapper, &const_cast<sol::function &>(fn));
//   if (id == 0) {
//     throw std::runtime_error(fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError()));
//   }

//   _timers[id] = std::move(fn);
// }

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