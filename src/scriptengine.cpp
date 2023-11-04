#include "scriptengine.hpp"

#include "engine.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"
#include "io.hpp"
#include "noncopyable.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "statemanager.hpp"

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua.new_enum(
      "Flip",
      "none", flip::none,
      "horizontal", flip::horizontal,
      "vertical", flip::vertical,
      "both", flip::both);

  lua.new_enum(
      "KeyEvent",
      "w", keyevent::w,
      "a", keyevent::a,
      "s", keyevent::s,
      "d", keyevent::d);

  lua.new_usertype<point>(
      "Point",
      sol::constructors<point(int32_t, int32_t)>(),
      "x", sol::property(&point::x, &point::set_x),
      "y", sol::property(&point::y, &point::set_y));

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "prefetch", &engine::prefetch,
      "spawn", &engine::spawn,
      "destroy", &engine::destroy,
      // "birth", &engine::birth,
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
      "angle", sol::property(&entity::angle, &entity::set_angle),
      "on_update", &entity::set_onupdate,
      "set_pixmap", &entity::set_pixmap,
      // "set_body", &entity::set_body,
      sol::meta_function::garbage_collect,
      sol::destructor(&entity::destroy));

  lua.script(R"(
      local engine = EngineFactory.new()
        :set_title("Carimbo")
        :set_width(800)
        :set_height(600)
        :create()

      -- engine:prefetch({"ball.avif"})

      local e = engine:spawn()

      e:set_pixmap("ball.avif")

      local floor = 800
      local angle = 0
      local energy = 100

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

        angle = angle + 1
        if angle > 360 then
          angle = 0
        end

        self.angle = angle
        self.y = self.y + 1
      end)

      engine:run()
  )");

  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}