#pragma once
#ifndef _size_hpp
#define _size_hpp

#include "common.hpp"

class size {
public:
  size() = default;
  size(uint32_t width, uint32_t height);
  size(const size &size);
  virtual ~size() = default;

  void set_width(const uint32_t width);

  uint32_t get_width() const;

  void set_height(const uint32_t height);

  uint32_t get_height() const;

private:
  uint32_t _width;
  uint32_t _height;
};

#endif