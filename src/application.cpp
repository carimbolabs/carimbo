#include "application.hpp"

application::application(int argc, char **argv) {
  curl_global_init(CURL_GLOBAL_ALL);
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);
  PHYSFS_init(argv[0]);
}

int application::run() {
  try {
    filesystem::mount("bundle.zip", "/");
    window w("Carimbo", 640, 480);
    const auto r = w.create_renderer();
    auto pp = pixmappool(r);
    const auto p = pp.get("image.avif");

    bool quit = false;
    SDL_Event e;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      SDL_RenderClear(*r);

      p->draw(0, 0);

      SDL_RenderPresent(*r);

      SDL_Delay(1000 / 60);
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

application::~application() {
  PHYSFS_deinit();
  SDL_Quit();
  curl_global_cleanup();
}