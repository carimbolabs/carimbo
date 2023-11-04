#pragma once
#ifndef _entitymanager_hpp
#define _entitymanager_hpp

#include "common.hpp"

class entitymanager {
public:
  entitymanager() = default;
  ~entitymanager() = default;

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  std::shared_ptr<entity> spawn();

  void destroy(std::shared_ptr<entity> entity);

  std::shared_ptr<entity> find(const std::string &id);

  void update();

  void draw();

private:
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::list<std::shared_ptr<entity>> _entities;
};

#endif