#include "entity.hpp"

void entity::update() {
  if (_fn) {
    _fn(shared_from_this());
  }
}

void entity::draw() const {
  // TODO
}

void entity::set_fn(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _fn = fn;
}