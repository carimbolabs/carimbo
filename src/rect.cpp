#include "rect.hpp"

#include "point.hpp"

rect::rect(const point &position, const point &size) : _position(position), _size(size) {}
rect::rect(const point &position, const int &width, const int &height) : _position(position), _size(width, height) {}