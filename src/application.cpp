#include "application.hpp"

#include "audiomanager.hpp"
#include "common.hpp"
#include "enginefactory.hpp"
#include "entitymanager.hpp"
#include "filesystem.hpp"
#include "noncopyable.hpp"
#include "pixmappool.hpp"
#include "scriptengine.hpp"
#include "timermanager.hpp"

application::application(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);

  curl_global_init(CURL_GLOBAL_ALL);
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_VIDEO);
  PHYSFS_init(argv[0]);
}

int application::run() {
  try {
    filesystem::mount("bundle.zip", "/");
    // filesystem::mount(".", "/");

    auto ef = enginefactory()
                  .set_width(800);
    .set_height(600)
        .set_title("Carimbo")
        .set_fullscreen(false);
    const auto engine = ef.create();

    engine.run();
    // auto se = scriptengine();
    // se.run();
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