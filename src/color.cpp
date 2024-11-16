#include "color.hpp"

using namespace graphics;

color::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _r(r), _g(g), _b(b), _a(a) {}

color::color(const SDL_Color &scolor)
    : color(scolor.r, scolor.g, scolor.b, scolor.a) {}

color::color(const std::string &hex) : color(0, 0, 0, 255) {
  if (hex.length() == 7 || hex.length() == 9) {
    if (hex[0] != '#') {
      throw std::invalid_argument("Hex code must start with '#'");
    }

    _r = static_cast<uint8_t>(std::stoi(hex.substr(1, 2), nullptr, 16));
    _g = static_cast<uint8_t>(std::stoi(hex.substr(3, 2), nullptr, 16));
    _b = static_cast<uint8_t>(std::stoi(hex.substr(5, 2), nullptr, 16));
    _a = (hex.length() == 9) ? static_cast<uint8_t>(std::stoi(hex.substr(7, 2), nullptr, 16)) : 255;
  } else {
    throw std::invalid_argument("Invalid hex code format. Use #RRGGBB or #RRGGBBAA.");
  }
}

color::color(uint32_t pixel, const SDL_PixelFormat *format) {
  uint8_t r, g, b, a;
  SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
  _r = r;
  _g = g;
  _b = b;
  _a = a;
}

bool color::operator==(const color &other) const noexcept {
  return std::tie(_r, _g, _b, _a) == std::tie(other._r, other._g, other._b, other._a);
}

bool color::operator!=(const color &other) const noexcept {
  return !(*this == other);
}

color::operator SDL_Color() const noexcept {
  return SDL_Color{_r, _g, _b, _a};
}
