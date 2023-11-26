#pragma once

#include "common.hpp"

#include "point.hpp"

namespace framework {
class entity : public std::enable_shared_from_this<entity> {
public:
  virtual ~entity();

  static std::shared_ptr<entity> create(const std::string &id);

  std::string id() const;

  virtual void update();

  virtual void draw() const;

  void set_x(int32_t x);

  int32_t x() const;

  void set_y(int32_t y);

  int32_t y() const;

  void move(int32_t x, int32_t y);

  int32_t width() const;

  int32_t height() const;

  void scale(double factor);

  void set_angle(const double_t angle);

  double_t angle() const;

  void set_alpha(const uint8_t alpha);

  uint8_t alpha() const;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager);

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn);

  void set_pixmap(const std::string &filename);

  void play_sound(const std::string &filename);

private:
  entity(const std::string &id);

  std::string _id;
  std::shared_ptr<graphics::pixmap> _pixmap;
  geometry::point _point;
  double_t _angle;
  uint8_t _alpha;

  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<resourcemanager> _resourcemanager;

  std::function<void(std::shared_ptr<entity>)> _fn;
};
}
