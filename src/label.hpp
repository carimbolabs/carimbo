#pragma once

#include "common.hpp"

namespace graphics {

class label : public std::enable_shared_from_this<label> {
public:
  label() = delete;
  // label(std::shared_ptr<font> font, const std::string &text, const geometry::point &position);
  ~label() = default;

  // static std::shared_ptr<label> create(std::shared_ptr<font> font, const std::string &text, const geometry::point &position) noexcept;

  void set(const std::string &text);
  void set(std::string text, const geometry::point &position);

  void draw() const noexcept;
  void dispose() noexcept;

private:
  // std::shared_ptr<font> _font;
  std::string _text;
  geometry::point _position;
};
}
