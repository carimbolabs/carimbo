#include "size.hpp"

size::size(uint32_t width, uint32_t height) : _width(width), _height(height) {}

size::size(const size &size) {
  _width = size._width;
  _height = size._height;
}

void size::set_width(const uint32_t width) {
  _width = width;
}

uint32_t size::get_width() const {
  return _width;
}

void size::set_height(const uint32_t height) {
  _height = height;
}

uint32_t size::get_height() const {
  return _height;
}