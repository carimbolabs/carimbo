#pragma once

#include "common.hpp"

namespace input {
class eventreceiver {
public:
  virtual ~eventreceiver() = default;

  virtual void on_quit() noexcept;
  virtual void on_keydown(const keyevent &event) noexcept;
  virtual void on_keyup(const keyevent &event) noexcept;
  virtual void on_mail(const mailevent &event) noexcept;
};
}
