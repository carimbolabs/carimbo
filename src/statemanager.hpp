#pragma once
#ifndef _statemanager_hpp
#define _statemanager_hpp

#include "common.hpp"

class statemanager : public eventreceiver {
public:
  statemanager() = default;
  virtual ~statemanager() = default;

  const bool is_keydown(const keyevent &event) const;

protected:
  virtual void on_keydown(const keyevent &event);

  virtual void on_keyup(const keyevent &event);

private:
  std::map<keyevent, bool> _keys;
};

#endif
