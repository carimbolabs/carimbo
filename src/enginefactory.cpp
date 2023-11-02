#include "enginefactory.hpp"

enginefactory &enginefactory::set_title(const std::string &title) {
  _title = title;
  return *this;
}

enginefactory &enginefactory::set_width(int32_t width) {
  _width = width;
  return *this;
}

enginefactory &enginefactory::set_height(int32_t height) {
  _height = height;
  return *this;
}

enginefactory &enginefactory::set_fullscreen(bool fullscreen) {
  _fullscreen = fullscreen;
  return *this;
}

std::shared_ptr<engine> enginefactory::create() {
  const auto em = std::make_shared<eventmanager>();
  const auto e = engine::create(_title, _width, _height, _fullscreen);
  e->set_eventmanager(em);
  em->add_receiver(e);

  return e;
}