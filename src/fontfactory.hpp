#pragma once

#include "common.hpp"

namespace graphics {
class fontfactory {
public:
  fontfactory() = delete;
  explicit fontfactory(std::shared_ptr<graphics::renderer> renderer) noexcept;
  ~fontfactory() noexcept = default;

  /* std::shared_ptr<font> */ void get(const std::string &face);

private:
  std::shared_ptr<graphics::renderer> _renderer;
};
}
