#pragma once

#include "common.hpp"

#include "effect.hpp"
#include "flip.hpp"
#include "rect.hpp"
#include "size.hpp"

namespace graphics {
typedef std::unique_ptr<SDL_Texture, SDL_Deleter> texture_ptr;

class pixmap {
public:
  pixmap() = default;
  pixmap(const std::shared_ptr<renderer> renderer, std::string_view filename);
  ~pixmap() = default;

  void apply_effects(const std::vector<effect> &effects);

  void draw(
      const geometry::rect &source,
      const geometry::rect &destination,
      const double angle = 0.0,
      flip flip = flip::none,
      const uint8_t alpha = 255) const;

  const geometry::size size() const;

  void set_size(const geometry::size &size);

private:
  std::shared_ptr<renderer> _renderer;

  geometry::size _size;
  texture_ptr _texture;
};
}
