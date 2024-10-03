#include "vector2d.hpp"
#include <cmath>

vector2d::vector2d() noexcept : _x(.0), _y(.0) {}

vector2d::vector2d(double_t x, double_t y) noexcept : _x(x), _y(y) {}

double_t vector2d::x() const noexcept { return _x; }

double_t vector2d::y() const noexcept { return _y; }

void vector2d::set_x(double_t x) noexcept { _x = x; }

void vector2d::set_y(double_t y) noexcept { _y = y; }

vector2d vector2d::operator+(const vector2d &other) const noexcept {
  return vector2d(_x + other._x, _y + other._y);
}

vector2d vector2d::operator-(const vector2d &other) const noexcept {
  return vector2d(_x - other._x, _y - other._y);
}

vector2d vector2d::operator*(double_t scalar) const noexcept {
  return vector2d(_x * scalar, _y * scalar);
}

vector2d vector2d::operator/(double_t scalar) const noexcept {
  return vector2d(_x / scalar, _y / scalar);
}

vector2d &vector2d::operator+=(const vector2d &other) noexcept {
  _x += other._x;
  _y += other._y;
  return *this;
}

vector2d &vector2d::operator-=(const vector2d &other) noexcept {
  _x -= other._x;
  _y -= other._y;
  return *this;
}

vector2d &vector2d::operator*=(double_t scalar) noexcept {
  _x *= scalar;
  _y *= scalar;
  return *this;
}

vector2d &vector2d::operator/=(double_t scalar) noexcept {
  _x /= scalar;
  _y /= scalar;
  return *this;
}

bool vector2d::operator==(const vector2d &other) const noexcept {
  return _x == other._x && _y == other._y;
}

bool vector2d::operator!=(const vector2d &other) const noexcept {
  return !(*this == other);
}

double_t vector2d::magnitude() const noexcept {
  return std::sqrt(_x * _x + _y * _y);
}

vector2d vector2d::unit() const noexcept {
  const auto m = magnitude();
  return (m == 0) ? vector2d(0, 0) : *this / m;
}

double_t vector2d::dot(const vector2d &other) const noexcept {
  return _x * other._x + _y * other._y;
}

bool vector2d::stationary() const noexcept {
  return _x == 0.0 && _y == 0.0;
}

bool vector2d::moving() const noexcept {
  return !stationary();
}

bool vector2d::right() const noexcept {
  return _x > 0;
}

bool vector2d::left() const noexcept {
  return _x < 0;
}
