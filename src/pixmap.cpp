#include "pixmap.hpp"

struct SDL_SurfaceDeleter {
  void operator()(SDL_Surface *ptr) {
    SDL_FreeSurface(ptr);
  }
};

pixmap::pixmap(const std::shared_ptr<renderer> r, const std::string &filename) {
  const auto buffer = file::read(filename);
  const auto decoder = avifDecoderCreate();
  avifRGBImage rgb{};

  if (avifDecoderSetIOMemory(decoder, reinterpret_cast<const uint8_t *>(&buffer[0]), buffer.size()) != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderSetIOMemory] Error while setting IO on avifDecoder: {}", filename));
  }

  if (avifDecoderParse(decoder) != AVIF_RESULT_OK) {
    throw std::runtime_error(fmt::format("[avifDecoderParse] Error while parsing avifDecoder: {}", filename));
  }

  while (avifDecoderNextImage(decoder) == AVIF_RESULT_OK) {
    avifRGBImageSetDefaults(&rgb, decoder->image);

    if (avifRGBImageAllocatePixels(&rgb) != AVIF_RESULT_OK) {
      avifRGBImageFreePixels(&rgb);
      avifDecoderDestroy(decoder);
      throw std::runtime_error(fmt::format("[avifRGBImageAllocatePixels] Error while allocating pixels on avifRGBImage: {}", filename));
    }

    if (avifImageYUVToRGB(decoder->image, &rgb) != AVIF_RESULT_OK) {
      avifRGBImageFreePixels(&rgb);
      avifDecoderDestroy(decoder);
      throw std::runtime_error(fmt::format("[avifImageYUVToRGB] Error while converting YUV to RGB on avifImage: {}", filename));
    }

    const auto surface = SDL_CreateRGBSurfaceWithFormatFrom(rgb.pixels, rgb.width, rgb.height, 32, rgb.rowBytes, SDL_PIXELFORMAT_RGBA32);
    const auto texture = SDL_CreateTextureFromSurface(*r, surface);

    // const auto surface = SDL_CreateRGBSurfaceWithFormatFrom(rgb.pixels, rgb.width, rgb.height, 32, rgb.rowBytes, SDL_PIXELFORMAT_RGBA32);

    // std::shared_ptr<SDL_Surface, SDL_SurfaceDeleter> surface{SDL_CreateRGBSurfaceWithFormatFrom(rgb.pixels, rgb.width, rgb.height, 32, rgb.rowBytes, SDL_PIXELFORMAT_RGBA32)};
    /*
    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> surf{SDL_CreateRGBSurfaceWithFormatFrom(
      const_cast<uint8_t*>(image.data.data()),
      image.width,
      image.height,
      SDL_BITSPERPIXEL(sdlformat), // depth
      image.width * SDL_BYTESPERPIXEL(sdlformat), // pitch
      sdlformat)};
    assert(surf);
  */
    // const auto surface = std::make_shared<SDL_Surface>(SDL_CreateRGBSurfaceWithFormatFrom(rgb.pixels, rgb.width, rgb.height, 32, rgb.rowBytes, SDL_PIXELFORMAT_RGBA32), SDL_FreeSurface);
    //  const auto texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    //  const auto texture = renderer.get()->create_texture_from_surface(surface);

    // SDL_FreeSurface(surface);
    avifRGBImageFreePixels(&rgb);
    avifDecoderDestroy(decoder);

    // if (FAILED(rwops = PHYSFSRWOPS_openRead(filename.c_str()))) {
    //  throw Exception("[PHYSFSRWOPS_openRead] Error while opening file: %s", filename.c_str());
    //}

    // shared_ptr<SDL_Texture>(tex, SDL_DestroyTexture)
    // auto *image = avifImageCreateEmpty();
    // auto *reader = avifDecoderCreate();
    // auto *raw = avifRawDataCreate();

    // avifResult result = avifDecoderRead(reader, raw, image);

    // if (result == AVIF_RESULT_OK) {
    //   auto *frame = image->frames[0];

    //   auto *buffer = frame->pixels;

    //   auto *texture = SDL_CreateTexture(renderer->get(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, frame->width, frame->height);

    //   void *pixels;
    //   int pitch;

    //   SDL_LockTexture(texture, nullptr, &pixels, &pitch);

    //   memcpy(pixels, buffer, pitch * frame->height);

    //   SDL_UnlockTexture(texture);

    //   _texture = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    // }

    // avifRawDataFree(raw);
    // avifDecoderDestroy(reader);
    // avifImageDestroy(image);
  }
}