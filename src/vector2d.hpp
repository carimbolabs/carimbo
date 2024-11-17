#pragma once

#include "common.hpp"

namespace math {
class vector2d {
public:
  vector2d() noexcept;
  vector2d(double_t x, double_t y) noexcept;

  double_t x() const noexcept;
  double_t y() const noexcept;

  void set_x(double_t x) noexcept;
  void set_y(double_t y) noexcept;

  vector2d operator+(const vector2d &other) const noexcept;
  vector2d operator-(const vector2d &other) const noexcept;
  vector2d operator*(double_t scalar) const noexcept;
  vector2d operator/(double_t scalar) const noexcept;

  vector2d &operator+=(const vector2d &other) noexcept;
  vector2d &operator-=(const vector2d &other) noexcept;
  vector2d &operator*=(double_t scalar) noexcept;
  vector2d &operator/=(double_t scalar) noexcept;

  bool operator==(const vector2d &other) const noexcept;
  bool operator!=(const vector2d &other) const noexcept;

  double_t magnitude() const noexcept;

  vector2d unit() const noexcept;

  double_t dot(const vector2d &other) const noexcept;

  bool moving() const noexcept;
  bool right() const noexcept;
  bool left() const noexcept;
  bool zero() const noexcept;

private:
  double_t _x;
  double_t _y;
};
}
