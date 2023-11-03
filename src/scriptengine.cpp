#include "scriptengine.hpp"

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua.new_enum("KeyEvent",
               "w", keyevent::w,
               "a", keyevent::a,
               "s", keyevent::s,
               "d", keyevent::d);

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "spawn", &engine::spawn,
      "is_keydown", &engine::is_keydown);

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create);

  lua.new_usertype<entity>(
      "Entity",
      "on_update", &entity::set_callback);

  lua.script(R"(
    local engine = EngineFactory.new()
      :set_title("Carimbo")
      :set_width(800)
      :set_height(600)
      :create()

    local entity = engine:spawn()
    entity:on_update(function(self)
      print("A is pressed? " .. tostring(engine:is_keydown(KeyEvent.a)))
    end)

    engine:run()
  )");

  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}