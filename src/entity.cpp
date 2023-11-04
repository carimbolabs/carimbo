#include "entity.hpp"

#include "pixmappool.hpp"
#include "resourcemanager.hpp"

entity::entity(const std::string &id) : _id(id), _x(0), _y(0) {
  std::cout << "[entity] constructor: " << _id << std::endl;
}

entity::~entity() {
  std::cout << "[entity] destructor: " << _id << std::endl;
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
    _pixmap->draw(_x, _y);
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

void entity::set_position(int32_t x, int32_t y) {
  _x = x;
  _y = y;
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
