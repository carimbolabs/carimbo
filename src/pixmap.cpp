#include "pixmap.hpp"

#include "deleters.hpp"
#include "io.hpp"
#include "renderer.hpp"
#include <cstdint>
#include <spng.h>
#include <vector>

using namespace graphics;

pixmap::pixmap(const std::shared_ptr<renderer> renderer, std::string_view filename)
    : _renderer(renderer) {
  const auto buffer = storage::io::read(filename);

  auto ctx = std::unique_ptr<spng_ctx, std::function<void(spng_ctx *)>>(
      spng_ctx_new(0), [](spng_ctx *ptr) {
        if (ptr) {
          spng_ctx_free(ptr);
        }
      });

  if (const auto error = spng_set_png_buffer(ctx.get(), buffer.data(), buffer.size()); error != SPNG_OK) {
    throw std::runtime_error(
        fmt::format("[spng_set_png_buffer] error while parsing image: {}, error: {}", filename, spng_strerror(error)));
  }

  spng_ihdr ihdr{};
  if (const auto error = spng_get_ihdr(ctx.get(), &ihdr); error != SPNG_OK) {
    throw std::runtime_error(
        fmt::format("[spng_get_ihdr] error while getting image information: {}, error: {}", filename, spng_strerror(error)));
  }

  const int format = SPNG_FMT_RGBA8;
  size_t length = 0;
  if (const auto error = spng_decoded_image_size(ctx.get(), format, &length);
      error != SPNG_OK) {
    throw std::runtime_error(
        fmt::format("[spng_decoded_image_size] error while getting image size: {}, error: {}", filename, spng_strerror(error)));
  }

  std::vector<uint8_t> output(length);
  if (const auto error = spng_decode_image(ctx.get(), output.data(), length, format, SPNG_DECODE_TRNS); error != SPNG_OK) {
    throw std::runtime_error(
        fmt::format("[spng_decode_image] error while decoding image: {}, error: {}", filename, spng_strerror(error)));
  }

  _size = geometry::size{ihdr.width, ihdr.height};

  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
      SDL_CreateRGBSurfaceWithFormat(
          0,
          _size.width(),
          _size.height(),
          0,
          SDL_PIXELFORMAT_ABGR8888),
      SDL_FreeSurface};
  if (!surface) {
    throw std::runtime_error(
        fmt::format("[SDL_CreateRGBSurfaceWithFormat] error while creating surface with format: {}, error {}", filename, SDL_GetError()));
  }

  std::memcpy(surface->pixels, output.data(), length);
  ctx.reset();

  _texture = texture_ptr(SDL_CreateTextureFromSurface(*renderer, surface.get()),
                         SDL_Deleter());
  if (!_texture) {
    throw std::runtime_error(
        fmt::format("[SDL_CreateTextureFromSurface] error while creating texture from surface: {}", filename));
  }
}

void pixmap::draw(
    const geometry::point &point,
    const double_t angle,
    flip flip,
    const uint8_t alpha) const {
  const SDL_Rect rect{
      point.x(),
      point.y(),
      static_cast<int>(_size.width()),
      static_cast<int>(_size.height())};

  SDL_SetTextureAlphaMod(_texture.get(), alpha);
  SDL_RenderCopyEx(*_renderer, _texture.get(), nullptr, &rect, angle, nullptr, static_cast<SDL_RendererFlip>(flip));
}

const geometry::size pixmap::size() const { return _size; }

void pixmap::set_size(const geometry::size &size) { _size = size; }
