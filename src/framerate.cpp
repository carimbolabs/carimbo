#include "framerate.hpp"

#include "loopable.hpp"

using namespace framework;

uint64_t framerate::per_second() const { return _frames; }

void framerate::loop(uint32_t delta) {
  UNUSED(delta);

  _frames++;

  const auto now = SDL_GetTicks();
  _elapsed += now - _start;
  _start = now;

  if (_elapsed >= 1000) {
    std::cout << fmt::format("{:.{}f}", _frames / (_elapsed / 1000.f), 1)
              << std::endl;
    _elapsed = 0;
    _frames = 0;
  }
}
