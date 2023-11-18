#include "rect.hpp"

#include "point.hpp"
#include "size.hpp"

using namespace geometry;

rect::rect(const point &position, const size &size) : _position(position), _size(size) {}