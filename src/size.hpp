#pragma once

#include "common.hpp"

namespace geometry {
class size {
public:
  size() = default;
  size(int32_t width, int32_t height);
  size(const size &other);

  ~size() = default;

  void set_width(const int32_t width);

  int32_t width() const;

  void set_height(const int32_t height);

  int32_t height() const;

  bool operator==(const size &rhs) const;

  bool operator!=(const size &rhs) const;

private:
  int32_t _width;
  int32_t _height;
};
}
