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

  const auto script = R"(
    local m = motor.new()

    m:init("Carimbo", 800, 600)
    m:run()
  )";

  _lua.script(script);
}