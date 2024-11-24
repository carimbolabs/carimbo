#include "label.hpp"

using namespace graphics;

void label::set_font(const std::shared_ptr<font> &font) noexcept {
  _font = font;
}

void label::set_placement(const geometry::point &position) noexcept {
  _position = position;
}

void label::set_text(std::string_view text) noexcept {
  _text = text;
}

void label::set_text_with_position(std::string_view text, const geometry::point &position) noexcept {
  _text = text;
  _position = position;
}

void label::update(float_t delta) noexcept {
  UNUSED(delta);
}

void label::draw() const noexcept {
  _font->draw(_text, _position);
}
