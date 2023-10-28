#pragma once
#ifndef _pixmap_hpp
#define _pixmap_hpp

#include "deleter.hpp"
#include "file.hpp"
#include "internal.hpp"
#include "renderer.hpp"

typedef std::unique_ptr<SDL_Texture, SDL_Deleter> texture_ptr;

class pixmap {
public:
  pixmap(const std::shared_ptr<renderer> renderer, const std::string &filename);
  ~pixmap() = default;

  void draw(const int x, const int y) const;

  int width() const;

  int height() const;

private:
  std::shared_ptr<renderer> _renderer;

  int _width;
  int _height;
  texture_ptr _texture;
};

#endif