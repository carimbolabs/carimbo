#include "size.hpp"

size::size(uint32_t width, uint32_t height)
    : _width(width), _height(height) {}

size::size(const size &other)
    : _width(other._width), _height(other._height) {}

// size::size(size &&other) noexcept
//     : _width(std::move(other._width)), _height(std::move(other._height)) {}

void size::set_width(const uint32_t width) {
  _width = width;
}

uint32_t size::width() const {
  return _width;
}

void size::set_height(const uint32_t height) {
  _height = height;
}

uint32_t size::height() const {
  return _height;
}