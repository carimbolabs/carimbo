#include "color.hpp"

using namespace graphics;

color::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _r(r), _g(g), _b(b), _a(a) {}

color::color(const SDL_Color &color)
    : _r(color.r), _g(color.g), _b(color.b), _a(color.a) {}

color::color(const std::string &hex) {
  auto to_uint8 = [](const std::string &hex) -> uint8_t {
    unsigned int value;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> value;
    return static_cast<uint8_t>(value);
  };

  if (hex.length() == 7 || hex.length() == 9) {
    if (hex[0] != '#') {
      throw std::invalid_argument("Hex code must start with '#'");
    }
    _r = to_uint8(hex.substr(1, 2));
    _g = to_uint8(hex.substr(3, 2));
    _b = to_uint8(hex.substr(5, 2));

    if (hex.length() == 9) {
      _a = to_uint8(hex.substr(7, 2));
    } else {
      _a = 255;
    }
  } else {
    throw std::invalid_argument("Invalid hex code format. Use #RRGGBB or #RRGGBBAA.");
  }
}

uint8_t color::r() const { return _r; }
uint8_t color::g() const { return _g; }
uint8_t color::b() const { return _b; }
uint8_t color::a() const { return _a; }

void color::set_r(uint8_t r) { _r = r; }
void color::set_g(uint8_t g) { _g = g; }
void color::set_b(uint8_t b) { _b = b; }
void color::set_a(uint8_t a) { _a = a; }

bool color::operator==(const color &other) const {
  return _r == other._r && _g == other._g && _b == other._b && _a == other._a;
}

bool color::operator!=(const color &other) const {
  return !(*this == other);
}

color::operator SDL_Color() const {
  return SDL_Color{_r, _g, _b, _a};
}
