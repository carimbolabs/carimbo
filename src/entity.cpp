#include "entity.hpp"

using namespace framework;

entity::entity(entityprops &&props) noexcept
    : _props(std::move(props)) {}

entity::~entity() noexcept {
  std::println("entity of type '{}' destroyed", kind());
}

std::shared_ptr<entity> entity::create(entityprops &&props) {
  return std::make_shared<entity>(std::move(props));
}

uint64_t entity::id() const noexcept {
  return _props.id;
}

std::string_view entity::kind() const noexcept {
  return _props.kind;
}

entityprops &entity::props() noexcept {
  return _props;
}

const entityprops &entity::props() const noexcept {
  return _props;
}

int32_t entity::x() const noexcept {
  return _props.position.x();
}

int32_t entity::y() const noexcept {
  return _props.position.y();
}

void entity::move(float_t x_velocity, float_t y_velocity) {
  cpBodySetVelocity(_props.body.get(), {x_velocity, y_velocity});
}

math::vector2d entity::get_velocity() const noexcept {
  cpVect velocity = cpBodyGetVelocity(_props.body.get());
  return {velocity.x, velocity.y};
}

void entity::update(float_t delta) noexcept {
  UNUSED(delta);

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
    ++_props.frame;
    _props.last_frame = now;

    if (_props.frame >= animation.size()) {
      if (std::ranges::any_of(animation, [](const auto &keyframe) { return keyframe.singleshoot; })) {
        _props.action.clear();

        if (_onanimationfinished) {
          _onanimationfinished(shared_from_this());
        }

        return;
      }

      _props.frame = 0;
    }
  }

  _props.angle = cpBodyGetAngle(_props.body.get());

  const auto position = cpBodyGetPosition(_props.body.get());
  _props.position.set(
      static_cast<int32_t>(std::round(position.x)),
      static_cast<int32_t>(std::round(position.y))
  );
}

void entity::draw() const noexcept {
  if (_props.action.empty() || !_props.visible) {
    return;
  }

  const auto &animation_frame = _props.animations.at(_props.action)[_props.frame];
  const auto &source = animation_frame.frame;
  const auto &offset = animation_frame.offset;
  geometry::rect destination{_props.position + offset, source.size()};
  destination.scale(_props.size.scale());

  if (!_props.spritesheet) {
    return;
  }

  _props.spritesheet->draw(
      source,
      destination,
      _props.angle,
      _props.flip,
      _props.alpha
  );
}

void entity::set_props(entityprops props) noexcept {
  _props = std::move(props);
}

void entity::set_placement(int32_t x, int32_t y) noexcept {
  cpBodySetPosition(_props.body.get(), {static_cast<cpFloat>(x), static_cast<cpFloat>(y)});
}

void entity::set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept {
  _onupdate = fn;
}

void entity::set_onanimationfinished(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept {
  _onanimationfinished = fn;
}

void entity::set_onmail(const std::function<void(std::shared_ptr<entity>, const std::string &)> &fn) noexcept {
  _onmail = fn;
}

void entity::set_flip(graphics::flip flip) noexcept {
  _props.flip = flip;
}

void entity::set_action(std::string_view action) {
  if (_props.action != action) {
    _props.action.assign(action);
    _props.frame = 0;
    _props.last_frame = SDL_GetTicks();
  }
}

void entity::unset_action() {
  _props.action.clear();
  _props.frame = 0;
  _props.last_frame = SDL_GetTicks();
}

std::string_view entity::action() const noexcept {
  return _props.action;
}

geometry::size entity::size() const noexcept {
  return _props.size;
}

bool entity::visible() const noexcept {
  return _props.visible;
}

void entity::on_email(const std::string &message) {
  if (_onmail) {
    _onmail(shared_from_this(), message);
  }
}
