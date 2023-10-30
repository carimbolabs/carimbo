#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "common.hpp"
#include "engine.hpp"
#include "filesystem.hpp"
#include "pixmappool.hpp"

class application {
public:
  application(int argc, char **argv);
  ~application();

  int run();
};

#endif