#pragma once

#include "common.hpp"

namespace geometry {
class size {
public:
  size() = default;
  size(int32_t width, int32_t height);
  size(const size &other);

  ~size() = default;

  void set_width(const int32_t width) noexcept;

  int32_t width() const noexcept;

  void set_height(const int32_t height) noexcept;

  int32_t height() const noexcept;

  bool operator==(const size &rhs) const noexcept;

  bool operator!=(const size &rhs) const noexcept;

private:
  int32_t _width;
  int32_t _height;
};
}
