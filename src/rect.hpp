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

  void set_position(const point &position);

  const point position() const;

  void set_size(const geometry::size &size);

  const geometry::size size() const;

  void scale(float_t factor);

  operator SDL_Rect() const;

private:
  point _position;
  geometry::size _size;
};
}
