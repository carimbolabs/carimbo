#include "size.hpp"

using namespace geometry;

size::size(int32_t width, int32_t height) : _width(width), _height(height) {}

size::size(const size &other) : _width(other._width), _height(other._height) {}

void size::set_width(const int32_t width) { _width = width; }

int32_t size::width() const { return _width; }

void size::set_height(const int32_t height) { _height = height; }

int32_t size::height() const { return _height; }

bool size::operator==(const size &rhs) const {
  return _width == rhs._width && _height == rhs._height;
}

bool size::operator!=(const size &rhs) const {
  return !(*this == rhs);
}
