#pragma once

#include "common.hpp"
#include "widget.hpp"

namespace graphics {

class label : public widget {
public:
  label() = default;
  virtual ~label() = default;

  void set_font(const std::shared_ptr<font> &font) noexcept;
  void set_placement(const geometry::point &position) noexcept;

  void set_text(std::string_view text) noexcept;
  void set_text_with_position(std::string_view text, const geometry::point &position) noexcept;

  void update(float_t delta) noexcept override;
  void draw() const noexcept override;

private:
  std::shared_ptr<font> _font{};
  std::string _text{};
  geometry::point _position{};
};
}
