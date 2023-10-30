#pragma once
#ifndef _renderer_hpp
#define _renderer_hpp

#include "common.hpp"

class renderer {
public:
  explicit renderer(SDL_Window *window);
  ~renderer() = default;

  operator SDL_Renderer *();

  void begin_draw();

  void end_draw();

private:
  std::unique_ptr<SDL_Renderer, SDL_Deleter> _renderer;

  uint32_t _time;
};

#endif