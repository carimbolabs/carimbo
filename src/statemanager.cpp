#include "statemanager.hpp"

#include "event.hpp"

using namespace framework;

bool statemanager::is_keydown(const input::keyevent &event) const {
  const auto it = _keys.find(event);
  return it != _keys.end() && it->second;
}

void statemanager::on_keydown(const input::keyevent &event) noexcept {
  _keys.emplace(event, true).first->second = true;
}

void statemanager::on_keyup(const input::keyevent &event) noexcept {
  if (auto it = _keys.find(event); it != _keys.end()) {
    it->second = false;
  }
}
