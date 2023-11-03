#include "entity.hpp"

entity::entity(const std::string &id) : _id(id), _x(0), _y(0) {
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

void entity::set_pixmappool(std::shared_ptr<pixmappool> pixmappool) {
  _pixmappool = pixmappool;
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _fn = fn;
}

void entity::set_pixmap(const std::string &filename) {
  _pixmap = _pixmappool->get(filename);
}
