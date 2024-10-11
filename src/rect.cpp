#include "rect.hpp"

#include "point.hpp"
#include "size.hpp"

using namespace geometry;

rect::rect(const ::point &position, const ::size &size)
    : _position(position), _size(size) {}

void rect::set_position(const ::point &position) { _position = position; }

const ::point rect::position() const { return _position; }

void rect::set_size(const geometry::size &size) { _size = size; }

const geometry::size rect::size() const { return _size; }

void rect::scale(float_t factor) {
  _size.set_width(static_cast<int>(_size.width() * factor));
  _size.set_height(static_cast<int>(_size.height() * factor));
}

rect::operator SDL_Rect() const {
  return {static_cast<int>(_position.x()),
          static_cast<int>(_position.y()),
          static_cast<int>(_size.width()),
          static_cast<int>(_size.height())};
}
