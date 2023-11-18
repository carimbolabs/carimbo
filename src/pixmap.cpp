#include "pixmap.hpp"

#include "io.hpp"
#include "renderer.hpp"

pixmap::pixmap(const std::shared_ptr<renderer> renderer, std::string_view filename) : _renderer(renderer) {
  const auto buffer = io::read(filename);
  auto result = avifResult{};

  std::unique_ptr<avifDecoder, decltype(&avifDecoderDestroy)> decoder{avifDecoderCreate(), &avifDecoderDestroy};

  result = avifDecoderSetIOMemory(decoder.get(), reinterpret_cast<const uint8_t *>(&buffer[0]), buffer.size());
  if (result != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderSetIOMemory] error while setting IO on AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  result = avifDecoderParse(decoder.get());
  if (result != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderParse] error while parsing AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  result = avifDecoderNextImage(decoder.get());
  if (result != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderNextImage] error while decoding AVIF: {}, error: {}", filename, avifResultToString(result)));
  }

  _size = ::size{decoder->image->width, decoder->image->height};

  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{SDL_CreateRGBSurfaceWithFormat(0, decoder->image->width, decoder->image->height, 0, SDL_PIXELFORMAT_ARGB8888), SDL_FreeSurface};

  if (surface == nullptr) {
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
    throw std::runtime_error(fmt::format("[avifImageYUVToRGB] error while converting YUV to RGB on avifImage: {}", filename));
  }

  _texture = texture_ptr(SDL_CreateTextureFromSurface(*renderer, surface.get()), SDL_Deleter());

  if (_texture == nullptr) {
    throw std::runtime_error(fmt::format("[SDL_CreateTextureFromSurface] error while creating texture from surface: {}", filename));
  }
}

void pixmap::draw(const point point, const double angle, const uint8_t alpha) const {
  const SDL_Rect rect{point.x(), point.y(), static_cast<int>(_size.width()), static_cast<int>(_size.height())};

  SDL_SetTextureAlphaMod(_texture.get(), alpha);
  SDL_RenderCopyEx(*_renderer, _texture.get(), nullptr, &rect, angle, nullptr, static_cast<SDL_RendererFlip>(flip::none));
}

const size pixmap::size() const {
  return _size;
}

void pixmap::set_size(const ::size &size) {
  _size = size;
}