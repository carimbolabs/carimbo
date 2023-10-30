#pragma once
#ifndef _scriptengine_hpp
#define _scriptengine_hpp

#include "common.hpp"
#include "file.hpp"
#include "motor.hpp"
#include "noncopyable.hpp"

class scriptengine : private noncopyable {
public:
  scriptengine() = default;
  virtual ~scriptengine() = default;

  void run();

private:
  sol::state _lua;
};

#endif