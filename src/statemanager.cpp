#include "statemanager.hpp"

#include "event.hpp"
#include "eventreceiver.hpp"

using namespace framework;

bool statemanager::is_keydown(const input::keyevent &event) const {
  const auto it = _keys.find(event);
  return it != _keys.end() && it->second;
}

void statemanager::on_keydown(const input::keyevent &event) {
  _keys[event] = true;
}

void statemanager::on_keyup(const input::keyevent &event) {
  _keys[event] = false;
}