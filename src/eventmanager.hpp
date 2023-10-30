#pragma once
#ifndef _eventmanager_hpp_
#define _eventmanager_hpp_

#include "common.hpp"
#include "noncopyable.hpp"

class eventmanager : private noncopyable {
public:
  eventmanager() = default;
  ~eventmanager() = default;

  void update();

  // void add_listener(std::shared_pre<eventlistener> listener);
  // void remove_listener(std::function<eventlistener> listener);
};

#endif