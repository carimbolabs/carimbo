#pragma once

#include "common.hpp"

namespace framework {
class statemanager : public input::eventreceiver {
public:
  statemanager() = default;
  virtual ~statemanager() = default;

  bool is_keydown(const input::keyevent &event) const;

protected:
  virtual void on_keydown(const input::keyevent &event);

  virtual void on_keyup(const input::keyevent &event);

private:
  std::unordered_map<input::keyevent, bool> _keys;
};
}
