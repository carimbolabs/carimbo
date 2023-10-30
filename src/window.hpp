#pragma once
#ifndef _window_hpp
#define _window_hpp

#include "common.hpp"
#include "renderer.hpp"

class window {
public:
  window(std::string_view title, int32_t width, int32_t height, bool fullscreen);
  ~window() = default;

  operator SDL_Window *();

  const std::shared_ptr<renderer> create_renderer() const;

private:
  std::unique_ptr<SDL_Window, SDL_Deleter> _window;
};

#endif