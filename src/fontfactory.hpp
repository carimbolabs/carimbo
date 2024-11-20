#pragma once

#include "common.hpp"

namespace graphics {
class fontfactory {
public:
  fontfactory() = delete;
  explicit fontfactory(const std::shared_ptr<framework::resourcemanager> resourcemanager) noexcept;
  ~fontfactory() noexcept = default;

  /* std::shared_ptr<font> */ void get(const std::string &face);

private:
  std::shared_ptr<framework::resourcemanager> _resourcemanager;
};
}
