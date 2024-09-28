#pragma once

#include "common.hpp"

#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"

namespace framework {
struct keyframe {
  geometry::rect frame;
  uint64_t duration;

  keyframe() = default;

  keyframe(const geometry::rect &frame, uint64_t duration)
      : frame(frame), duration(duration) {}
};

struct entityprops {
public:
  std::shared_ptr<graphics::pixmap> spritesheet;
  std::map<std::string, std::vector<keyframe>> frames;
  geometry::point position;
  geometry::point pivot;
  float_t angle;
  graphics::flip flip;
  uint8_t alpha;
  std::string_view id;

  entityprops() = default;

  entityprops(std::shared_ptr<graphics::pixmap> spritesheet,
              std::map<std::string, std::vector<keyframe>> frames,
              geometry::point position = {},
              geometry::point pivot = {},
              float_t angle = 0.0f,
              graphics::flip flip = graphics::flip::none,
              uint8_t alpha = 255,
              std::string id = "")
      : spritesheet(std::move(spritesheet)),
        frames(std::move(frames)),
        position(std::move(position)),
        pivot(std::move(pivot)),
        angle(angle),
        flip(flip),
        alpha(alpha),
        id(std::move(id)) {}
};
}
