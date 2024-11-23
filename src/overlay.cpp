#include "overlay.hpp"

using namespace graphics;

void overlay::add(std::shared_ptr<widget> widget) noexcept {
  _widgets.emplace_back(std::move(widget));
}

void overlay::remove(std::shared_ptr<widget> widget) noexcept {
  _widgets.remove_if([&widget](const std::shared_ptr<::widget> &existing) {
    return existing == widget;
  });
}

void overlay::update(float_t delta) noexcept {
  for (const auto &widget : _widgets) {
    widget->update(delta);
  }
}

void overlay::draw() const noexcept {
  for (const auto &widget : _widgets) {
    widget->draw();
  }
}
