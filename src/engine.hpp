#pragma once
#ifndef _engine_hpp
#define _engine_hpp

#include "common.hpp"
#include "loopable.hpp"
#include "renderer.hpp"
#include "window.hpp"

class engine {
public:
  engine();
  ~engine() = default;

  void create_window(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  void add_loopable(const loopable &loopable, const uint64_t priority);

  void run();

private:
  bool _running;

  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
};

#endif