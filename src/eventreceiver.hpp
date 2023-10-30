#pragma once
#ifndef _eventreceiver_hpp
#define _eventreceiver_hpp

#include "common.hpp"

class eventreceiver {
public:
  eventreceiver() = default;
  virtual ~eventreceiver() = default;

  virtual void on_quit();

protected:
  // std::shared_ptr<eventmanager> _eventmanager;
};

#endif