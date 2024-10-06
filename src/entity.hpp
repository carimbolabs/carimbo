#pragma once

#include "common.hpp"

#include "anchor.hpp"
#include "entityprops.hpp"
#include "pixmap.hpp"
#include "vector2d.hpp"

namespace framework {
class entity : public std::enable_shared_from_this<entity> {
public:
  virtual ~entity();

  static std::shared_ptr<entity> create(const entityprops &&props);

  uint64_t id() const;

  const std::string kind() const;

  virtual void update(double delta) noexcept;

  virtual void draw() const noexcept;

  bool colliding_with(const entity &other) const noexcept;

  const entityprops props() const noexcept;

  void set_props(entityprops props) noexcept;

  int32_t x() const noexcept;

  int32_t y() const noexcept;

  void set_placement(int32_t x, int32_t y, anchor anchor = anchor::none) noexcept;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager);

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn);

  void set_onmail(const std::function<void(std::shared_ptr<entity>, const std::string &)> &fn);

  void set_velocity(const vector2d &velocity) noexcept;

  void set_pixmap(const std::string_view filename);

  void play_sound(const std::string_view filename);

  void set_flip(graphics::flip flip) noexcept;

  void set_action(const std::string_view action) noexcept;

  std::string action() const noexcept;

  void set_visible(bool visible) noexcept;

  void dispatch(const std::string &message);

private:
  friend class entitymanager;

  entity(const entityprops &&props);

  std::string _id;
  entityprops _props;
  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::function<void(std::shared_ptr<entity>)> _fn;
  std::function<void(std::shared_ptr<entity>, const std::string &)> _onmail;
};
}
