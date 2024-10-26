#pragma once

#include "common.hpp"

namespace framework {
class scriptengine : private noncopyable {
public:
  scriptengine() noexcept = default;
  virtual ~scriptengine() noexcept = default;

  void run();
};
}
