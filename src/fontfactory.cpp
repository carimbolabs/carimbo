#include "fontfactory.hpp"

using namespace graphics;
using json = nlohmann::json;

fontfactory::fontfactory(std::shared_ptr<framework::resourcemanager> resourcemanager) noexcept
    : _resourcemanager(std::move(resourcemanager)) {}

std::shared_ptr<font> fontfactory::get(const std::string &face) {
  const auto buffer = storage::io::read(fmt::format("fonts/{}.json", face));
  const auto j = json::parse(buffer);
  const auto alphabet = j["alphabet"].get<std::string>();
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].get<std::string>());

  int32_t width, height;
  SDL_QueryTexture(*spritesheet, nullptr, nullptr, &width, &height);

  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
      SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, SDL_PIXELFORMAT_ABGR8888),
      SDL_FreeSurface
  };
  if (!surface) {
    throw std::runtime_error(fmt::format("[SDL_CreateRGBSurfaceWithFormat] error: {}", SDL_GetError()));
  }

  if (SDL_RenderReadPixels(*_resourcemanager->renderer(), nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
    throw std::runtime_error(fmt::format("[SDL_RenderReadPixels] error: {}", SDL_GetError()));
  }

  const auto pixels = reinterpret_cast<uint32_t *>(surface->pixels);
  const auto format = surface->format;
  const auto separator = color(pixels[0], format);

  for (auto y = 0; y < height; ++y) {
    for (auto x = 0; x < width; ++x) {
      const auto pixel = pixels[(y * width) + x];
      color current_color(pixel, format);

      if (current_color == separator) {
        continue;
      }
    }
  }

  return std::make_shared<font>();
}
