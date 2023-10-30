#pragma once
#ifndef _eventmanager_hpp_
#define _eventmanager_hpp_

#include "common.hpp"
#include "noncopyable.hpp"

class event_manager : private noncopyable {
public:
  event_manager() = default;
  ~event_manager() = default;

  // void add_listener(std::shared_pre<eventlistener> listener);
  // void remove_listener(std::function<eventlistener> listener);
};

#endif