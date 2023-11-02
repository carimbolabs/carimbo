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
  const auto w = std::make_shared<window>(_title, _width, _height, _fullscreen);
  const auto r = w->create_renderer();
  const auto em1 = std::make_shared<eventmanager>();
  const auto em2 = std::make_shared<entitymanager>();

  const auto e = std::make_shared<engine>();

  e->set_window(w);
  e->set_renderer(r);
  e->set_eventmanager(em1);
  e->set_entitymanager(em2);

  em1->add_receiver(e);

  return e;
}