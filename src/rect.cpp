#include "rect.hpp"

#include "point.hpp"
#include "size.hpp"

using namespace geometry;

rect::rect(const ::point &position, const ::size &size) : _position(position), _size(size) {}

void rect::set_position(const ::point &position) {
  _position = position;
}

const ::point rect::position() const {
  return _position;
}

void rect::set_size(const ::size &size) {
  _size = size;
}

const ::size rect::size() const {
  return _size;
}