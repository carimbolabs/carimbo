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

void overlay::add(std::variant<std::shared_ptr<widget>, std::shared_ptr<label>> &&widget) noexcept {
  std::visit([this](auto &&arg) {
    _widgets.emplace_back(std::move(arg));
  },
             std::move(widget));
}

void overlay::remove(std::variant<std::shared_ptr<widget>, std::shared_ptr<label>> &&widget) noexcept {
  std::visit([this](auto &&arg) {
    std::erase_if(_widgets, [&arg](const auto &existing) {
      return existing == arg;
    });
  },
             std::move(widget));
}
