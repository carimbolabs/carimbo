#pragma once

#include "common.hpp"
#include "renderer.hpp"

namespace framework {
using space_ptr = std::shared_ptr<cpSpace>;

class world {
public:
  world() = delete;
  world(float_t gravity, std::shared_ptr<graphics::renderer> renderer);
  ~world() = default;

  space_ptr space() const noexcept;

  void draw() noexcept;

private:
  space_ptr _space;
  std::shared_ptr<graphics::renderer> _renderer;
};
}
