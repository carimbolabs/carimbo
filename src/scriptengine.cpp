#include "scriptengine.hpp"

#include "engine.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"
#include "io.hpp"
#include "noncopyable.hpp"
#include "statemanager.hpp"

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua.new_enum(
      "KeyEvent",
      "w", keyevent::w,
      "a", keyevent::a,
      "s", keyevent::s,
      "d", keyevent::d);

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "prefetch", &engine::prefetch,
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
      "x", sol::property(&entity::x, &entity::set_x),
      "y", sol::property(&entity::y, &entity::set_y),
      "on_update", &entity::set_onupdate,
      "set_pixmap", &entity::set_pixmap);

  lua.script(R"(
      local engine = EngineFactory.new()
        :set_title("Carimbo")
        :set_width(800)
        :set_height(600)
        :create()

      -- engine:prefetch({"fox.avif"})

      local e = engine:spawn()

      e:set_pixmap("fox.avif")

      e:on_update(function(self)
        if engine:is_keydown(KeyEvent.w) then
          self.y = self.y - 5
        end
        
        if engine:is_keydown(KeyEvent.a) then
          self.x = self.x - 5
        end

        if engine:is_keydown(KeyEvent.s) then
          self.y = self.y + 5
        end

        if engine:is_keydown(KeyEvent.d) then
          self.x = self.x + 5
        end
      end)

      engine:run()
  )");

  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}