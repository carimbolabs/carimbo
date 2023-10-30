#include "frames.hpp"

uint64_t frames::per_second() const {
  return _frames;
}

void frames::loop() {
  _frames++;
  _elapsed += 1000 / 60;
  if (_elapsed >= 1000) {
    std::cout << "FPS: " << _frames << std::endl;
    _elapsed = 0;
    _frames = 0;
  }
}