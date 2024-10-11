#pragma once

#include <cmath>
class vector2d {
public:
  vector2d();
  vector2d(double_t x, double_t y);

  double_t x() const;
  double_t y() const;

  void set_x(double_t x);
  void set_y(double_t y);

  vector2d operator+(const vector2d &other) const;
  vector2d operator-(const vector2d &other) const;
  vector2d operator*(double scalar) const;
  vector2d operator/(double scalar) const;

  vector2d &operator+=(const vector2d &other);
  vector2d &operator-=(const vector2d &other);
  vector2d &operator*=(double scalar);
  vector2d &operator/=(double scalar);

  bool operator==(const vector2d &other) const;
  bool operator!=(const vector2d &other) const;

  double_t magnitude() const;

  vector2d unit() const;

  double_t dot(const vector2d &other) const;

  bool moving() const;
  bool right() const;
  bool left() const;
  bool zero() const;

private:
  double_t _x, _y;
};
