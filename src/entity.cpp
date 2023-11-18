#include "entity.hpp"

#include "entitymanager.hpp"
#include "pixmap.hpp"
#include "pixmappool.hpp"
#include "resourcemanager.hpp"
#include "soundmanager.hpp"

using namespace framework;

entity::entity(const std::string &id)
    : _id(id), _point(0, 0), _angle(0.0), _alpha(255), _fn(nullptr) {
}

entity::~entity() {
  std::cout << "entity::~entity(), id: " << _id << std::endl;
}

std::shared_ptr<entity> entity::create(const std::string &id) {
  return std::shared_ptr<entity>(new entity(id));
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
    _pixmap->draw(_point, _angle, _alpha);
  }
}

void entity::set_x(int32_t x) {
  _point.set_x(x);
}

int32_t entity::get_x() const {
  return _point.x();
}

void entity::set_y(int32_t y) {
  _point.set_y(y);
}

int32_t entity::get_y() const {
  return _point.y();
}

void entity::move(int32_t x, int32_t y) {
  _point.set_x(_point.x() + x);
  _point.set_y(_point.y() + y);
}

int32_t entity::width() const {
  return _pixmap->size().width();
}

int32_t entity::height() const {
  return _pixmap->size().height();
}

void entity::scale(double factor) {
  _pixmap->set_size({
      static_cast<uint32_t>(std::llround(_pixmap->size().width() * factor)),
      static_cast<uint32_t>(std::llround(_pixmap->size().height() * factor)),
  });
}

void entity::set_angle(const double_t angle) {
  _angle = angle;
}

double_t entity::angle() const {
  return _angle;
}

void entity::set_alpha(const uint8_t alpha) {
  _alpha = alpha;
}

uint8_t entity::alpha() const {
  return _alpha;
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
  _pixmap = _resourcemanager->pixmappool()->get(filename);
}

void entity::play_sound(const std::string &filename) {
  _resourcemanager->soundmanager()->play(filename);
}