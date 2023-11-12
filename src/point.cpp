#include "point.hpp"

point::point(const int32_t x, const int32_t y) : _x(x), _y(y) {
}

point::point(const point &other) : _x(other.x()), _y(other.y()) {}

int32_t point::x() const {
  return _x;
}

void point::set_x(const int32_t x) {
  _x = x;
}

int32_t point::y() const {
  return _y;
}

void point::set_y(const int32_t y) {
  _y = y;
}

point::operator SDL_Point() const {
  return SDL_Point{_x, _y};
}
