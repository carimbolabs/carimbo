#pragma once
#ifndef _engine_hpp
#define _engine_hpp

#include "common.hpp"
#include "eventmanager.hpp"
#include "eventreceiver.hpp"
#include "framerate.hpp"
#include "loopable.hpp"
#include "noncopyable.hpp"
#include "renderer.hpp"
#include "window.hpp"

class motor : public eventreceiver, public std::enable_shared_from_this<motor> {
public:
  virtual ~motor() = default;

  static std::shared_ptr<motor> make();

  void init(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  void add_loopable(std::shared_ptr<loopable> loopable);

  void run();

protected:
  virtual void on_quit() override;

private:
  motor() = default;

  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
  std::shared_ptr<eventmanager> _eventmanager;
};

#endif