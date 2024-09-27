#include "window.hpp"

#include "renderer.hpp"

using namespace graphics;

window::window(std::string_view title, int32_t width, int32_t height,
               bool fullscreen)
    : _width(width), _height(height),
      _window(SDL_CreateWindow(
                  title.data(),
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  width,
                  height,
                  SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)),
              SDL_Deleter()) {
  if (_window == nullptr) {
    throw std::runtime_error(fmt::format(
        "[SDL_CreateWindow] failed to create window: {}", SDL_GetError()));
  }
}

window::operator SDL_Window *() { return _window.get(); }

const std::shared_ptr<renderer> window::create_renderer() const {
  return std::make_shared<renderer>(&*_window);
}

int32_t window::width() const { return _width; }

int32_t window::height() const { return _height; }
