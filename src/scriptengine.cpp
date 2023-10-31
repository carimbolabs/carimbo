#include "scriptengine.hpp"

void scriptengine::run() {
  _lua.open_libraries(
      sol::lib::base,
      sol::lib::package,
      sol::lib::string,
      sol::lib::math,
      sol::lib::table,
      sol::lib::debug);

  _lua.new_usertype<motor>("motor",
                           "new", sol::factories(&motor::make),
                           "init", &motor::init,
                           "run", &motor::run);

  _lua.set_function("set", &timermanager::set, &_timermanager);

  const auto script = R"(
    local motor = motor.new()
    motor:init("Carimbo", 800, 600)
    motor:run()
  )";

  // const auto script = io::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));

  _lua.script(script);
}