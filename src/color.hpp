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

  [[nodiscard]] inline uint8_t r() const noexcept { return _r; }
  [[nodiscard]] inline uint8_t g() const noexcept { return _g; }
  [[nodiscard]] inline uint8_t b() const noexcept { return _b; }
  [[nodiscard]] inline uint8_t a() const noexcept { return _a; }

  inline void set_r(uint8_t r) noexcept { _r = r; }
  inline void set_g(uint8_t g) noexcept { _g = g; }
  inline void set_b(uint8_t b) noexcept { _b = b; }
  inline void set_a(uint8_t a) noexcept { _a = a; }

  bool operator==(const color &other) const noexcept;

  bool operator!=(const color &other) const noexcept;

  explicit operator SDL_Color() const noexcept;

private:
  uint8_t _r = 0;
  uint8_t _g = 0;
  uint8_t _b = 0;
  uint8_t _a = 255;
};
}
