#include "pixmap.hpp"

pixmap::pixmap(const std::string &filename) {
  // avifResult result = avifDecoderSetIOFile(decoder, filename.c_str());
  // if (result != AVIF_RESULT_OK) {
  //   throw std::runtime_error("Failed to open file");
  // }
  // result = avifDecoderParse(decoder);
  // if (result != AVIF_RESULT_OK) {
  //   throw std::runtime_error("Failed to parse file");
  // }
  // result = avifDecoderNextImage(decoder);
  // if (result != AVIF_RESULT_OK) {
  //   throw std::runtime_error("Failed to decode image");
  // }
  // avifRGBImage rgb;
  // avifRGBImageSetDefaults(&rgb, decoder->image);
  // rgb.format = AVIF_RGB_FORMAT_RGBA;
  // rgb.depth = 8;
  // rgb.ignoreAlpha = false;
  // avifResult rgbResult = avifImageYUVToRGB(decoder->image, &rgb);
  // if (rgbResult != AVIF_RESULT_OK) {
  //   throw std::runtime_error("Failed to convert image to RGB");
  // }
  // width = rgb.width;
  // height = rgb.height;
  // pixels = new uint32_t[width * height];
  // memcpy(pixels, rgb.pixels, width * height * sizeof(uint32_t));
  // avifRGBImageFreePixels(&rgb);
  // avifDecoderDestroy(decoder);
}