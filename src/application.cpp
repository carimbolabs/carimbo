#include "application.hpp"

#include "common.hpp"
#include "filesystem.hpp"
#include "scriptengine.hpp"

using namespace framework;

application::application(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);

  SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER | SDL_INIT_VIDEO);

  PHYSFS_init(argv[0]);
}

int application::run() {
  try {
#if SANDBOX
    // storage::filesystem::mount("../assets/sandbox", "/");
    storage::filesystem::mount("../../megarick"sv, "/"sv);
#else
    storage::filesystem::mount("bundle.7z"sv, "/"sv);
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
