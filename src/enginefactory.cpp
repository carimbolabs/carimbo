#include "enginefactory.hpp"

#include "audiodevice.hpp"
#include "engine.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "resourcemanager.hpp"
#include "scenemanager.hpp"
#include "window.hpp"

using namespace framework;

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
  const auto w = std::make_shared<graphics::window>(_title, _width, _height, _fullscreen);
  const auto r = w->create_renderer();
  const auto ad = std::make_shared<audio::audiodevice>();
  const auto em1 = std::make_shared<input::eventmanager>();
  const auto em2 = std::make_shared<framework::entitymanager>();
  const auto em3 = std::make_shared<framework::statemanager>();
  const auto rm = std::make_shared<framework::resourcemanager>(r, ad);
  const auto sm = std::make_shared<framework::scenemanager>(rm->pixmappool());
  const auto ff = std::make_shared<graphics::fontfactory>(rm);
  const auto e = std::make_shared<framework::engine>();

  e->set_window(std::move(w));
  e->set_renderer(std::move(r));
  e->set_audiodevice(std::move(ad));
  e->set_eventmanager(std::move(em1));
  e->set_entitymanager(std::move(em2));
  e->set_statemanager(std::move(em3));
  e->set_resourcemanager(std::move(rm));
  e->set_scenemanager(std::move(sm));
  e->set_fontfactory(std::move(ff));

  em1->add_receiver(std::move(em2));
  em1->add_receiver(std::move(e));
  em1->add_receiver(std::move(em3));

  em2->set_resourcemanager(std::move(rm));

  return e;
}
