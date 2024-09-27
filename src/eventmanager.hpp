#pragma once

#include "common.hpp"

#include "noncopyable.hpp"

typedef std::unique_ptr<SDL_GameController, SDL_Deleter> gamecontroller_ptr;

namespace input {
class eventmanager : private framework::noncopyable {
public:
  eventmanager();
  virtual ~eventmanager() = default;

  void update();

  void add_receiver(std::shared_ptr<eventreceiver> receiver);

  void remove_receiver(std::shared_ptr<eventreceiver> receiver);

private:
  std::list<std::shared_ptr<eventreceiver>> _receivers;

  std::unordered_map<SDL_JoystickID, gamecontroller_ptr> _controllers;
};
}
