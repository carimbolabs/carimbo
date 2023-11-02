#include "engine.hpp"

engine::engine() : _running(true) {
  add_loopable(std::make_shared<framerate>());
}

void engine::run() {
  while (_running) {
    const auto now = SDL_GetTicks();

    _eventmanager->update();
    _renderer->begin();
    // _scenegraph->render();
    _renderer->end();

    const auto delta = SDL_GetTicks() - now;

    std::for_each(_loopables.begin(), _loopables.end(),
                  std::bind(&loopable::loop, std::placeholders::_1, delta));
  }
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

void engine::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(loopable);
}

void engine::on_quit() {
  _running = false;
}

void engine::on_keydown(const keyevent &event) {
  std::cout << "on_keydown: " << static_cast<int32_t>(event) << std::endl;
  std::cout << "is_equal: " << (event == keyevent::a) << std::endl;
}