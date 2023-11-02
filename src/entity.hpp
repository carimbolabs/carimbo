#pragma once
#ifndef _entity_hpp
#define _entity_hpp

#include "common.hpp"

class entity {
public:
  entity() = default;
  ~entity() = default;

  virtual void update();

  virtual void draw() const;
};

#endif
