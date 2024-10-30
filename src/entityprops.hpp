#pragma once

#include "common.hpp"
#include "flip.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"
#include "vector2d.hpp"

namespace framework {
struct keyframe {
  geometry::rect frame;
  uint64_t duration{};
  bool singleshoot{};
  geometry::point offset;

  keyframe() noexcept = default;
  keyframe(const geometry::rect &rect, uint64_t duration, bool singleshoot, const geometry::point &offset) noexcept
      : frame(rect), duration(duration), singleshoot(singleshoot), offset(offset) {}
};

struct entityprops {
  uint64_t id{};
  std::string kind;
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> animations;
  geometry::point position;
  geometry::point pivot;
  geometry::size size;
  float_t angle{};
  double_t scale{1.0};
  graphics::flip flip{graphics::flip::none};
  uint8_t alpha{255};
  std::string action;
  uint32_t frame{};
  uint32_t last_frame{};
  math::vector2d velocity;
  bool visible{true};
  b2BodyId body;

  entityprops() noexcept = default;

  using attribute_t = std::variant<
      uint64_t,
      std::string,
      std::shared_ptr<graphics::pixmap>,
      std::map<std::string, std::vector<keyframe>>,
      geometry::point,
      geometry::size,
      float_t,
      double_t,
      graphics::flip,
      uint8_t,
      uint32_t,
      math::vector2d,
      bool,
      b2BodyId>;

  attribute_t get(const std::string &name) const {
    static const std::map<std::string, std::function<attribute_t(const entityprops &)>> getters{
        {"id", [](const entityprops &e) { return e.id; }},
        {"kind", [](const entityprops &e) { return e.kind; }},
        {"spritesheet", [](const entityprops &e) { return e.spritesheet; }},
        {"animations", [](const entityprops &e) { return e.animations; }},
        {"position", [](const entityprops &e) { return e.position; }},
        {"pivot", [](const entityprops &e) { return e.pivot; }},
        {"size", [](const entityprops &e) { return e.size; }},
        {"angle", [](const entityprops &e) { return e.angle; }},
        {"scale", [](const entityprops &e) { return e.scale; }},
        {"flip", [](const entityprops &e) { return e.flip; }},
        {"alpha", [](const entityprops &e) { return e.alpha; }},
        {"action", [](const entityprops &e) { return e.action; }},
        {"frame", [](const entityprops &e) { return e.frame; }},
        {"last_frame", [](const entityprops &e) { return e.last_frame; }},
        {"velocity", [](const entityprops &e) { return e.velocity; }},
        {"visible", [](const entityprops &e) { return e.visible; }},
        {"body", [](const entityprops &e) { return e.body; }},
    };
    return getters.at(name)(*this);
  }

  void set(const std::string &name, const attribute_t &value) {
    static const std::map<std::string, std::function<void(entityprops &, const attribute_t &)>> setters{
        {"id", [](entityprops &e, const attribute_t &v) { e.id = std::get<uint64_t>(v); }},
        {"kind", [](entityprops &e, const attribute_t &v) { e.kind = std::get<std::string>(v); }},
        {"spritesheet", [](entityprops &e, const attribute_t &v) { e.spritesheet = std::get<std::shared_ptr<graphics::pixmap>>(v); }},
        {"animations", [](entityprops &e, const attribute_t &v) { e.animations = std::get<std::map<std::string, std::vector<keyframe>>>(v); }},
        {"position", [](entityprops &e, const attribute_t &v) { e.position = std::get<geometry::point>(v); }},
        {"pivot", [](entityprops &e, const attribute_t &v) { e.pivot = std::get<geometry::point>(v); }},
        {"size", [](entityprops &e, const attribute_t &v) { e.size = std::get<geometry::size>(v); }},
        {"angle", [](entityprops &e, const attribute_t &v) { e.angle = std::get<float_t>(v); }},
        {"scale", [](entityprops &e, const attribute_t &v) { e.scale = std::get<double_t>(v); }},
        {"flip", [](entityprops &e, const attribute_t &v) { e.flip = std::get<graphics::flip>(v); }},
        {"alpha", [](entityprops &e, const attribute_t &v) { e.alpha = std::get<uint8_t>(v); }},
        {"action", [](entityprops &e, const attribute_t &v) { e.action = std::get<std::string>(v); }},
        {"frame", [](entityprops &e, const attribute_t &v) { e.frame = std::get<uint32_t>(v); }},
        {"last_frame", [](entityprops &e, const attribute_t &v) { e.last_frame = std::get<uint32_t>(v); }},
        {"velocity", [](entityprops &e, const attribute_t &v) { e.velocity = std::get<math::vector2d>(v); }},
        {"visible", [](entityprops &e, const attribute_t &v) { e.visible = std::get<bool>(v); }},
        {"body", [](entityprops &e, const attribute_t &v) { e.body = std::get<b2BodyId>(v); }},
    };
    setters.at(name)(*this, value);
  }
};
}
