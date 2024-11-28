#pragma once

#include "common.hpp"

namespace graphics {
class fontfactory {
public:
  fontfactory() noexcept = delete;
  explicit fontfactory(std::shared_ptr<graphics::renderer> renderer) noexcept;
  ~fontfactory() noexcept = default;

  std::shared_ptr<font> get(std::string_view family);

  void flush() noexcept;

private:
  std::list<std::string> _filenames{};
  std::unordered_map<std::string_view, std::shared_ptr<font>> _pool{};
  std::shared_ptr<graphics::renderer> _renderer{};
};
}
