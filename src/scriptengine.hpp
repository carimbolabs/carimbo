#pragma once
#ifndef _scriptengine_hpp
#define _scriptengine_hpp

#include "common.hpp"
#include "eventreceiver.hpp"
#include "io.hpp"
#include "motor.hpp"
#include "noncopyable.hpp"
#include "statemanager.hpp"

class scriptengine : private noncopyable {
public:
  scriptengine() = default;
  virtual ~scriptengine() = default;

  void run();

private:
  sol::state _lua;
};

#endif