#pragma once

#include "common.hpp"

namespace geometry {
class point {
public:
  point() = default;
  point(const int32_t x, const int32_t y);
  point(const point &other);
  ~point() = default;

  int32_t x() const;
  void set_x(const int32_t x);

  int32_t y() const;
  void set_y(const int32_t y);

  operator SDL_Point() const;

private:
  int32_t _x;
  int32_t _y;
};
}
