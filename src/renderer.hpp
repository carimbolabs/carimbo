#pragma once
#ifndef _renderer_hpp
#define _renderer_hpp

#include "deleter.hpp"
#include "internal.hpp"

typedef std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer_ptr;

class renderer {
public:
  explicit renderer(SDL_Window *window);
  ~renderer() = default;

  operator const SDL_Renderer *() const;

private:
  renderer_ptr _renderer;
};

#endif