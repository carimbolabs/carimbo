#pragma once
#ifndef _entitymanager_hpp
#define _entitymanager_hpp

#include "common.hpp"
#include "entity.hpp"

class entitymanager {
public:
  entitymanager() = default;
  ~entitymanager() = default;

  std::shared_ptr<entity> spwan();

  void destroy(std::shared_ptr<entity> entity);

  std::shared_ptr<entity> find(const std::string &id);

  void update();

  void draw();

private:
  std::list<std::shared_ptr<entity>> _entities;
};

#endif