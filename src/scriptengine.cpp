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

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create);

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "spawn", &engine::spawn,
      "destroy", &engine::destroy,
      "is_keydown", &engine::is_keydown,
      "prefetch", [](engine &engine, sol::table table) {
        std::list<std::string> filenames(table.size());
        for (auto &item : table) {
          filenames.push_back(item.second.as<std::string>());
        }
        engine.prefetch(filenames);
      });

  lua.new_usertype<entity>(
      "Entity",
      "x", sol::property(&entity::x, &entity::set_x),
      "y", sol::property(&entity::y, &entity::set_y),
      "width", sol::property(&entity::width),
      "height", sol::property(&entity::height),
      "angle", sol::property(&entity::angle, &entity::set_angle),
      "alpha", sol::property(&entity::alpha, &entity::set_alpha),
      "on_update", &entity::set_onupdate,
      "set_pixmap", &entity::set_pixmap,
      sol::meta_function::garbage_collect,
      sol::destructor(&entity::destroy));

  const auto script = io::read("scripts/main.lua");
  lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}