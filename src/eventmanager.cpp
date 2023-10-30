#include "eventmanager.hpp"

void eventmanager::update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      exit(0);
      break;
    }
    // if (event.type == SDL_QUIT) {
    //   _running = false;
    // }
  }
}