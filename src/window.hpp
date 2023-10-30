#pragma once
#ifndef _window_hpp
#define _window_hpp

#include "common.hpp"
#include "renderer.hpp"

class window {
public:
  window(std::string_view title, uint64_t width, uint64_t height);
  ~window() = default;

  operator SDL_Window *();

  const std::shared_ptr<renderer> create_renderer() const;

private:
  std::unique_ptr<SDL_Window, SDL_Deleter> _window;
};

#endif