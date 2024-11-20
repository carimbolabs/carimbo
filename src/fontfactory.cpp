#include "fontfactory.hpp"
#include "font.hpp"
#include "helpers.hpp"
#include "rect.hpp"
#include "renderer.hpp"
#include <ostream>

using namespace graphics;
using json = nlohmann::json;

std::ostream &operator<<(std::ostream &os, const color &c) {
  os << std::hex << std::uppercase << std::setfill('0')
     << "#"
     << std::setw(2) << static_cast<int>(c.r())
     << std::setw(2) << static_cast<int>(c.g())
     << std::setw(2) << static_cast<int>(c.b())
     << std::setw(2) << static_cast<int>(c.a());
  return os;
}

fontfactory::fontfactory(std::shared_ptr<graphics::renderer> renderer) noexcept
    : _renderer(std::move(renderer)) {}

std::shared_ptr<font> fontfactory::get(const std::string &face) {
  const auto buffer = storage::io::read(fmt::format("fonts/{}.json", face));
  const auto j = json::parse(buffer);
  const auto alphabet = j["alphabet"].get<std::string>();

  std::vector<uint8_t> output;
  geometry::size size;
  std::tie(output, size) = _load_png(j["spritesheet"].get<std::string_view>());
  auto surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>{
      SDL_CreateRGBSurfaceWithFormatFrom(
          output.data(),
          size.width(),
          size.height(),
          32,
          size.width() * 4,
          SDL_PIXELFORMAT_ABGR8888
      ),
      SDL_FreeSurface
  };

  if (!surface) {
    throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormatFrom] Error creating surface. Error: {}", SDL_GetError()));
  }

  const auto pixels = static_cast<uint32_t *>(surface->pixels);

  const auto separator = color(pixels[0], surface->format);

  glyphmap map;
  int x = 0, y = 0, width = 0, height = 0;
  for (const auto letter : alphabet) {
    while (x < size.width()) {
      if (color(pixels[y * size.width() + x], surface->format) != separator) {
        break;
      }
      ++x;
    }

    if (x >= size.width()) {
      throw std::runtime_error(fmt::format("Error: Missing glyph for '{}'", letter));
    }

    width = 0;
    while (x + width < size.width()) {
      if (color(pixels[y * size.width() + x + width], surface->format) == separator) {
        break;
      }
      ++width;
    }

    height = 0;
    while (y + height < size.height()) {
      if (color(pixels[(y + height) * size.width() + x], surface->format) == separator) {
        break;
      }
      ++height;
    }

    map[letter] = {{x, y}, {width, height}};

    x += width;
  }

  int line_height = 0;
  for (const auto &[_, rect] : map) {
    line_height = std::max(line_height, rect.size().height());
  }

  for (const auto &[letter, rect] : map) {
    fmt::print("glyph '{}' -> x: {}, y: {}, w: {}, h: {}\n", static_cast<char>(letter), rect.position().x(), rect.position().y(), rect.size().width(), rect.size().height());
  }

  return std::make_shared<font>(map, std::make_shared<pixmap>(_renderer, std::move(surface)));
}
