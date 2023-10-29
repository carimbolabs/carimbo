#pragma once
#ifndef _window_hpp
#define _window_hpp

#include "common.hpp"

class window {
public:
  window(const std::string &title, uint64_t width, uint64_t height);
  ~window();

  const std::shared_ptr<renderer> create_renderer() const;

private:
  SDL_Window *_window;
};

#endif