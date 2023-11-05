#include "engine.hpp"

#include "entity.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "eventreceiver.hpp"
#include "framerate.hpp"
#include "loopable.hpp"
#include "noncopyable.hpp"
#include "renderer.hpp"
#include "resourcemanager.hpp"
#include "singleton.hpp"
#include "statemanager.hpp"
#include "window.hpp"

#ifdef EMSCRIPTEN
#include <emscripten.h>

template <class T>
void run(void *arg) {
  reinterpret_cast<T *>(arg)->_loop();
}
#endif

engine::engine() : _running(true) {
  add_loopable(std::make_shared<framerate>());
}

void engine::run() {
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(::run<engine>, this, 60, true);
#else
  while (_running) {
    _loop();
  }
#endif
}

void engine::_loop() {
  const auto now = SDL_GetTicks();

  _resourcemanager->update();
  _eventmanager->update();
  _entitymanager->update();
  _renderer->begin();
  _entitymanager->draw();
  // _scenegraph->render();
  _renderer->end();

  const auto delta = SDL_GetTicks() - now;

  std::for_each(_loopables.begin(), _loopables.end(),
                std::bind(&loopable::loop, std::placeholders::_1, delta));
}

void engine::set_window(std::shared_ptr<window> window) {
  _window = window;
}

const std::shared_ptr<window> engine::get_window() const {
  return _window;
}

void engine::set_renderer(std::shared_ptr<renderer> renderer) {
  _renderer = renderer;
}

const std::shared_ptr<renderer> engine::get_renderer() const {
  return _renderer;
}

void engine::set_eventmanager(std::shared_ptr<eventmanager> eventmanager) {
  _eventmanager = eventmanager;
}

const std::shared_ptr<eventmanager> engine::get_eventmanager() const {
  return _eventmanager;
}

void engine::set_entitymanager(std::shared_ptr<entitymanager> entitymanager) {
  _entitymanager = entitymanager;
}

const std::shared_ptr<entitymanager> engine::get_entitymanager() const {
  return _entitymanager;
}

void engine::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

const std::shared_ptr<resourcemanager> engine::get_resourcemanager() const {
  return _resourcemanager;
}

void engine::set_statemanager(std::shared_ptr<statemanager> statemanager) {
  _statemanager = statemanager;
}

const std::shared_ptr<statemanager> engine::get_statemanager() const {
  return _statemanager;
}

void engine::prefetch(const std::list<std::string> &filenames) {
  _resourcemanager->prefetch(filenames);
}

const bool engine::is_keydown(const keyevent &event) const {
  return _statemanager->is_keydown(event);
}

const std::shared_ptr<entity> engine::spawn() {
  const auto entity = _entitymanager->spawn();
  entity->set_entitymanager(_entitymanager);
  entity->set_resourcemanager(_resourcemanager);
  return entity;
}

void engine::destroy(const std::shared_ptr<entity> entity) {
  _entitymanager->destroy(entity);
}

void engine::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(loopable);
}

void engine::on_quit() {
  _running = false;
}
