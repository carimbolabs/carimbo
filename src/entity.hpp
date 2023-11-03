#pragma once
#ifndef _entity_hpp
#define _entity_hpp

#include "common.hpp"

class engine;

class entity : public std::enable_shared_from_this<entity> {
public:
  explicit entity(const std::string &id);

  virtual ~entity() = default;

  std::string get_id() const;

  virtual void update();

  virtual void draw() const;

  void set_x(int32_t x);

  int32_t x() const;

  void set_y(int32_t y);

  int32_t y() const;

  void set_position(int32_t x, int32_t y);

  void set_pixmappool(std::shared_ptr<pixmappool> pixmappool);

  void set_onupdate(const std::function<void(std::shared_ptr<entity>)> &fn);

  void set_pixmap(const std::string &filename);

private:
  std::string _id;
  std::shared_ptr<pixmap> _pixmap;
  int32_t _x;
  int32_t _y;

  std::shared_ptr<engine> _engine;
  std::shared_ptr<pixmappool> _pixmappool;

  std::function<void(std::shared_ptr<entity>)> _fn;
};

#endif
