#pragma once

#include "common.hpp"

#include "event.hpp"

namespace input {
class eventreceiver {
public:
  virtual ~eventreceiver() = default;

  virtual void on_quit();

  virtual void on_keydown(const keyevent &event);

  virtual void on_keyup(const keyevent &event);

  virtual void on_mail(const mailevent &event);
};
}
