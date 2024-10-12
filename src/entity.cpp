#include "entity.hpp"

#include "anchor.hpp"
#include "entitymanager.hpp"
#include "rect.hpp"
#include "resourcemanager.hpp"

using namespace framework;

entity::entity(const entityprops &&props)
    : _props(std::move(props)) {
}

entity::~entity() {
  std::cout << "entity::~entity(), id: " << _props.id << std::endl;
}

std::shared_ptr<entity> entity::create(const entityprops &&props) {
  return std::shared_ptr<entity>(new entity(std::move(props)));
}

uint64_t entity::id() const { return _props.id; }

const std::string entity::kind() const { return _props.kind; }

const entityprops entity::props() const {
  return _props;
}

void entity::set_props(entityprops props) {
  _props = std::move(props);
}

int32_t entity::x() const {
  return _props.position.x();
}

int32_t entity::y() const {
  return _props.position.y();
}

void entity::update(double delta) {
  if (_onupdate) {
    _onupdate(shared_from_this());
  }

  if (_props.action.empty() || !_props.visible) {
    return;
  }

  const auto now = SDL_GetTicks();
  const auto &animation = _props.animations.at(_props.action);
  const auto &frame = animation[_props.frame];

  if (frame.duration > 0 && now - _props.last_frame >= frame.duration) {
    _props.frame++;
    _props.last_frame = now;

    if (_props.frame >= animation.size()) {
      if (std::any_of(animation.begin(), animation.end(), [](const auto &keyframe) { return keyframe.singleshoot; })) {
        _props.action.clear();

        if (_onanimationfinished) {
          _onanimationfinished(shared_from_this());
        }

        return;
      }

      _props.frame = 0;
    }
  }

  if (_props.gravitic || !_props.velocity.zero()) {
    _props.position.set(
        _props.position.x() + static_cast<int32_t>(_props.velocity.x() * delta),
        _props.position.y() + static_cast<int32_t>(_props.velocity.y() * delta)
    );
  }
}

void entity::draw() const {
  if (_props.action.empty() || !_props.visible) {
    return;
  }

  const auto source = _props.animations.at(_props.action)[_props.frame].frame;
  const auto offset = _props.animations.at(_props.action)[_props.frame].offset;
  geometry::rect destination{_props.position + offset, source.size()};
  destination.scale(_props.scale);

  _props.spritesheet->draw(
      source,
      destination,
      _props.angle,
      _props.flip,
      _props.alpha
  );
}

bool entity::colliding_with(const entity &other) const {
  return _props.position.x() < other._props.position.x() + other._props.size.width() &&
         _props.position.x() + _props.size.width() > other._props.position.x() &&
         _props.position.y() < other._props.position.y() + other._props.size.height() &&
         _props.position.y() + _props.size.height() > other._props.position.y();
}

void entity::set_placement(int32_t x, int32_t y, anchor) {
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
    std::shared_ptr<resourcemanager> resourcemanager
) {
  _resourcemanager = resourcemanager;
}

void entity::set_velocity(const vector2d &velocity) {
  _props.velocity = std::move(velocity);
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _onupdate = std::move(fn);
}

void entity::set_onanimationfinished(const std::function<void(std::shared_ptr<entity>)> &fn) {
  _onanimationfinished = std::move(fn);
}

void entity::set_onmail(const std::function<void(std::shared_ptr<entity>, const std::string &)> &fn) {
  _onmail = std::move(fn);
}

void entity::set_flip(graphics::flip flip) {
  _props.flip = flip;
}

void entity::set_action(const std::string_view action) {
  if (_props.action != action) {
    _props.action = action;
    _props.frame = 0;
    _props.last_frame = SDL_GetTicks();
  }
}

void entity::unset_action() {
  _props.action = std::string();
  _props.frame = 0;
  _props.last_frame = SDL_GetTicks();
}

std::string entity::action() const {
  return _props.action;
}

const geometry::size entity::size() const {
  return _props.size;
}

bool entity::visible() const {
  return _props.visible;
}

void entity::dispatch(const std::string &message) {
  if (!_onmail) {
    return;
  }

  _onmail(shared_from_this(), message);
}
