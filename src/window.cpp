#include "window.hpp"

window::window(std::string_view title, int32_t width, int32_t height, bool fullscreen) : _window(SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)), SDL_Deleter()) {
  if (_window == nullptr) {
    throw std::runtime_error(fmt::format("[SDL_CreateWindow] Failed to create window: {}", SDL_GetError()));
  }
}

window::operator SDL_Window *() {
  return _window.get();
}

const std::shared_ptr<renderer> window::create_renderer() const {
  return std::make_shared<renderer>(&*_window);
}
