#include "entity.hpp"

#include "entitymanager.hpp"
#include "pixmap.hpp"
#include "pixmappool.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"
#include "soundmanager.hpp"

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

const entityprops entity::props() const {
  return _props;
}

void entity::set_props(entityprops props) {
  _props = std::move(props);
}

void entity::update() {
  const auto now = SDL_GetTicks();
  const auto animation = _props.animations.at(_props.action);
  if (now - _props.last_frame >= animation[_props.frame].duration) {
    _props.frame = (_props.frame + 1) % animation.size();
    _props.last_frame = now;
  }

  if (_props.gravitic) {
  }

  if (_fn) {
    _fn(shared_from_this());
  }
}

void entity::draw() const {
  if (_props.spritesheet) {
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

void entity::set_entitymanager(std::shared_ptr<entitymanager> entitymanager) {
  _entitymanager = entitymanager;
}

void entity::set_resourcemanager(
    std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _fn = fn;
}

void entity::set_pixmap(const std::string_view) {
  // _pixmap = _resourcemanager->pixmappool()->get(filename);
}
