#include "fontfactory.hpp"
#include "helpers.hpp"
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

/* std::shared_ptr<font> */ void fontfactory::get(const std::string &face) {
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

  std::cout << "Created separator: " << separator << std::endl;

  std::unordered_map<char, SDL_Rect> glyphs;

  int x = 0, y = 0, glyph_width = 0, glyph_height = 0;
  for (char letter : alphabet) {
    std::cout << "letter " << letter << std::endl;
    while (x < size.width()) {
      if (color(pixels[y * size.width() + x], surface->format) != separator) {
        break;
      }
      ++x;
    }

    if (x >= size.width()) {
      throw std::runtime_error(fmt::format("Error: Missing glyph for '{}'", letter));
    }

    glyph_width = 0;
    while (x + glyph_width < size.width()) {
      if (color(pixels[y * size.width() + x + glyph_width], surface->format) == separator) {
        break;
      }
      ++glyph_width;
    }

    glyph_height = 0;
    while (y + glyph_height < size.height()) {
      if (color(pixels[(y + glyph_height) * size.width() + x], surface->format) == separator) {
        break;
      }
      ++glyph_height;
    }

    glyphs[letter] = SDL_Rect{x, y, glyph_width, glyph_height};

    x += glyph_width;
  }

  // Ajustar altura da linha com base nos glifos analisados
  int line_height = 0;
  for (const auto &[_, rect] : glyphs) {
    line_height = std::max(line_height, rect.h);
  }

  // Renderizar para verificar
  for (const auto &[c, rect] : glyphs) {
    fmt::print("Glyph '{}' -> x: {}, y: {}, w: {}, h: {}\n", c, rect.x, rect.y, rect.w, rect.h);
  }
  /*
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(
      SDL_CreateTexture(
          *_renderer.get(),
          SDL_PIXELFORMAT_ABGR8888,
          SDL_TEXTUREACCESS_STREAMING,
          size.width(),
          size.height()
      ),
      SDL_DestroyTexture
  );
  if (!texture) {
    throw std::runtime_error(fmt::format("[SDL_CreateTexture] Failed to create streaming texture. Error: {}", SDL_GetError()));
  }

  void *pixels = nullptr;
  int pitch = 0;
  if (SDL_LockTexture(texture.get(), nullptr, &pixels, &pitch) != 0) {
    throw std::runtime_error(fmt::format("[SDL_LockTexture] Failed to lock texture. Error: {}", SDL_GetError()));
  }

  std::memcpy(pixels, output.data(), output.size());

  SDL_UnlockTexture(texture.get());
  */
  // std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
  //     SDL_CreateRGBSurfaceWithFormat(
  //         0,
  //         size.width(),
  //         size.height(),
  //         0,
  //         SDL_PIXELFORMAT_ABGR8888
  //     ),
  //     SDL_FreeSurface
  // };
  // if (!surface) {
  //   throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormat] error while creating surface, file: {}, error: {}", filename, SDL_GetError()));
  // }

  // // const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string>());

  // int32_t width, height;
  // SDL_QueryTexture(*spritesheet, nullptr, nullptr, &width, &height);

  // std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
  //     SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, SDL_PIXELFORMAT_ABGR8888),
  //     SDL_FreeSurface
  // };
  // if (!surface) {
  //   throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormat] error: {}", SDL_GetError()));
  // }

  // if (SDL_RenderReadPixels(*_resourcemanager->renderer(), nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
  //   throw std::runtime_error(fmt::format("[SDL_RenderReadPixels] error: {}", SDL_GetError()));
  // }

  // const auto pixels = reinterpret_cast<uint32_t *>(surface->pixels);
  // const auto format = surface->format;
  // const auto separator = color(pixels[0], format);

  // static const auto black = color("#000000");
  // static const auto white = color("#ffffff");
  // static const auto mangeta = color("#ff00ff");
  // UNUSED(black);
  // UNUSED(white);
  // UNUSED(mangeta);

  // for (auto y = 0; y < height; ++y) {
  //   for (auto x = 0; x < width; ++x) {
  //     const auto pixel = pixels[(y * width) + x];
  //     color current_color(pixel, format);

  //     if (current_color == separator) {
  //       continue;
  //     }
  //   }
  // }

  // // return std::make_shared<font>();
}
