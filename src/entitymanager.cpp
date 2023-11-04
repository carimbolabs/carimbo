#include "entitymanager.hpp"

#include "entity.hpp"
#include "resourcemanager.hpp"

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

std::shared_ptr<entity> entitymanager::spawn() {
  const auto id = "TODO"; //
  const auto e = std::make_shared<entity>(id);
  e->set_resourcemanager(_resourcemanager);
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(std::shared_ptr<entity> entity) {
  // TODO run destroy routine
  // entity->on_destroy();
  // _entities.remove(entity);
}

std::shared_ptr<entity> entitymanager::find(const std::string &id) {
  for (auto entity : _entities) {
    if (entity->get_id() == id) {
      return entity;
    }
  }

  return nullptr;
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
