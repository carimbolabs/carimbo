#include "statemanager.hpp"

const bool statemanager::is_keydown(const keyevent &event) const {
  const auto it = _keys.find(event);
  return it != _keys.end() && it->second;
}

void statemanager::on_keydown(const keyevent &event) {
  _keys[event] = true;
}