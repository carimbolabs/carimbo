#include "vector2d.hpp"
#include <cmath>

// Construtores
constexpr vector2d::vector2d() noexcept : x(0.0), y(0.0) {}

constexpr vector2d::vector2d(double_t x, double_t y) noexcept : x(x), y(y) {}

// Métodos getter
constexpr double_t vector2d::get_x() const noexcept { return x; }

constexpr double_t vector2d::get_y() const noexcept { return y; }

// Operadores Aritméticos
constexpr vector2d vector2d::operator+(const vector2d &other) const noexcept {
  return vector2d(x + other.x, y + other.y);
}

constexpr vector2d vector2d::operator-(const vector2d &other) const noexcept {
  return vector2d(x - other.x, y - other.y);
}

constexpr vector2d vector2d::operator*(double_t scalar) const noexcept {
  return vector2d(x * scalar, y * scalar);
}

constexpr vector2d vector2d::operator/(double_t scalar) const noexcept {
  return vector2d(x / scalar, y / scalar);
}

vector2d &vector2d::operator+=(const vector2d &other) noexcept {
  x += other.x;
  y += other.y;
  return *this;
}

vector2d &vector2d::operator-=(const vector2d &other) noexcept {
  x -= other.x;
  y -= other.y;
  return *this;
}

vector2d &vector2d::operator*=(double_t scalar) noexcept {
  x *= scalar;
  y *= scalar;
  return *this;
}

vector2d &vector2d::operator/=(double_t scalar) noexcept {
  x /= scalar;
  y /= scalar;
  return *this;
}

constexpr bool vector2d::operator==(const vector2d &other) const noexcept {
  return x == other.x && y == other.y;
}

constexpr bool vector2d::operator!=(const vector2d &other) const noexcept {
  return !(*this == other);
}

constexpr double_t vector2d::magnitude() const noexcept {
  return std::sqrt(x * x + y * y);
}

vector2d vector2d::unit() const noexcept {
  const auto m = magnitude();
  return (m == 0) ? vector2d(0, 0) : *this / m;
}

constexpr double_t vector2d::dot(const vector2d &other) const noexcept {
  return x * other.x + y * other.y;
}
