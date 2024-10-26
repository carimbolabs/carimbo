#include "glyph.hpp"

using namespace graphics;

glyph::glyph(uint32_t code) noexcept
    : _code(code) {}

void glyph::draw(const glyphprops &props) const noexcept {
  UNUSED(props);
}
