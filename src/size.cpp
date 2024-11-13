#include "size.hpp"

using namespace geometry;

size::size(int32_t width, int32_t height) noexcept : _width(width), _height(height) {}

size::size(float_t scale, int32_t width, int32_t height) noexcept : _scale(scale), _width(width), _height(height) {}

size::size(const size &other) noexcept : _scale(other._scale), _width(other._width), _height(other._height) {}

void size::set_scale(float_t scale) noexcept { _scale = scale; }
float_t size::scale() const noexcept { return _scale; }

void size::set_width(int32_t width) noexcept { _width = width; }

int32_t size::width() const noexcept { return _width; }

void size::set_height(int32_t height) noexcept { _height = height; }

int32_t size::height() const noexcept { return _height; }

size size::resized() const noexcept {
  return {
      static_cast<int32_t>(std::round(_width * _scale)),
      static_cast<int32_t>(std::round(_height * _scale))
  };
}

bool size::operator==(const size &rhs) const noexcept {
  return _width == rhs._width && _height == rhs._height;
}

bool size::operator!=(const size &rhs) const noexcept {
  return !(*this == rhs);
}
