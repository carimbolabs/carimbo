#include "window.hpp"

window::window(const std::string &title, uint64_t width, uint64_t height) {
  _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

  if (_window == nullptr) {
    throw std::runtime_error(fmt::format("Failed to create window: {}", SDL_GetError()));
  }
}

window::~window() {
  SDL_DestroyWindow(_window);
}

const std::shared_ptr<renderer> window::create_renderer() const {
  return std::make_shared<renderer>(_window);
}
