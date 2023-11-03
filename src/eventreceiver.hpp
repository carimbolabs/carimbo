#pragma once
#ifndef _eventreceiver_hpp
#define _eventreceiver_hpp

#include "common.hpp"

#include "event.hpp"

class eventreceiver {
public:
  eventreceiver() = default;
  virtual ~eventreceiver() = default;

  virtual void on_quit();

  virtual void on_keydown(const keyevent &event);

  virtual void on_keyup(const keyevent &event);

protected:
  // std::shared_ptr<eventmanager> _eventmanager;
};

#endif