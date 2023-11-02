#pragma once
#ifndef _application_hpp
#define _application_hpp

#include "audiomanager.hpp"
#include "common.hpp"
#include "enginefactory.hpp"
#include "entitymanager.hpp"
#include "filesystem.hpp"
#include "noncopyable.hpp"
#include "pixmappool.hpp"
#include "scriptengine.hpp"
#include "timermanager.hpp"

class application : private noncopyable {
public:
  application(int argc, char **argv);
  virtual ~application();

  int run();
};

#endif