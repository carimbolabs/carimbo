#pragma once
#ifndef _pixmap_hpp
#define _pixmap_hpp

#include "file.hpp"
#include "internal.hpp"
#include "renderer.hpp"

class pixmap {
public:
  pixmap(const std::shared_ptr<renderer> &renderer, const std::string &filename);
  ~pixmap() = default;

private:
  // inline static /*const*/ auto *decoder = avifDecoderCreate();
};

#endif