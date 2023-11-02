#include "engine.hpp"

// engine::engine() : _eventmanager(std::make_shared<eventmanager>()) {
// }

engine::engine(std::string_view title, int32_t width, int32_t height, bool fullscreen) : _running(true) {
  _window = std::make_shared<window>(title, width, height, fullscreen);
  _renderer = _window->create_renderer();

  //

  add_loopable(std::make_shared<framerate>());
}

std::shared_ptr<engine> engine::create(const std::string &title, int32_t width, int32_t height, bool fullscreen) {
  return std::shared_ptr<engine>(new engine(title, width, height, fullscreen));
}

// void engine::ignite(std::string_view title, int32_t width, int32_t height, bool fullscreen) {
//   _running = true;
//   _window = std::make_shared<window>(title, width, height, fullscreen);
//   _renderer = _window->create_renderer();

//   // _eventmanager->add_receiver(instance());

//   add_loopable(std::make_shared<framerate>());
// }

void engine::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(loopable);
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

void engine::set_eventmanager(std::shared_ptr<eventmanager> eventmanager) {
  _eventmanager = eventmanager;
  // _eventmanager->add_receiver(std::make_shared<engine>(*this));
}

const std::shared_ptr<eventmanager> engine::get_eventmanager() const {
  return _eventmanager;
}

void engine::on_quit() {
  _running = false;
}

void engine::on_keydown(const keyevent &event) {
  std::cout << "on_keydown: " << static_cast<int32_t>(event) << std::endl;
  std::cout << "is_equal: " << (event == keyevent::a) << std::endl;
  // std::cout << "event.key: " << event.key << std::endl;
}