#include "window.hpp"

using namespace graphics;

window::window(std::string_view title, int32_t width, int32_t height, bool fullscreen) noexcept(false)
    : _width(width), _height(height),
      _window(SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)), SDL_Deleter()) {
  if (_window == nullptr) [[unlikely]] {
    std::ostringstream oss;
    oss << "[SDL_CreateWindow] failed to create window: " << SDL_GetError();
    throw std::runtime_error(oss.str());
  }
}

window::operator SDL_Window *() noexcept {
  return _window.get();
}

std::shared_ptr<renderer> window::create_renderer() const noexcept {
  return std::make_shared<renderer>(_window.get());
}

int32_t window::width() const noexcept {
  return _width;
}

int32_t window::height() const noexcept {
  return _height;
}
