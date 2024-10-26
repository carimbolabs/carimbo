#pragma once

#include "anchor.hpp"
#include "common.hpp"
#include "entitymanager.hpp"
#include "entityprops.hpp"
#include "flip.hpp"
#include "resourcemanager.hpp"
#include "vector2d.hpp"

namespace framework {
class entity : public std::enable_shared_from_this<entity> {
public:
  virtual ~entity();

  static std::shared_ptr<entity> create(const entityprops &&props);

  uint64_t id() const noexcept;

  std::string kind() const;

  virtual void update(double_t delta);

  virtual void draw() const;

  bool colliding_with(const entity &other) const noexcept;

  entityprops props() const;

  void set_props(entityprops props) noexcept;

  int32_t x() const noexcept;

  int32_t y() const noexcept;

  void set_placement(int32_t x, int32_t y, anchor anchor = anchor::none) noexcept;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager) noexcept;

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept;

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept;

  void set_onanimationfinished(const std::function<void(std::shared_ptr<entity>)> &fn) noexcept;

  void set_onmail(const std::function<void(std::shared_ptr<entity>, const std::string &)> &fn) noexcept;

  void set_velocity(const math::vector2d &velocity) noexcept;

  void set_pixmap(std::string_view filename);

  void play_sound(std::string_view filename);

  void set_flip(graphics::flip flip) noexcept;

  void set_action(std::string_view action);

  void unset_action();

  std::string action() const;

  geometry::size size() const noexcept;

  bool visible() const noexcept;

  void dispatch(const std::string &message);

private:
  friend class entitymanager;

  entity(const entityprops &&props);

  entityprops _props;
  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::function<void(std::shared_ptr<entity>)> _onupdate;
  std::function<void(std::shared_ptr<entity>)> _onanimationfinished;
  std::function<void(std::shared_ptr<entity>, const std::string &)> _onmail;
};
}
