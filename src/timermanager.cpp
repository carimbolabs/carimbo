#include "timermanager.hpp"

using namespace framework;

uint32_t wrapper(uint32_t interval, void *param) {
  auto fn = static_cast<std::function<void()> *>(param);
  (*fn)();
  return interval;
}

timermanager::~timermanager() {
  for (const auto &[id, ptr] : _timers) {
    SDL_RemoveTimer(id);
    delete ptr;
  }
}

void timermanager::set(int32_t interval, const std::function<void()> &fn) {
  const auto ptr = new std::function<void()>(fn);
  const auto id = SDL_AddTimer(interval, wrapper, ptr);
  if (id == 0) {
    throw std::runtime_error(
        fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError())
    );
  }

  _timers.emplace(id, ptr);
}

void timermanager::clear(int32_t id) {
  if (auto it = _timers.find(id); it != _timers.end()) {
    SDL_RemoveTimer(id);
    delete it->second;
    _timers.erase(it);
  }
}
