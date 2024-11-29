#include "fontfactory.hpp"

using namespace graphics;

using json = nlohmann::json;

fontfactory::fontfactory(std::shared_ptr<graphics::renderer> renderer) noexcept
    : _renderer(std::move(renderer)) {}

std::shared_ptr<font> fontfactory::get(std::string_view family) {
  auto [it, added] = _pool.insert_or_assign(family, nullptr);

  if (added) [[unlikely]] {
    std::cout << "[fontfactory] cache miss: " << family << '\n';

    const auto &buffer = storage::io::read(fmt::format("fonts/{}.json", family));
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
      throw std::runtime_error(
          fmt::format("[SDL_CreateRGBSurfaceWithFormatFrom] Error: {}", SDL_GetError())
      );
    }

    const auto pixels = static_cast<uint32_t *>(surface->pixels);
    const auto separator = color(pixels[0], surface->format);

    glyphmap map;
    int x = 0, y = 0, width = 0, height = 0;

    for (const char letter : alphabet) {
      while (x < size.width() && color(pixels[y * size.width() + x], surface->format) == separator) {
        ++x;
      }

      if (x >= size.width()) [[unlikely]] {
        throw std::runtime_error(fmt::format("Error: Missing glyph for '{}'", letter));
      }

      width = 0;
      while (x + width < size.width() &&
             color(pixels[y * size.width() + x + width], surface->format) != separator) {
        ++width;
      }

      height = 0;
      while (y + height < size.height() &&
             color(pixels[(y + height) * size.width() + x], surface->format) != separator) {
        ++height;
      }

      map[letter] = {{x, y}, {width, height}};
      x += width;
    }

    it->second = std::make_shared<font>(
        std::move(map),
        std::make_shared<pixmap>(_renderer, std::move(surface)),
        spacing
    );
  }

  return it->second;
}

void fontfactory::flush() noexcept {
  std::erase_if(_pool, [](const auto &pair) { return pair.second.use_count() == MINIMAL_USE_COUNT; });
}

void fontfactory::update(float_t delta) noexcept {
  UNUSED(delta);
}
