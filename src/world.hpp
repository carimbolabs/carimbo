#pragma once

#include "common.hpp"
#include "renderer.hpp"

namespace framework {
class world {
public:
  world() = delete;
  world(float_t gravity, std::shared_ptr<graphics::renderer> renderer);
  ~world() = default;

  void update(float_t delta) const noexcept;

  void draw() noexcept;

private:
  std::shared_ptr<graphics::renderer> _renderer;
};
}
