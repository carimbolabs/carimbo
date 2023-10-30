#include "scriptengine.hpp"

void scriptengine::exec() {
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

  const auto script = file::read("scripts/main.lua");

  _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}