#include "timermanager.hpp"

using namespace framework;

uint32_t generic_wrapper(uint32_t interval, void *param, bool repeat) {
  auto fn = static_cast<std::function<void()> *>(param);
  (*fn)();
  return repeat ? interval : 0;
}

uint32_t wrapper(uint32_t interval, void *param) {
  return generic_wrapper(interval, param, true);
}

uint32_t singleshot_wrapper(uint32_t interval, void *param) {
  return generic_wrapper(interval, param, false);
}

timermanager::~timermanager() {
  for (const auto &[id, ptr] : _timers) {
    SDL_RemoveTimer(id);
  }
}

void timermanager::set(int32_t interval, const std::function<void()> &fn) {
  add_timer(interval, fn, true);
}

void timermanager::singleshot(int32_t interval, const std::function<void()> &fn) {
  add_timer(interval, fn, false);
}

void timermanager::clear(int32_t id) {
  if (auto it = _timers.find(id); it != _timers.end()) {
    SDL_RemoveTimer(id);
    _timers.erase(it);
  }
}

void timermanager::add_timer(int32_t interval, const std::function<void()> &fn, bool repeat) {
  const auto ptr = std::make_shared<std::function<void()>>(fn);
  std::cout << ">>> interval " << interval << std::endl;
  const auto id = SDL_AddTimer(interval, repeat ? wrapper : singleshot_wrapper, ptr.get());
  if (!id) {
    throw std::runtime_error(fmt::format("[SDL_AddTimer] failed to set timer. reason: {}", SDL_GetError()));
  }

  _timers.emplace(id, ptr);
}
