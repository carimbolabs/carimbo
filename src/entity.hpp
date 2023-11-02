#pragma once
#ifndef _entity_hpp
#define _entity_hpp

#include "common.hpp"

class entity : public std::enable_shared_from_this<entity> {
public:
  entity() = default;
  // ~entity() = default;
  virtual ~entity() {
    std::cout << "entity::~entity()" << std::endl;
  }

  virtual void update();

  virtual void draw() const;

  std::string get_id() const { return _id; }

  void set_fn(const std::function<void(std::shared_ptr<entity>)> &fn);

private:
  std::string _id;
  std::function<void(std::shared_ptr<entity>)> _fn;
};

#endif
