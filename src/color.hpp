#pragma once

#include "common.hpp"

namespace graphics {
class color {
public:
  color() = default;
  color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  color(const SDL_Color &color);
  color(const std::string &hex);
  color(uint32_t pixel, const SDL_PixelFormat *format);
  ~color() = default;

  uint8_t r() const;
  uint8_t g() const;
  uint8_t b() const;
  uint8_t a() const;

  void set_r(uint8_t r);
  void set_g(uint8_t g);
  void set_b(uint8_t b);
  void set_a(uint8_t a);

  bool operator==(const color &other) const;

  bool operator!=(const color &other) const;

  operator SDL_Color() const;

private:
  uint8_t _r = 0;
  uint8_t _g = 0;
  uint8_t _b = 0;
  uint8_t _a = 255;
};
}
