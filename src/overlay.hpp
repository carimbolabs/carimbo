#pragma once

#include "common.hpp"
#include "widget.hpp"

namespace graphics {
class overlay {
public:
  overlay() = default;
  ~overlay() = default;

  void add(std::shared_ptr<widget> widget) noexcept;

  void remove(std::shared_ptr<widget> widget) noexcept;

  void update(float_t delta) noexcept;

  void draw() const noexcept;

private:
  std::list<std::shared_ptr<widget>> _widgets;
};
}
