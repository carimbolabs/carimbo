#pragma once
#ifndef _eventmanager_hpp_
#define _eventmanager_hpp_

#include "common.hpp"

#include "noncopyable.hpp"

namespace input {
class eventmanager : private noncopyable {
public:
  eventmanager() = default;
  virtual ~eventmanager() = default;

  void update();

  void add_receiver(std::shared_ptr<eventreceiver> receiver);

  void remove_receiver(std::shared_ptr<eventreceiver> receiver);

private:
  std::list<std::shared_ptr<eventreceiver>> _receivers;
};
}

#endif