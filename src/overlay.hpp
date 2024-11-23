#pragma once

#include "common.hpp"
#include "fontfactory.hpp"
#include "widget.hpp"

namespace graphics {
class overlay {
public:
  overlay(std::shared_ptr<renderer> renderer) : _renderer(std::move(renderer)) {
    auto ff = fontfactory(_renderer);
    _font = ff.get("fonts/fixedsys.json");
  }

  ~overlay() = default;

  void add(std::shared_ptr<widget> widget) noexcept;

  void remove(std::shared_ptr<widget> widget) noexcept;

  void update(float_t delta) noexcept;

  void draw() const noexcept;

private:
  std::shared_ptr<renderer> _renderer;
  std::list<std::shared_ptr<widget>> _widgets;
  std::shared_ptr<font> _font;
};
}
