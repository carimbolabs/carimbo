#pragma once
#ifndef _engine_hpp
#define _engine_hpp

#include "common.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "eventreceiver.hpp"
#include "framerate.hpp"
#include "loopable.hpp"
#include "noncopyable.hpp"
#include "renderer.hpp"
#include "singleton.hpp"
#include "window.hpp"

class engine : public eventreceiver {
public:
  virtual ~engine() = default;
  engine();

  void set_window(std::shared_ptr<window> window);

  const std::shared_ptr<window> get_window() const;

  void set_renderer(std::shared_ptr<renderer> renderer);

  const std::shared_ptr<renderer> get_renderer() const;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager);

  const std::shared_ptr<entitymanager> get_entitymanager() const;

  const std::shared_ptr<entity> spawn();

  void set_eventmanager(std::shared_ptr<eventmanager> eventmanager);

  const std::shared_ptr<eventmanager> get_eventmanager() const;

  void add_loopable(std::shared_ptr<loopable> loopable);

  void run();

protected:
  virtual void on_quit() override;

  virtual void on_keydown(const keyevent &event) override;

private:
  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<window> _window;
  std::shared_ptr<renderer> _renderer;
  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<eventmanager> _eventmanager;
};

#endif