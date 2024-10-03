#pragma once

#include "common.hpp"

#include "anchor.hpp"
#include "entityprops.hpp"
#include "vector2d.hpp"
#include <string_view>

namespace framework {
class entity : public std::enable_shared_from_this<entity> {
public:
  virtual ~entity();

  static std::shared_ptr<entity> create(const entityprops &&props);

  uint64_t id() const;

  virtual void update(double delta) noexcept;

  virtual void draw() const noexcept;

  const entityprops props() const noexcept;

  void set_props(entityprops props) noexcept;

  void set_placement(int32_t x, int32_t y, anchor anchor = anchor::none) noexcept;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager);

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn);

  void set_velocity(const vector2d &velocity) noexcept;

  void set_pixmap(const std::string_view filename);

  void play_sound(const std::string_view filename);

  void set_action(const std::string_view action) noexcept;

  std::string action() const noexcept;

private:
  entity(const entityprops &&props);

  std::string _id;
  entityprops _props;
  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::function<void(std::shared_ptr<entity>)> _fn;
};
}
