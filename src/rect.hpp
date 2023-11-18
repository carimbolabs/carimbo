#pragma once
#ifndef _rect_hpp
#define _rect_hpp

#include "common.hpp"

namespace geometry {
class rect {
public:
  rect() = default;
  rect(const point &position, const size &size);
  rect(const rect &other) = default;
  ~rect() = default;

  void set_position(const point &position);

  const point position() const;

  void set_size(const size &size);

  const size size() const;

private:
  point _position;
  class size _size;
};
}

#endif
