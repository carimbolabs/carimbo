#pragma once
#ifndef _pixmap_hpp
#define _pixmap_hpp

#include "file.hpp"
#include "internal.hpp"
#include "renderer.hpp"

class pixmap {
public:
  pixmap(const std::shared_ptr<renderer> r, const std::string &filename);
  ~pixmap() = default;

  // void draw(const std::shared_ptr<renderer> renderer, const int64_t x, const int64_t y) const;

  // uint64_t width() const;

  // uint64_t height() const;
};

#endif