#include "engine.hpp"

engine::engine() : _running(false) {
}

void engine::create(std::string_view title, int32_t width, int32_t height, bool fullscreen) {
  _window = std::make_shared<window>(title, width, height, fullscreen);
  _renderer = _window->create_renderer();

  _loopables.emplace_back(std::make_shared<framerate>());
}

void engine::add_loopable(std::shared_ptr<loopable> loopable) {
  _loopables.emplace_back(loopable);
}

void engine::run() {
  _running = true;

  SDL_Event event;
  while (_running) {
    _time = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        _running = false;
      }
    }

    _renderer->begin_draw();

    //

    _renderer->end_draw();

    const auto delta = SDL_GetTicks() - _time;
    if (delta < DELAY_MS) {
      SDL_Delay(DELAY_MS - delta);
    }

    std::for_each(_loopables.begin(), _loopables.end(),
                  std::bind(&loopable::loop, std::placeholders::_1, delta));
  }
}