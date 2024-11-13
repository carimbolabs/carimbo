#pragma once

#include "common.hpp"
#include <cstdint>

namespace geometry {
class size {
public:
  size() noexcept = default;
  size(int32_t width, int32_t height) noexcept;
  size(float_t scale, int32_t width, int32_t height) noexcept;
  size(const size &other) noexcept;
  ~size() = default;

  void set_scale(float_t scale) noexcept;
  float_t scale() const noexcept;
  void set_width(int32_t width) noexcept;
  int32_t width() const noexcept;
  void set_height(int32_t height) noexcept;
  int32_t height() const noexcept;

  size resized() const noexcept;

  bool operator==(const size &rhs) const noexcept;
  bool operator!=(const size &rhs) const noexcept;

  friend void from_json(const nlohmann::json &j, size &s) noexcept;

private:
  float_t _scale{0.0};
  int32_t _width{0};
  int32_t _height{0};
};

inline void from_json(const nlohmann::json &j, size &s) noexcept {
  j.at("scale").get_to(s._scale);
  j.at("width").get_to(s._width);
  j.at("height").get_to(s._height);
}
}
