#include "pixmap.hpp"

pixmap::pixmap(const std::shared_ptr<renderer> renderer, std::string_view filename) : _renderer(renderer) {
  const auto buffer = io::read(filename);
  const auto decoder = avifDecoderCreate();
  auto result = avifResult{};

  result = avifDecoderSetIOMemory(decoder, reinterpret_cast<const uint8_t *>(&buffer[0]), buffer.size());
  if (result != AVIF_RESULT_OK) {
    avifDecoderDestroy(decoder);
    throw std::runtime_error(fmt::format("[avifDecoderSetIOMemory] error while setting IO on AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  result = avifDecoderParse(decoder);
  if (result != AVIF_RESULT_OK) {
    avifDecoderDestroy(decoder);
    throw std::runtime_error(fmt::format("[avifDecoderParse] error while parsing AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  result = avifDecoderNextImage(decoder);
  if (result != AVIF_RESULT_OK) {
    avifDecoderDestroy(decoder);
    throw std::runtime_error(fmt::format("[avifDecoderNextImage] error while decoding AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  _width = decoder->image->width;
  _height = decoder->image->height;

  const auto surface = SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 0, SDL_PIXELFORMAT_ARGB8888);

  if (surface == nullptr) {
    avifDecoderDestroy(decoder);
    throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormat] error while creating surface with format: {}, error {}", filename, SDL_GetError()));
  }

  avifRGBImage rgb{};
  rgb.width = surface->w;
  rgb.height = surface->h;
  rgb.depth = 8;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  rgb.format = AVIF_RGB_FORMAT_BGRA;
#else
  rgb.format = AVIF_RGB_FORMAT_ARGB;
#endif
  rgb.pixels = (uint8_t *)surface->pixels;
  rgb.rowBytes = (uint32_t)surface->pitch;

  if (avifImageYUVToRGB(decoder->image, &rgb) != AVIF_RESULT_OK) {
    avifDecoderDestroy(decoder);
    SDL_FreeSurface(surface);
    throw std::runtime_error(fmt::format("[avifImageYUVToRGB] error while converting YUV to RGB on avifImage: {}", filename));
  }

  _texture = texture_ptr(SDL_CreateTextureFromSurface(*renderer, surface), SDL_Deleter());

  if (_texture == nullptr) {
    avifDecoderDestroy(decoder);
    SDL_FreeSurface(surface);
    throw std::runtime_error(fmt::format("[SDL_CreateTextureFromSurface] error while creating texture from surface: {}", filename));
  }

  avifDecoderDestroy(decoder);
  SDL_FreeSurface(surface);
}

void pixmap::draw(const int32_t x, const int32_t y) const {
  const SDL_Rect rect{x, y, _width, _height};

  SDL_RenderCopy(*_renderer, _texture.get(), nullptr, &rect);
}