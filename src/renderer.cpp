#include "renderer.hpp"

renderer::renderer(SDL_Window *window) : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) {}

// renderer::~renderer() {
// }

// void renderer::render() {
//   const auto renderer = _renderer.get();
//   SDL_RenderClear(renderer);
//   SDL_RenderPresent(renderer);
// }

renderer::operator SDL_Renderer *() {
  return _renderer.get();
}
