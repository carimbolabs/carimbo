#pragma once

#include "common.hpp"
#include "entitymanager.hpp"
#include "entityprops.hpp"
#include "flip.hpp"
#include "vector2d.hpp"
#include <string_view>

namespace framework {
class entity : public std::enable_shared_from_this<entity> {
public:
  explicit entity(entityprops &&props) noexcept;
  ~entity() noexcept;

  static std::shared_ptr<entity> create(entityprops &&props);

  uint64_t id() const noexcept;
  std::string_view kind() const noexcept;

  virtual void update(float_t delta) noexcept;
  virtual void draw() const noexcept;

  entityprops &props() noexcept;
  const entityprops &props() const noexcept;
  void set_props(entityprops props) noexcept;

  int32_t x() const noexcept;
  int32_t y() const noexcept;

  void move(float_t x_velocity, float_t y_velocity);
  math::vector2d get_velocity() const noexcept;

  void set_placement(int32_t x, int32_t y) noexcept;

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept;
  void set_onanimationfinished(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept;
  void set_onmail(const std::function<void(std::shared_ptr<entity>, const std::string &)> &fn) noexcept;

  void set_pixmap(std::string_view filename);
  void play_sound(std::string_view filename);
  void set_flip(graphics::flip flip) noexcept;
  void set_action(std::string_view action);
  void unset_action();

  std::string_view action() const noexcept;
  geometry::size size() const noexcept;
  bool visible() const noexcept;

  void on_email(const std::string &message);

private:
  friend class entitymanager;

  entityprops _props;
  std::function<void(std::shared_ptr<entity>)> _onupdate;
  std::function<void(std::shared_ptr<entity>)> _onanimationfinished;
  std::function<void(std::shared_ptr<entity>, const std::string &)> _onmail;
};
}
