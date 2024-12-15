#include "font.hpp"

using namespace graphics;

font::font(const glyphmap &glyphs, std::shared_ptr<pixmap> pixmap, int16_t spacing, float_t scale)
    : _glyphs(glyphs), _pixmap(std::move(pixmap)), _spacing(spacing), _scale(scale) {}

void font::draw(const std::string &text, const geometry::point &position) const noexcept {
  geometry::point cursor = position;

  for (const auto &character : text) {
    const auto &glyph = _glyphs.at(character);
    auto size = glyph.size();
    size.set_scale(_scale);

    _pixmap->draw(glyph, {cursor, size.resized()});

    cursor += std::make_pair('x', size.width() + _spacing);
  }
}
