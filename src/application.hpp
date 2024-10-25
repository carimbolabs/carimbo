#pragma once

#include "noncopyable.hpp"

namespace framework {
class application : private noncopyable {
public:
  application(int argc, char **argv);
  virtual ~application() noexcept;

  int run();
};
}
