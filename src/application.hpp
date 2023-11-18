#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "noncopyable.hpp"

namespace framework {
class application : private noncopyable {
public:
  application(int argc, char **argv);
  virtual ~application();

  int run();
};
}

#endif