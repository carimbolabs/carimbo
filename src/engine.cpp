#include "engine.hpp"

#include "audiodevice.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "framerate.hpp"
#include "loopable.hpp"
#include "renderer.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"
#include "window.hpp"

using namespace framework;

engine::engine() : _running(true) {
  add_loopable(std::make_shared<framerate>());
}

void engine::set_window(std::shared_ptr<graphics::window> window) {
  _window = std::move(window);
}

std::shared_ptr<graphics::window> engine::window() const {
  return _window;
}

void engine::set_renderer(std::shared_ptr<graphics::renderer> renderer) {
  _renderer = std::move(renderer);
}

std::shared_ptr<graphics::renderer> engine::renderer() const {
  return _renderer;
}

void engine::set_audiodevice(std::shared_ptr<audio::audiodevice> audiodevice) {
  _audiodevice = std::move(audiodevice);
}

std::shared_ptr<audio::audiodevice> engine::audiodevice() const {
  return _audiodevice;
}

void engine::set_eventmanager(std::shared_ptr<input::eventmanager> eventmanager) {
  _eventmanager = std::move(eventmanager);
}

std::shared_ptr<input::eventmanager> engine::eventmanager() const {
  return _eventmanager;
}

void engine::set_entitymanager(std::shared_ptr<framework::entitymanager> entitymanager) {
  _entitymanager = std::move(entitymanager);
}

std::shared_ptr<framework::entitymanager> engine::entitymanager() const {
  return _entitymanager;
}

void engine::set_resourcemanager(std::shared_ptr<framework::resourcemanager> resourcemanager) {
  _resourcemanager = std::move(resourcemanager);
}

std::shared_ptr<framework::resourcemanager> engine::resourcemanager() const {
  return _resourcemanager;
}

std::shared_ptr<audio::soundmanager> engine::soundmanager() const {
  return _resourcemanager->soundmanager();
}

void engine::set_statemanager(std::shared_ptr<framework::statemanager> statemanager) {
  _statemanager = std::move(statemanager);
}

std::shared_ptr<framework::statemanager> engine::statemanager() const {
  return _statemanager;
}

void engine::set_scenemanager(std::shared_ptr<framework::scenemanager> scenemanager) {
  _scenemanager = std::move(scenemanager);
}

std::shared_ptr<framework::scenemanager> engine::scenemanager() const {
  return _scenemanager;
}

void engine::set_fontfactory(std::shared_ptr<graphics::fontfactory> fontfactory) {
  _fontfactory = std::move(fontfactory);
}

std::shared_ptr<graphics::fontfactory> engine::fontfactory() const {
  return _fontfactory;
}

void engine::prefetch(const std::vector<std::string> &filenames) {
  _resourcemanager->prefetch(filenames);
}

void engine::flush() const {
  _resourcemanager->pixmappool()->flush();
  _resourcemanager->soundmanager()->flush();
}

bool engine::is_keydown(const input::keyevent &event) const {
  return _statemanager->is_keydown(event);
}

std::shared_ptr<entity> engine::spawn(const std::string &kind) {
  auto entity = _entitymanager->spawn(kind);
  entity->set_entitymanager(_entitymanager);
  entity->set_resourcemanager(_resourcemanager);
  return entity;
}

void engine::destroy(const std::shared_ptr<entity> entity) {
  _entitymanager->destroy(entity);
}

void engine::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(std::move(loopable));
}

void engine::set_scene(const std::string_view name) {
  _scenemanager->load(name);
}

#ifdef EMSCRIPTEN
template <class T>
inline void run(void *arg) {
  reinterpret_cast<T *>(arg)->_loop();
}
#endif

void engine::run() {
#ifdef EMSCRIPTEN
  emscripten_set_main_loop_arg(::run<engine>, this, 0, true);
#else
  while (_running) {
    _loop();
  }
#endif
}

void engine::_loop() {
  static auto prior = SDL_GetTicks();
  const auto now = SDL_GetTicks();
  const auto delta = now - prior;

  prior = now;

  _resourcemanager->update(delta);
  _scenemanager->update(delta);
  _eventmanager->update(delta);
  _entitymanager->update(delta);

  for (auto &loopable : _loopables) {
    loopable->loop(delta);
  }

  _renderer->begin();
  _scenemanager->draw();
  _entitymanager->draw();
  _renderer->end();
}

int32_t engine::width() const { return _window->width(); }

int32_t engine::height() const { return _window->height(); }

void engine::on_quit() noexcept { _running = false; }
