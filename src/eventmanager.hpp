#pragma once
#ifndef _eventmanager_hpp_
#define _eventmanager_hpp_

#include "common.hpp"

#include "noncopyable.hpp"

class eventmanager : private noncopyable {
public:
  eventmanager() = default;
  virtual ~eventmanager() = default;

  void update();

  void add_receiver(std::shared_ptr<eventreceiver> receiver);

  void remove_receiver(std::shared_ptr<eventreceiver> receiver);

  // void add_listener(std::shared_pre<eventlistener> listener);
  // void remove_listener(std::function<eventlistener> listener);
private:
  std::list<std::shared_ptr<eventreceiver>> _receivers;
};

#endif