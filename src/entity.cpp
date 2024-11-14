#include "entity.hpp"

using namespace framework;

entity::entity(entityprops &&props)
    : _props(std::move(props)) {}

std::shared_ptr<entity> entity::create(entityprops &&props) {
  return std::shared_ptr<entity>(new entity(std::move(props)));
}

uint64_t entity::id() const noexcept { return _props.id; }

std::string entity::kind() const { return _props.kind; }

const entityprops &entity::props() const { return _props; }

int32_t entity::x() const noexcept { return _props.position.x(); }

int32_t entity::y() const noexcept { return _props.position.y(); }

void entity::update() {
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

  // usando chipmunk, leia de props o tamanho, considere o scale de size e o tipo do body e entao aplique o shape
  // mas, faca cache, se nao mudar nao mexa no shape, se mudar desaloque a memoria e criei um novo e atache ao body
  // para o cache pode ser criada uma propriedade em _props
  // e arrume o caculo de angulo e posicao, o body nao esta se movendo

  _props.angle = cpBodyGetAngle(_props.body.get());

  const auto position = cpBodyGetPosition(_props.body.get());
  _props.position.set(
      static_cast<int32_t>(std::round(position.x)),
      static_cast<int32_t>(std::round(position.y))
  );
}

void entity::draw() const {
  if (_props.action.empty() || !_props.visible) {
    return;
  }

  const auto source = _props.animations.at(_props.action)[_props.frame].frame;
  const auto offset = _props.animations.at(_props.action)[_props.frame].offset;
  geometry::rect destination{_props.position + offset, source.size()};
  destination.scale(_props.size.scale());

  _props.spritesheet->draw(
      source,
      destination,
      _props.angle,
      _props.flip,
      _props.alpha
  );
}

bool entity::colliding_with(const entity &other) const noexcept {
  return _props.position.x() < other._props.position.x() + other._props.size.width() &&
         _props.position.x() + _props.size.width() > other._props.position.x() &&
         _props.position.y() < other._props.position.y() + other._props.size.height() &&
         _props.position.y() + _props.size.height() > other._props.position.y();
}

void entity::set_props(entityprops props) noexcept {
  _props = std::move(props);
}

void entity::set_placement(int32_t x, int32_t y, anchor) noexcept {
  int32_t _x{x}, _y{y};
  _props.position.set(_x, _y);
}

void entity::set_entitymanager(std::shared_ptr<entitymanager> entitymanager) noexcept {
  _entitymanager = std::move(entitymanager);
}

void entity::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept {
  _resourcemanager = std::move(resourcemanager);
}

void entity::set_velocity(const math::vector2d &velocity) noexcept {
  UNUSED(velocity);
  // _props.velocity = velocity;
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

void entity::set_action(const std::string_view action) {
  if (_props.action != action) {
    _props.action = action;
    _props.frame = 0;
    _props.last_frame = SDL_GetTicks();
  }
}

void entity::unset_action() {
  std::string().swap(_props.action);
  _props.frame = 0;
  _props.last_frame = SDL_GetTicks();
}

std::string entity::action() const { return _props.action; }

geometry::size entity::size() const noexcept { return _props.size; }

bool entity::visible() const noexcept { return _props.visible; }

void entity::on_email(const std::string &message) {
  if (!_onmail) {
    return;
  }

  _onmail(shared_from_this(), message);
}
