#include "renderer.hpp"

using namespace graphics;

renderer::renderer(SDL_Window *window)
    : _renderer(SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                SDL_Deleter()) {
  if (!_renderer) {
    throw std::runtime_error(fmt::format("[SDL_CreateRenderer] failed to create renderer: {}", SDL_GetError()));
  }
}

renderer::operator SDL_Renderer *() { return _renderer.get(); }

void renderer::begin() { SDL_RenderClear(*this); }

void renderer::end() { SDL_RenderPresent(*this); }
