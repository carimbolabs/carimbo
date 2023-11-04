#include "entity.hpp"

#include "entitymanager.hpp"
#include "pixmap.hpp"
#include "pixmappool.hpp"
#include "resourcemanager.hpp"

entity::entity(const std::string &id) : _id(id), _x(0), _y(0) {
}

std::shared_ptr<entity> entity::create(const std::string &id) {
  return std::shared_ptr<entity>(new entity(id));
}

void entity::destroy(const std::shared_ptr<entity> entity) {
  std::cout << "[entity] destroy: " << entity->get_id() << std::endl;
  std::cout << "[entity] destroy use_count: " << entity.use_count() << std::endl;
  entity.~shared_ptr();
}

std::string entity::get_id() const {
  return _id;
}

void entity::update() {
  if (_fn) {
    _fn(shared_from_this());
  }
}

void entity::draw() const {
  if (_pixmap) {
    _pixmap->draw(_x, _y, _angle);
  }
}

void entity::set_x(int32_t x) {
  _x = x;
}

int32_t entity::x() const {
  return _x;
}

void entity::set_y(int32_t y) {
  _y = y;
}

int32_t entity::y() const {
  return _y;
}

void const entity::set_angle(const double angle) {
  _angle = angle;
}

const double entity::angle() const {
  return _angle;
}

void entity::set_entitymanager(std::shared_ptr<entitymanager> entitymanager) {
  _entitymanager = entitymanager;
}

void entity::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _fn = fn;
}

void entity::set_pixmap(const std::string &filename) {
  _pixmap = _resourcemanager->get_pixmappool()->get(filename);
}
