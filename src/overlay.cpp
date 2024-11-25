#include "overlay.hpp"
#include "helpers.hpp"

using namespace graphics;

overlay::overlay(std::shared_ptr<renderer> renderer)
    : _renderer(std::move(renderer)) {}

void overlay::update(float_t delta) noexcept {
  for (const auto &widget : _widgets | std::views::all) {
    widget->update(delta);
  }
}

void overlay::draw() const noexcept {
  for (const auto &widget : _widgets | std::views::all) {
    widget->draw();
  }
}

/*
std::shared_ptr<widget> overlay::create(widgettype type) noexcept {
  auto widget = [&]() -> std::shared_ptr<::widget> {
    switch (type) {
    case widgettype::label:
      // return std::make_shared<label>();
      return std::shared_ptr<::widget>{};
    default:
      return std::shared_ptr<::widget>{};
    }
  }();

  _widgets.emplace_back(widget);

  return widget;
}

void overlay::destroy(std::shared_ptr<widget> widget) noexcept {
  std::erase_if(_widgets, [&widget](const auto &existing) {
    return existing == widget;
  });
}
*/

void overlay::add(std::shared_ptr<widget> widget) noexcept {
  _widgets.emplace_back(widget);
}
