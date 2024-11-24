#pragma once

#include "common.hpp"
#include "fontfactory.hpp"
#include "widget.hpp"

namespace graphics {
class overlay {
public:
  explicit overlay(std::shared_ptr<renderer> renderer);
  ~overlay() = default;

  void update(float_t delta) noexcept;

  void draw() const noexcept;

  std::shared_ptr<widget> create(widgettype type) noexcept;

  void destroy(std::shared_ptr<widget> widget) noexcept;

private:
  std::shared_ptr<renderer> _renderer;
  std::list<std::shared_ptr<widget>> _widgets;
};
}
