#include "entitymanager.hpp"

std::shared_ptr<entity> entitymanager::spwan() {
  const auto e = std::make_shared<entity>();
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(std::shared_ptr<entity> entity) {
  // TODO run destroy routine
  // entity->on_destroy();
  // _entities.remove(entity);
}

void entitymanager::update() {
  for (auto entity : _entities) {
    entity->update();
  }
}

void entitymanager::draw() {
  for (auto entity : _entities) {
    entity->draw();
  }
}
