#include "font.hpp"
#include "resourcemanager.hpp"

using namespace graphics;

font::font(
    const std::shared_ptr<framework::resourcemanager> resourcemanager,
    const std::string &filename,
    const std::string &alphabet
) {
  UNUSED(filename);
  UNUSED(alphabet);

  const auto texture = resourcemanager->pixmappool()->get(filename);
  int32_t width, height;
  SDL_QueryTexture(*texture, NULL, NULL, &width, &height);

  SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

  if (SDL_RenderReadPixels(*resourcemanager->renderer(), NULL, surface->format->format, surface->pixels, surface->pitch) != 0) {
    printf("Error reading pixels: %s\n", SDL_GetError());
  }

  uint32_t *pixels = (uint32_t *)surface->pixels;
  for (int32_t y = 0; y < height; ++y) {
    for (int32_t x = 0; x < width; ++x) {
      uint32_t pixel = pixels[(y * width) + x];
      uint8_t r, g, b, a;
      SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
    }
  }

  SDL_FreeSurface(surface);
}

// void font::update(double_t delta) {
//   for (auto &[key, glyph] : _glyphs) {
//     glyph.update(delta);
//   }
// }

// void font::draw() const {
//   for (const auto &[key, glyph] : _glyphs) {
//     glyph.draw();
//   }
// }
