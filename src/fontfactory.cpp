#include "fontfactory.hpp"

using namespace graphics;

using json = nlohmann::json;
/*

using json = nlohmann::json;

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

std::shared_ptr<entity> entitymanager::spawn(const std::string &kind) {
  const auto buffer = storage::io::read(fmt::format("entities/{}.json", kind));
  const auto j = json::parse(buffer);
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].template get<std::string>());
  const auto gravitic = j.value("gravitic", false);
  const auto scale = j.value("scale", 1.);*/

fontfactory::fontfactory(const std::shared_ptr<framework::resourcemanager> resourcemanager)
    : _resourcemanager(resourcemanager) {}

std::shared_ptr<font> fontfactory::get(const std::string &face) {
  const auto buffer = storage::io::read(fmt::format("fonts/{}.json", face));
  const auto j = json::parse(buffer);
  const auto alphabet = j["alphabet"].template get<std::string>();
  const auto spritesheet = _resourcemanager->pixmappool()->get(j["spritesheet"].template get<std::string>());

  int32_t width, height;
  SDL_QueryTexture(*spritesheet, NULL, NULL, &width, &height);

  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
      SDL_CreateRGBSurfaceWithFormat(
          0,
          width,
          height,
          0,
          SDL_PIXELFORMAT_ABGR8888
      ),
      SDL_FreeSurface
  };
  if (!surface) {
    throw std::runtime_error(
        fmt::format("[SDL_CreateRGBSurfaceWithFormat] error while creating surface with format: {}", SDL_GetError())
    );
  }

  if (SDL_RenderReadPixels(*_resourcemanager->renderer(), NULL, surface->format->format, surface->pixels, surface->pitch) != 0) {
    throw std::runtime_error(fmt::format("[SDL_RenderReadPixels] error reading pixels: {}", SDL_GetError()));
  }

  uint32_t *pixels = reinterpret_cast<uint32_t *>(surface->pixels);
  for (int32_t y = 0; y < height; ++y) {
    for (int32_t x = 0; x < width; ++x) {
      uint32_t pixel = pixels[(y * width) + x];
      uint8_t r, g, b, a;
      SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
    }
  }

  // const auto ptr = _resourcemanager.lock();
  // if (!ptr) {
  //   throw std::runtime_error("bad resourcemanager_shared");
  // }

  // const auto texture = ptr->pixmappool()->get(filename);
  // int32_t width, height;
  // SDL_QueryTexture(*texture, NULL, NULL, &width, &height);

  // std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
  //     SDL_CreateRGBSurfaceWithFormat(
  //         0,
  //         width,
  //         height,
  //         0,
  //         SDL_PIXELFORMAT_ABGR8888
  //     ),
  //     SDL_FreeSurface
  // };
  // if (!surface) {
  //   throw std::runtime_error(
  //       fmt::format("[SDL_CreateRGBSurfaceWithFormat] error while creating surface with format: {}, error {}", filename, SDL_GetError())
  //   );
  // }

  // if (SDL_RenderReadPixels(*ptr->renderer(), NULL, surface->format->format, surface->pixels, surface->pitch) != 0) {
  //   throw std::runtime_error(fmt::format("[SDL_RenderReadPixels] error reading pixels: {}, error {}", filename, SDL_GetError()));
  // }

  // uint32_t *pixels = reinterpret_cast<uint32_t *>(surface->pixels);
  // for (int32_t y = 0; y < height; ++y) {
  //   for (int32_t x = 0; x < width; ++x) {
  //     uint32_t pixel = pixels[(y * width) + x];
  //     uint8_t r, g, b, a;
  //     SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
  //   }
  // }

  return std::shared_ptr<font>(); // TEMP
}

// void font::update(double_t delta) {
//   for (auto &[key, glyph] : _glyphs) {
//     glyph.update(delta);
//   }
// }

// void font::draw() const {
//   for (const auto &[key, glyph] : _glyphs) {
//     glyph.draw();
//   }
// }
