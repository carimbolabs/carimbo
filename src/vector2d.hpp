#pragma once

class vector2d {
public:
  constexpr vector2d() noexcept;
  constexpr vector2d(double_t x, double_t y) noexcept;

  constexpr double_t get_x() const noexcept;
  constexpr double_t get_y() const noexcept;

  constexpr vector2d operator+(const vector2d &other) const noexcept;
  constexpr vector2d operator-(const vector2d &other) const noexcept;
  constexpr vector2d operator*(double scalar) const noexcept;
  constexpr vector2d operator/(double scalar) const noexcept;

  vector2d &operator+=(const vector2d &other) noexcept;
  vector2d &operator-=(const vector2d &other) noexcept;
  vector2d &operator*=(double scalar) noexcept;
  vector2d &operator/=(double scalar) noexcept;

  constexpr bool operator==(const vector2d &other) const noexcept;
  constexpr bool operator!=(const vector2d &other) const noexcept;

  constexpr double_t magnitude() const noexcept;

  vector2d unit() const noexcept;

  constexpr double_t dot(const vector2d &other) const noexcept;

private:
  double_t x, y;
};
