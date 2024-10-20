#pragma once

#include "common.hpp"

#include "font.hpp"
#include "point.hpp"

namespace graphics {
class label : protected std::enable_shared_from_this<label> {
public:
  label() = delete;
  label(std::shared_ptr<font> font, const std::string &text, const geometry::point &position);
  ~label() = default;

  static std::shared_ptr<label> create(std::shared_ptr<font> font, const std::string &text, const geometry::point &position);

  void set(const std::string &text);

  void set(const std::string &text, const geometry::point &position);

  void draw() const;

  void dispose(); // ???

private:
  std::shared_ptr<font> _font;
  std::string _text;
  geometry::point _position;
};
}
