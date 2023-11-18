#pragma once
#ifndef _size_hpp
#define _size_hpp

#include "common.hpp"

namespace geometry {
class size {
public:
  size() = default;
  size(uint32_t width, uint32_t height);
  size(const size &other);
  // size(size &&other) noexcept;
  virtual ~size() = default;

  void set_width(const uint32_t width);

  uint32_t width() const;

  void set_height(const uint32_t height);

  uint32_t height() const;

private:
  uint32_t _width;
  uint32_t _height;
};
} // namespace geometry

#endif