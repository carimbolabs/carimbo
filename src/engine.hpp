#pragma once
#ifndef _engine_hpp
#define _engine_hpp

#include "common.hpp"
#include "framerate.hpp"
#include "loopable.hpp"
#include "noncopyable.hpp"
#include "renderer.hpp"
#include "window.hpp"

class engine : private noncopyable {
public:
  engine();
  ~engine() = default;

  void create(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  void add_loopable(std::shared_ptr<loopable> loopable);

  void run();

private:
  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
};

#endif