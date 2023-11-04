#pragma once
#ifndef _pixmap_hpp
#define _pixmap_hpp

#include "common.hpp"

typedef std::unique_ptr<SDL_Texture, SDL_Deleter> texture_ptr;

enum class flip : int32_t {
  none = SDL_FLIP_NONE,
  horizontal = SDL_FLIP_HORIZONTAL,
  vertical = SDL_FLIP_VERTICAL,
  both = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
};

class pixmap {
public:
  pixmap(const std::shared_ptr<renderer> renderer, std::string_view filename);
  ~pixmap() = default;

  void draw(const int x, const int y, const double angle = 0.0) const;

  int width() const;

  int height() const;

private:
  std::shared_ptr<renderer> _renderer;

  int _width;
  int _height;
  texture_ptr _texture;
};

#endif