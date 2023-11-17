#include "scriptengine.hpp"

#include "delay.hpp"
#include "engine.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"
#include "io.hpp"
#include "noncopyable.hpp"
#include "pixmap.hpp"
#include "point.hpp"
#include "soundmanager.hpp"
#include "statemanager.hpp"
#include "ticks.hpp"

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
      "d", keyevent::d,
      "space", keyevent::space);

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
      "ticks", &ticks,
      "is_keydown", &engine::is_keydown,
      "prefetch", [](engine &engine, sol::table table) {
        std::vector<std::string> filenames{table.size()};
        for (auto &item : table) {
          filenames.push_back(item.second.as<std::string>());
        }
        engine.prefetch(filenames);
      });

  lua.new_usertype<entity>(
      "Entity",
      "x", sol::property(&entity::get_x, &entity::set_x),
      "y", sol::property(&entity::get_y, &entity::set_y),
      "width", sol::property(&entity::get_width),
      "height", sol::property(&entity::get_height),
      "move", &entity::move,
      "angle", sol::property(&entity::get_angle, &entity::set_angle),
      "alpha", sol::property(&entity::get_alpha, &entity::set_alpha),
      "pixmap", sol::property(&entity::set_pixmap),
      "play", &entity::play_sound,
      "on_update", &entity::set_onupdate);

  lua.set_function("sleep", &sleep);

  const auto script = io::read("scripts/main.lua");
  lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}