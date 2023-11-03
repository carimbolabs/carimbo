#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "audiomanager.hpp"

#include "noncopyable.hpp"

class application : private noncopyable {
public:
  application(int argc, char **argv);
  virtual ~application();

  int run();
};

#endif