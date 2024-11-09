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
  geometry::point offset;
  uint64_t duration{};
  bool singleshoot{};

  keyframe() noexcept = default;
  keyframe(const geometry::rect &rect, uint64_t duration, bool singleshoot, const geometry::point &offset) noexcept
      : frame(rect), offset(offset), duration(duration), singleshoot(singleshoot) {}
};

struct entityprops {
  uint64_t id{};
  uint32_t frame{};
  uint32_t last_frame{};
  double_t angle{};
  double_t scale{1.0};
  uint8_t alpha{255};
  bool visible{true};
  geometry::point position{};
  geometry::point pivot{};
  geometry::size size{};
  // math::vector2d velocity;
  std::string kind{};
  std::string action{};
  graphics::flip flip{graphics::flip::none};
  std::shared_ptr<graphics::pixmap> spritesheet{};
  std::map<std::string, std::vector<keyframe>> animations{};
  // b2BodyId body{};

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
      bool>;

  attribute_t get(const std::string &name) const {
    if (name == "id")
      return id;
    else if (name == "angle")
      return angle;
    else if (name == "scale")
      return scale;
    else if (name == "alpha")
      return alpha;
    else if (name == "visible")
      return visible;
    else if (name == "position")
      return position;
    else if (name == "pivot")
      return pivot;
    else if (name == "size")
      return size;
    else if (name == "kind")
      return kind;
    else if (name == "action")
      return action;
    else if (name == "flip")
      return flip;
    else if (name == "spritesheet")
      return spritesheet;
    else if (name == "animations")
      return animations;
    throw std::invalid_argument("Invalid property name");
  }

  void set(const std::string &name, const attribute_t &value) {
    if (name == "id")
      id = std::get<uint64_t>(value);
    else if (name == "frame")
      frame = std::get<uint32_t>(value);
    else if (name == "last_frame")
      last_frame = std::get<uint32_t>(value);
    else if (name == "angle")
      angle = std::get<double_t>(value);
    else if (name == "scale")
      scale = std::get<double_t>(value);
    else if (name == "alpha")
      alpha = std::get<uint8_t>(value);
    else if (name == "visible")
      visible = std::get<bool>(value);
    else if (name == "position")
      position = std::get<geometry::point>(value);
    else if (name == "pivot")
      pivot = std::get<geometry::point>(value);
    else if (name == "size")
      size = std::get<geometry::size>(value);
    else if (name == "kind")
      kind = std::get<std::string>(value);
    else if (name == "action")
      action = std::get<std::string>(value);
    else if (name == "flip")
      flip = std::get<graphics::flip>(value);
    else if (name == "spritesheet")
      spritesheet = std::get<std::shared_ptr<graphics::pixmap>>(value);
    else if (name == "animations")
      animations = std::get<std::map<std::string, std::vector<keyframe>>>(value);
    else
      throw std::invalid_argument("Invalid property name");
  }
};

}
