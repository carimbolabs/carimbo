#include "entitymanager.hpp"

#include "entity.hpp"
#include "resourcemanager.hpp"

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

std::shared_ptr<entity> entitymanager::spawn() {
  const auto id = "TODO"; //
  const auto e = entity::create(id);
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(const std::shared_ptr<entity> entity) {
  _entities.remove(entity);
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
