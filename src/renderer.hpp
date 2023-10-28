#pragma once
#ifndef _renderer_hpp
#define _renderer_hpp

#include "deleter.hpp"
#include "internal.hpp"

typedef std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer_ptr;

class renderer {
public:
  renderer(SDL_Window *window);
  ~renderer();

  void render();

private:
  renderer_ptr _renderer;
};

#endif