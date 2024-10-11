#include "vector2d.hpp"
#include <cmath>

vector2d::vector2d() : _x(.0), _y(.0) {}

vector2d::vector2d(double_t x, double_t y) : _x(x), _y(y) {}

double_t vector2d::x() const { return _x; }

double_t vector2d::y() const { return _y; }

void vector2d::set_x(double_t x) { _x = x; }

void vector2d::set_y(double_t y) { _y = y; }

vector2d vector2d::operator+(const vector2d &other) const {
  return vector2d(_x + other._x, _y + other._y);
}

vector2d vector2d::operator-(const vector2d &other) const {
  return vector2d(_x - other._x, _y - other._y);
}

vector2d vector2d::operator*(double_t scalar) const {
  return vector2d(_x * scalar, _y * scalar);
}

vector2d vector2d::operator/(double_t scalar) const {
  return vector2d(_x / scalar, _y / scalar);
}

vector2d &vector2d::operator+=(const vector2d &other) {
  _x += other._x;
  _y += other._y;
  return *this;
}

vector2d &vector2d::operator-=(const vector2d &other) {
  _x -= other._x;
  _y -= other._y;
  return *this;
}

vector2d &vector2d::operator*=(double_t scalar) {
  _x *= scalar;
  _y *= scalar;
  return *this;
}

vector2d &vector2d::operator/=(double_t scalar) {
  _x /= scalar;
  _y /= scalar;
  return *this;
}

bool vector2d::operator==(const vector2d &other) const {
  return _x == other._x && _y == other._y;
}

bool vector2d::operator!=(const vector2d &other) const {
  return !(*this == other);
}

double_t vector2d::magnitude() const {
  return std::sqrt(_x * _x + _y * _y);
}

vector2d vector2d::unit() const {
  const auto m = magnitude();
  return (m == 0) ? vector2d(0, 0) : *this / m;
}

double_t vector2d::dot(const vector2d &other) const {
  return _x * other._x + _y * other._y;
}

bool vector2d::moving() const {
  return !zero();
}

bool vector2d::right() const {
  return _x > 0;
}

bool vector2d::left() const {
  return _x < 0;
}

bool vector2d::zero() const {
  return _x == 0.0 && _y == 0.0;
}
