#pragma once

#include "common.hpp"

namespace storage {
class filesystem {
public:
  static void mount(std::string_view filename, std::string_view mountpoint);

private:
  constexpr filesystem() = default;
  ~filesystem() = default;
};
}
