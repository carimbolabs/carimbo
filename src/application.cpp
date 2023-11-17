#include "application.hpp"

#include "audiodevice.hpp"
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
#if SANDBOX
    // filesystem::mount("../assets/sandbox", "/");
    filesystem::mount("/opt/workspace/carimbolabs/snake", "/");
#else
    filesystem::mount("bundle.7z", "/");
#endif

    auto se = scriptengine();
    se.run();
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