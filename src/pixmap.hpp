#pragma once

#include "common.hpp"
#include "rect.hpp"
#include "renderer.hpp"
#include "size.hpp"

namespace graphics {
typedef std::unique_ptr<SDL_Texture, SDL_Deleter> texture_ptr;

class pixmap {
public:
  pixmap() = default;
  pixmap(const std::shared_ptr<renderer> &renderer, std::string_view filename);
  ~pixmap() = default;

  void apply_effects(const std::vector<effect> &effects);

  void draw(
      const geometry::rect &source,
      const geometry::rect &destination,
      double angle = 0.0,
      flip flip = flip::none,
      uint8_t alpha = 255
  ) const noexcept;

  geometry::size size() const noexcept;

  void set_size(const geometry::size &size) noexcept;

  operator SDL_Texture *() const noexcept;

private:
  std::shared_ptr<renderer> _renderer;
  geometry::size _size{0, 0};
  texture_ptr _texture;
};
}
