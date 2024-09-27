#pragma once

#include "common.hpp"

namespace framework {
template <typename T>
class singleton {
public:
  virtual ~singleton() = default;

  static std::shared_ptr<T> instance();
};
}
