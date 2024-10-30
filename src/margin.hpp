#pragma once

#include "common.hpp"

namespace geometry {
class margin {
public:
  int32_t top;
  int32_t left;
  int32_t bottom;
  int32_t right;

  margin() noexcept = default;
  ~margin() noexcept = default;

  friend void from_json(const nlohmann::json &j, margin &m);
};
}
