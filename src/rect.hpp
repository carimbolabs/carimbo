#pragma once
#ifndef _rect_hpp
#define _rect_hpp

#include "common.hpp"

class rect {
public:
  rect() = default;
  rect(const point &position, const point &size);
  rect(const point &position, const int &width, const int &height);
  rect(const rect &other) = default;
  ~rect() = default;

private:
  point _position;
  point _size;
};

#endif
