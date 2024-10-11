#pragma once

#include "common.hpp"

namespace geometry {
class point {
public:
  point() = default;
  point(int32_t x, int32_t y);
  point(const point &other);
  ~point() = default;

  void set(int32_t x, int32_t y);

  int32_t x() const;
  void set_x(int32_t x);

  int32_t y() const;
  void set_y(int32_t y);

  operator SDL_Point() const;

  point operator+(const point &other) const;

private:
  int32_t _x;
  int32_t _y;
};
}
