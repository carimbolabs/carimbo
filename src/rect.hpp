#pragma once

#include "common.hpp"
#include "size.hpp"

namespace geometry {
class rect {
public:
  rect() = default;
  rect(const point &position, const size &size);
  rect(const rect &other) = default;
  ~rect() = default;

  void set_position(const point &position) noexcept;

  const point position() const noexcept;

  void set_size(const geometry::size &size) noexcept;

  const geometry::size size() const noexcept;

  void scale(float_t factor) noexcept;

  operator SDL_Rect() const noexcept;

private:
  point _position;
  geometry::size _size;
};
}
