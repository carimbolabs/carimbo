#pragma once

#include "common.hpp"
#include "widget.hpp"

namespace graphics {
class overlay {
public:
  explicit overlay(std::shared_ptr<renderer> renderer);
  ~overlay() = default;

  void update(float_t delta) noexcept;

  void draw() const noexcept;

  void add(std::variant<std::shared_ptr<widget>, std::shared_ptr<label>> &&widget) noexcept;

  void remove(std::variant<std::shared_ptr<widget>, std::shared_ptr<label>> &&widget) noexcept;

private:
  std::shared_ptr<renderer> _renderer;
  std::list<std::shared_ptr<widget>> _widgets;
};
}
