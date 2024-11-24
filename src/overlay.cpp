#include "overlay.hpp"

using namespace graphics;

overlay::overlay(std::shared_ptr<renderer> renderer)
    : _renderer(std::move(renderer)) {}

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

std::shared_ptr<widget> overlay::create(widgettype type) noexcept {
  std::shared_ptr<widget> widget;

  switch (type) {
  case widgettype::label:
    widget = std::make_shared<label>();
    break;
  default:
    return nullptr;
  }

  _widgets.emplace_back(widget);
  return widget;
}

void overlay::destroy(std::shared_ptr<widget> widget) noexcept {
  _widgets.remove_if([&widget](const std::shared_ptr<::widget> &existing) {
    return existing == widget;
  });
}
