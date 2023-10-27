#pragma once
#ifndef _pixmap_hpp
#define _pixmap_hpp

#include "internal.hpp"

class pixmap {
public:
  pixmap(const std::string &filename);
  ~pixmap() = default;

  // void load(const std::string &filename);
private:
  inline static const auto *decoder = avifDecoderCreate();
};

#endif