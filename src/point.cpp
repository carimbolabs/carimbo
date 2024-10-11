#include "point.hpp"

using namespace geometry;

point::point(int32_t x, int32_t y) : _x(x), _y(y) {}

point::point(const point &other) : _x(other.x()), _y(other.y()) {}

void point::set(int32_t x, int32_t y) {
  _x = x;
  _y = y;
}

int32_t point::x() const { return _x; }

void point::set_x(int32_t x) { _x = x; }

int32_t point::y() const { return _y; }

void point::set_y(int32_t y) { _y = y; }

point::operator SDL_Point() const { return SDL_Point{_x, _y}; }

point point::operator+(const point &other) const {
  return point(_x + other._x, _y + other._y);
}
