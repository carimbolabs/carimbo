#include "motor.hpp"

motor::motor() : _eventmanager(std::make_shared<eventmanager>()) {
}

void motor::init(std::string_view title, int32_t width, int32_t height, bool fullscreen) {
  _running = true;
  _window = std::make_shared<window>(title, width, height, fullscreen);
  _renderer = _window->create_renderer();

  _eventmanager->add_receiver(instance());

  add_loopable(std::make_shared<framerate>());
}

void motor::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(loopable);
}

void motor::run() {
  while (_running) {
    const auto now = SDL_GetTicks();

    _eventmanager->update();
    _renderer->begin();
    // scenegraph->render();
    _renderer->end();

    const auto delta = SDL_GetTicks() - now;

    std::for_each(_loopables.begin(), _loopables.end(),
                  std::bind(&loopable::loop, std::placeholders::_1, delta));

    if (delta < DELAY_MS) {
      // SDL_Delay(DELAY_MS - delta);
    }
  }
}

const std::shared_ptr<eventmanager> motor::get_eventmanager() const {
  return _eventmanager;
}

void motor::on_quit() {
  _running = false;
}

void motor::on_keydown(const keyevent &event) {
  std::cout << "on_keydown: " << static_cast<int32_t>(event) << std::endl;
  std::cout << "is_equal: " << (event == keyevent::a) << std::endl;
  // std::cout << "event.key: " << event.key << std::endl;
}