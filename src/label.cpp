#include "label.hpp"

using namespace graphics;

label::label(std::shared_ptr<font> font, const std::string &text, const geometry::point &position)
    : _font(std::move(font)), _text(text), _position(position) {}

std::shared_ptr<label> label::create(std::shared_ptr<font> font, const std::string &text, const geometry::point &position) noexcept {
  return std::make_shared<label>(std::move(font), text, position);
}

void label::set(const std::string &text) {
  _text = text;
}

void label::set(std::string text, const geometry::point &position) {
  _text = std::move(text);
  _position = position;
}

void label::draw() const noexcept {
}
