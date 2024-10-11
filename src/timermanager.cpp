#include "timermanager.hpp"

using namespace framework;

uint32_t wrapper(uint32_t interval, void *param) {
  auto fn = static_cast<std::function<void()> *>(param);
  (*fn)();
  return interval;
}

timermanager::~timermanager() {
  for (const auto &[id, _] : _timers) {
    SDL_RemoveTimer(id);
  }
}

void timermanager::set(int32_t interval, std::function<void()> fn) {
  const auto id = SDL_AddTimer(interval, wrapper, new std::function<void()>(fn));
  if (id == 0) {
    throw std::runtime_error(
        fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError()));
  }

  _timers.emplace(id, std::move(fn));
}

void timermanager::clear(int32_t id) {
  if (auto it = _timers.find(id); it != _timers.end()) {
    SDL_RemoveTimer(id);
    _timers.erase(it);
  }
}
