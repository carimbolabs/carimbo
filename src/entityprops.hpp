#pragma once

#include "common.hpp"
#include "flip.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"

namespace framework {

using body_ptr = std::unique_ptr<cpBody, void (*)(cpBody *)>;

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
  uint8_t alpha{255};
  bool visible{true};
  geometry::point position{};
  geometry::point pivot{};
  geometry::size size{};
  std::string kind{};
  std::string action{};
  graphics::flip flip{graphics::flip::none};
  std::shared_ptr<graphics::pixmap> spritesheet{};
  std::map<std::string, std::vector<keyframe>> animations{};
  body_ptr body{nullptr, [](cpBody *) {}};

  entityprops(const entityprops &) = delete;
  entityprops &operator=(const entityprops &) = delete;
  entityprops(entityprops &&) noexcept = default;
  entityprops &operator=(entityprops &&) noexcept = default;
};

}
