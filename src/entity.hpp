#pragma once
#ifndef _entity_hpp
#define _entity_hpp

#include "common.hpp"

class entity : public std::enable_shared_from_this<entity> {
public:
  entity() = default;
  ~entity() = default;

  virtual void update();

  virtual void draw() const;

  std::string get_id() const { return _id; }

  void set_id(const std::string &id) { _id = id; }

private:
  std::string _id;
};

#endif
