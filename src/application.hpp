#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "internal.hpp"

class application {
public:
  application(int argc, char **argv);
  ~application();

  int run();
};

#endif