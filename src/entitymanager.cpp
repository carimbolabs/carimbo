#include "entitymanager.hpp"

void entitymanager::set_pixmappool(std::shared_ptr<pixmappool> pixmappool) {
  _pixmappool = pixmappool;
}

std::shared_ptr<entity> entitymanager::spawn() {
  const auto id = "TODO"; //
  const auto e = std::make_shared<entity>(id);
  e->set_pixmappool(_pixmappool);
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
