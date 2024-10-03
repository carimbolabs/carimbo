#include "entity.hpp"

#include "anchor.hpp"
#include "entitymanager.hpp"
#include "pixmap.hpp"
#include "pixmappool.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "soundmanager.hpp"
#include <iostream>

using namespace framework;

// constexpr double_t GRAVITY = .5;

entity::entity(const entityprops &&props)
    : _props(std::move(props)), _fn(nullptr) {
}

entity::~entity() {
  std::cout << "entity::~entity(), id: " << _id << std::endl;
}

std::shared_ptr<entity> entity::create(const entityprops &&props) {
  return std::shared_ptr<entity>(new entity(std::move(props)));
}

uint64_t entity::id() const { return _props.id; }

const entityprops entity::props() const noexcept {
  return _props;
}

void entity::set_props(entityprops props) noexcept {
  _props = std::move(props);
}

void entity::update(double delta) noexcept {
  if (!_props.action.empty()) {
    const auto now = SDL_GetTicks();
    const auto animation = _props.animations.at(_props.action);
    if (now - _props.last_frame >= animation[_props.frame].duration) {
      _props.frame = (_props.frame + 1) % animation.size();
      _props.last_frame = now;
    }

    if (_props.gravitic || _props.velocity.x() != 0.0 || _props.velocity.y() != 0.0) {
      const auto x = _props.position.x() + static_cast<int32_t>(_props.velocity.x() * delta);
      const auto y = _props.position.y() + static_cast<int32_t>(_props.velocity.y() * delta);
      _props.position.set(x, y);
    }
  }

  if (_fn) {
    _fn(shared_from_this());
  }
}

void entity::draw() const noexcept {
  if (!_props.action.empty()) {
    const auto source = _props.animations.at(_props.action)[_props.frame].frame;
    geometry::rect destination{_props.position, source.size()};
    destination.scale(_props.scale);

    _props.spritesheet->draw(
        source,
        destination,
        .0f,
        graphics::flip::none,
        255);
  }
}

void entity::set_placement(int32_t x, int32_t y, anchor) noexcept {
  int32_t _x{x}, _y{y};

  // const auto window = SDL_GetMouseFocus();
  // if (!window) {
  //   std::cerr << "[SDL_GetMouseFocus] failed to obtain SDL_Window: No window is currently focused or available." << std::endl;
  //   return;
  // }

  // int _width{0}, _height{0};
  // SDL_GetWindowSize(window, &_width, &_height);

  // switch (anchor) {
  // case anchor::top:
  //   _y = 0;
  //   break;
  // case anchor::bottom:
  //   _y = _height - y;
  //   break;
  // case anchor::left:
  //   _x = 0;
  //   break;
  // case anchor::right:
  //   _x = _width - x;
  //   break;
  // case anchor::none:
  //   break;
  // }

  // std::cout << "_props.position.set >> " << _x << "x" << _y << std::endl;

  _props.position.set(_x, _y);
}

void entity::set_entitymanager(std::shared_ptr<entitymanager> entitymanager) {
  _entitymanager = entitymanager;
}

void entity::set_resourcemanager(
    std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

void entity::set_velocity(const vector2d &velocity) noexcept {
  _props.velocity = std::move(velocity);
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _fn = fn;
}

void entity::set_action(const std::string_view action) noexcept {
  _props.action = action;
}

std::string entity::action() const noexcept {
  return _props.action;
}
