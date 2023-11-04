#pragma once
#ifndef _entity_hpp
#define _entity_hpp

#include "common.hpp"

class engine;

class entity : public std::enable_shared_from_this<entity> {
public:
  virtual ~entity();

  static std::shared_ptr<entity> create(const std::string &id);

  static void destroy(const std::shared_ptr<entity> entity);

  std::string get_id() const;

  virtual void update();

  virtual void draw() const;

  void set_x(int32_t x);

  int32_t x() const;

  void set_y(int32_t y);

  int32_t y() const;

  void const set_angle(const double angle);

  const double angle() const;

  void set_entitymanager(std::shared_ptr<entitymanager> entitymanager);

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn);

  void set_pixmap(const std::string &filename);

private:
  entity(const std::string &id);

  std::string _id;
  std::shared_ptr<pixmap> _pixmap;
  int32_t _x;
  int32_t _y;
  double _angle;

  std::shared_ptr<entitymanager> _entitymanager;
  std::shared_ptr<resourcemanager> _resourcemanager;

  std::function<void(std::shared_ptr<entity>)> _fn;
};

#endif
