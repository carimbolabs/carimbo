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
#include "singleton.hpp"
#include "window.hpp"

class motor : public eventreceiver, public singleton<motor> {
public:
  virtual ~motor() = default;

  // static std::shared_ptr<motor> instance();

  void init(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  void add_loopable(std::shared_ptr<loopable> loopable);

  const std::shared_ptr<eventmanager> get_eventmanager() const;

  void run();

protected:
  virtual void on_quit() override;

  virtual void on_keydown(const keyevent &event) override;

private:
  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
  std::shared_ptr<eventmanager> _eventmanager;
};

#endif