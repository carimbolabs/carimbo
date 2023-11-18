#pragma once
#ifndef _scriptengine_hpp
#define _scriptengine_hpp

#include "common.hpp"

namespace framework {
class scriptengine : private noncopyable {
public:
  scriptengine() = default;
  virtual ~scriptengine() = default;

  void run();
};
}

#endif