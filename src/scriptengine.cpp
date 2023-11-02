#include "scriptengine.hpp"

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries(sol::lib::base);

  sol::usertype<engine> engine_type = lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run);

  sol::usertype<enginefactory> enginefactory_type = lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create);

  lua.script(R"(
    local engine = EngineFactory.new()
        :set_title("Carimbo")
        :set_width(800)
        :set_height(600)
        :set_fullscreen(false)
        :create()

    engine:run()
  )");

  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}