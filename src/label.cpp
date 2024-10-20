
#include "label.hpp"

using namespace graphics;

label::label(std::shared_ptr<font> font, const std::string &text, const geometry::point &position)
    : _font(font), _text(text), _position(position) {}

std::shared_ptr<label> label::create(std::shared_ptr<font> font, const std::string &text, const geometry::point &position) {
  return std::make_shared<label>(font, text, position);
}

void label::set(const std::string &text) {
  _text = text;
}

void label::set(const std::string &text, const geometry::point &position) {
  _text = text;
  _position = position;
}

void label::draw() const {
}
