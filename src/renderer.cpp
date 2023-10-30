#include "renderer.hpp"

renderer::renderer(SDL_Window *window) : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_Deleter()) {
  if (!_renderer) {
    throw std::runtime_error(fmt::format("[SDL_CreateRenderer] Failed to create renderer: {}", SDL_GetError()));
  }
}

renderer::operator SDL_Renderer *() {
  return _renderer.get();
}

void renderer::begin_draw() {
  _time = SDL_GetTicks();

  SDL_RenderClear(*this);
}

void renderer::end_draw() {
  SDL_RenderPresent(*this);

  const auto delta = SDL_GetTicks() - _time;
  if (delta < DELAY_MS) {
    SDL_Delay(DELAY_MS - delta);
  }
}
