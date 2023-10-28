#include "pixmap.hpp"

pixmap::pixmap(const std::shared_ptr<renderer> renderer, const std::string &filename) : _renderer(renderer) {
  const auto buffer = file::read(filename);

  const auto decoder = avifDecoderCreate();

  //   rgb.depth = 8;
  // #if SDL_BYTEORDER == SDL_LIL_ENDIAN
  //   rgb.format = AVIF_RGB_FORMAT_BGRA;
  // #else
  //   rgb.format = AVIF_RGB_FORMAT_ARGB;
  // #endif

  if (avifDecoderSetIOMemory(decoder, reinterpret_cast<const uint8_t *>(&buffer[0]), buffer.size()) != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderSetIOMemory] Error while setting IO on avifDecoder: {}", filename));
  }

  if (avifDecoderParse(decoder) != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderParse] Error while parsing avifDecoder: {}", filename));
  }

  if (avifDecoderNextImage(decoder) != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderNextImage] Error while decoding avifDecoder: {}", filename));
  }

  _width = decoder->image->width;
  _height = decoder->image->height;
  const auto surface = SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 0, SDL_PIXELFORMAT_ARGB8888);

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
    avifRGBImageFreePixels(&rgb);
    avifDecoderDestroy(decoder);
    SDL_FreeSurface(surface);
    throw std::runtime_error(fmt::format("[avifImageYUVToRGB] Error while converting YUV to RGB on avifImage: {}", filename));
  }

  _texture = texture_ptr(SDL_CreateTextureFromSurface(*renderer, surface), SDL_Deleter());

  if (_texture == nullptr) {
    avifRGBImageFreePixels(&rgb);
    avifDecoderDestroy(decoder);
    throw std::runtime_error(fmt::format("[SDL_CreateTextureFromSurface] Error while creating texture from surface: {}", filename));
  }

  SDL_FreeSurface(surface);
  // avifRGBImageFreePixels(&rgb);
  avifDecoderDestroy(decoder);
}

void pixmap::draw(const int x, const int y) const {
  const SDL_Rect rect{x, y, _width, _height};

  SDL_RenderCopy(*_renderer, _texture.get(), nullptr, &rect);
}