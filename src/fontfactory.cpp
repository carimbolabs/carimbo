#include "fontfactory.hpp"
#include "font.hpp"
#include "helpers.hpp"
#include "rect.hpp"
#include "renderer.hpp"
#include <ostream>

using namespace graphics;
using json = nlohmann::json;

fontfactory::fontfactory(std::shared_ptr<graphics::renderer> renderer) noexcept
    : _renderer(std::move(renderer)) {}

std::shared_ptr<font> fontfactory::get(const std::string &name) {
  auto [it, added] = _pool.try_emplace(name, nullptr);

  if (added) {
    std::cout << "[fontfactory] cache miss: " << name << std::endl;

    const auto &buffer = storage::io::read(fmt::format("fonts/{}.json", name));
    const auto &j = json::parse(buffer);
    const auto &alphabet = j["alphabet"].get<std::string>();
    const auto spacing = j["spacing"].get<int16_t>();

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

    if (!surface) [[unlikely]] {
      throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormatFrom] Error creating surface. Error: {}", SDL_GetError()));
    }

    const auto pixels = static_cast<uint32_t *>(surface->pixels);

    const auto separator = color(pixels[0], surface->format);

    glyphmap map;
    int x = 0, y = 0, width = 0, height = 0;
    for (const auto &letter : alphabet) {
      while (x < size.width()) {
        if (color(pixels[y * size.width() + x], surface->format) != separator) {
          break;
        }
        ++x;
      }

      if (x >= size.width()) [[unlikely]] {
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

    // for (const auto &[letter, rect] : map) {
    //   fmt::print("glyph '{}' -> x: {}, y: {}, w: {}, h: {}\n", static_cast<char>(letter), rect.position().x(), rect.position().y(), rect.size().width(), rect.size().height());
    // }

    it->second = std::make_shared<font>(map, std::make_shared<pixmap>(_renderer, std::move(surface)), spacing);
  }

  return it->second;
}

void fontfactory::flush() noexcept {
  for (auto it = _pool.begin(); it != _pool.end();) {
    switch (it->second.use_count()) {
    case 1:
      it = _pool.erase(it);
      break;

    default:
      ++it;
      break;
    }
  }
}
