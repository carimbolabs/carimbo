#pragma once
#ifndef _rect_hpp
#define _rect_hpp

#include "common.hpp"

class rect {
public:
  rect() = default;
  rect(const point &position, const size &size);
  rect(const rect &other) = default;
  ~rect() = default;

private:
  point _position;
  size _size;
};

#endif
