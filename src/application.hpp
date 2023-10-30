#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "common.hpp"
#include "filesystem.hpp"
#include "noncopyable.hpp"
#include "pixmappool.hpp"
#include "scriptengine.hpp"
#include "timer.hpp"

class application : private noncopyable {
public:
  application(int argc, char **argv);
  virtual ~application();

  int run();
};

#endif