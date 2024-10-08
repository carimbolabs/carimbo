#include "point.hpp"

using namespace geometry;

point::point(int32_t x, int32_t y) noexcept : _x(x), _y(y) {}

point::point(const point &other) noexcept : _x(other.x()), _y(other.y()) {}

void point::set(int32_t x, int32_t y) noexcept {
  _x = x;
  _y = y;
}

int32_t point::x() const noexcept { return _x; }

void point::set_x(int32_t x) noexcept { _x = x; }

int32_t point::y() const noexcept { return _y; }

void point::set_y(int32_t y) noexcept { _y = y; }

point::operator SDL_Point() const noexcept { return SDL_Point{_x, _y}; }

point point::operator+(const point &other) const noexcept {
  return point(_x + other._x, _y + other._y);
}
