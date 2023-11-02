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

class engine : public eventreceiver, public singleton<engine> {
public:
  virtual ~engine() = default;

  static std::shared_ptr<engine> create(const std::string &title, int32_t width, int32_t height, bool fullscreen);
  // engine();

  // static std::shared_ptr<motor> instance();

  // void ignite(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  void add_loopable(std::shared_ptr<loopable> loopable);

  void set_eventmanager(std::shared_ptr<eventmanager> eventmanager);

  const std::shared_ptr<eventmanager> get_eventmanager() const;

  void run();

protected:
  virtual void on_quit() override;

  virtual void on_keydown(const keyevent &event) override;

private:
  friend class enginefactory;

  engine(std::string_view title, int32_t width, int32_t height, bool fullscreen = false);

  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
  std::shared_ptr<eventmanager> _eventmanager;
};

#endif