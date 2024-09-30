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

using namespace framework;

application::application(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);

  SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO);
  // SDL_EventState(SDL_CONTROLLERDEVICEADDED, SDL_ENABLE);
  // SDL_EventState(SDL_CONTROLLERDEVICEREMOVED, SDL_ENABLE);

  PHYSFS_init(argv[0]);
}

int application::run() {
  try {
#if SANDBOX
    // storage::filesystem::mount("../assets/sandbox", "/");
    storage::filesystem::mount("/opt/workspace/khromatizo/henrique", "/");
#else
    storage::filesystem::mount("bundle.7z", "/");
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
}
