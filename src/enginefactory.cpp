#include "enginefactory.hpp"

#include "audiodevice.hpp"
#include "engine.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "resourcemanager.hpp"
#include "scenemanager.hpp"
#include "window.hpp"

using namespace framework;

enginefactory &enginefactory::set_title(const std::string &title) noexcept {
  _title = title;
  return *this;
}

enginefactory &enginefactory::set_width(int32_t width) noexcept {
  _width = width;
  return *this;
}

enginefactory &enginefactory::set_height(int32_t height) noexcept {
  _height = height;
  return *this;
}

enginefactory &enginefactory::set_gravity(float_t gravity) noexcept {
  _gravity = gravity;
  return *this;
}

enginefactory &enginefactory::set_fullscreen(bool fullscreen) noexcept {
  _fullscreen = fullscreen;
  return *this;
}

std::shared_ptr<engine> enginefactory::create() {
  auto window = std::make_shared<graphics::window>(_title, _width, _height, _fullscreen);
  auto renderer = window->create_renderer();
  auto audiodevice = std::make_shared<audio::audiodevice>();
  auto eventmanager = std::make_shared<input::eventmanager>();
  auto entitymanager = std::make_shared<framework::entitymanager>(_gravity);
  auto statemanager = std::make_shared<framework::statemanager>();
  auto resourcemanager = std::make_shared<framework::resourcemanager>(renderer, audiodevice);
  auto scenemanager = std::make_shared<framework::scenemanager>(resourcemanager->pixmappool());
  auto fontfactory = std::make_shared<graphics::fontfactory>(resourcemanager);
  auto engine = std::make_shared<framework::engine>();

  engine->set_window(std::move(window));
  engine->set_renderer(std::move(renderer));
  engine->set_audiodevice(std::move(audiodevice));
  engine->set_eventmanager(std::move(eventmanager));
  engine->set_entitymanager(std::move(entitymanager));
  engine->set_statemanager(std::move(statemanager));
  engine->set_resourcemanager(std::move(resourcemanager));
  engine->set_scenemanager(std::move(scenemanager));
  engine->set_fontfactory(std::move(fontfactory));

  engine->eventmanager()->add_receiver(engine->entitymanager());
  engine->eventmanager()->add_receiver(engine);
  engine->eventmanager()->add_receiver(engine->statemanager());

  engine->entitymanager()->set_resourcemanager(engine->resourcemanager());

  return engine;
}
