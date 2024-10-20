#include "scriptengine.hpp"

#include "color.hpp"
#include "common.hpp"
#include "engine.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "io.hpp"
#include "loopable.hpp"
#include "point.hpp"
#include "postalservice.hpp"
#include "soundmanager.hpp"
#include "ticks.hpp"
#include "vector2d.hpp"

using namespace framework;

class loopable_proxy : public loopable {
public:
  loopable_proxy(sol::function lua_func) : function(lua_func) {}

  void loop(uint32_t delta) override {
    if (function.valid()) {
      function(delta);
    }
  }

private:
  sol::function function;
};

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua.new_usertype<audio::soundmanager>(
      "SoundManager",
      "play", &audio::soundmanager::play,
      "stop", &audio::soundmanager::stop
  );

  lua.new_enum(
      "Anchor",
      "top", anchor::top,
      "bottom", anchor::bottom,
      "left", anchor::left,
      "right", anchor::right,
      "none", anchor::none
  );

  lua.new_usertype<entity>(
      "Entity",
      "id", sol::property(&entity::id),
      "x", sol::property(&entity::x),
      "y", sol::property(&entity::y),
      "visible", sol::property(&entity::visible),
      "size", sol::property(&entity::size),
      "on_update", &entity::set_onupdate,
      "on_animationfinished", &entity::set_onanimationfinished,
      "on_mail", &entity::set_onmail,
      "set_flip", &entity::set_flip,
      "set_action", &entity::set_action,
      "unset_action", &entity::unset_action,
      "set_velocity", &entity::set_velocity,
      "set_placement", &entity::set_placement
  );

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "spawn", &engine::spawn,
      "destroy", &engine::destroy,
      "ticks", &ticks,
      "is_keydown", &engine::is_keydown,
      "width", sol::property(&engine::width),
      "height", sol::property(&engine::height),
      "soundmanager", &engine::soundmanager,
      "add_loopable", &engine::add_loopable,
      "set_scene", &engine::set_scene,
      //"load_font", &engine::load_font,
      "prefetch", [](engine &engine, sol::table table) {
        std::vector<std::string> filenames;
        filenames.reserve(table.size());
        for (const auto &item : table) {
          filenames.emplace_back(item.second.as<std::string>());
        }
        engine.prefetch(filenames);
      },
      "flush", &engine::flush
  );

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create
  );

  lua.new_usertype<geometry::point>(
      "Point",
      sol::constructors<geometry::point(), geometry::point(int32_t, int32_t)>(),
      "set", &geometry::point::set,
      "x", sol::property(&geometry::point::x, &geometry::point::set_x),
      "y", sol::property(&geometry::point::y, &geometry::point::set_y),
      sol::meta_function::to_string, [](const geometry::point &p) {
        return "point(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")";
      }
  );

  lua.new_usertype<geometry::size>(
      "Size", sol::constructors<geometry::size(), geometry::size(int32_t, int32_t), geometry::size(const geometry::size &)>(),
      "width", sol::property(&geometry::size::width, &geometry::size::set_width),
      "height", sol::property(&geometry::size::height, &geometry::size::set_height)
  );

  lua.new_enum(
      "Flip",
      "none", graphics::flip::none,
      "horizontal", graphics::flip::horizontal,
      "vertical", graphics::flip::vertical,
      "both", graphics::flip::both
  );

  lua.new_usertype<graphics::color>(
      "color", sol::constructors<graphics::color(const std::string &)>(),

      "r", sol::property(&graphics::color::r, &graphics::color::set_r),
      "g", sol::property(&graphics::color::g, &graphics::color::set_g),
      "b", sol::property(&graphics::color::b, &graphics::color::set_b),
      "a", sol::property(&graphics::color::a, &graphics::color::set_a),

      sol::meta_function::equal_to, &graphics::color::operator==, // sol::meta_function::not_equal_to, &graphics::color::operator!=,

      sol::meta_function::to_string, [](const graphics::color &c) {
        return "color(" + std::to_string(c.r()) + ", " +
               std::to_string(c.g()) + ", " +
               std::to_string(c.b()) + ", " +
               std::to_string(c.a()) + ")";
      }
  );

  lua.new_enum(
      "KeyEvent",
      "w", input::keyevent::w,
      "a", input::keyevent::a,
      "s", input::keyevent::s,
      "d", input::keyevent::d,
      "space", input::keyevent::space
  );

  lua.new_usertype<loopable_proxy>(
      "loopable_proxy", sol::constructors<loopable_proxy(sol::function)>(),
      "loop", &loopable_proxy::loop
  );

  lua.new_usertype<mail>(
      "Mail",
      sol::constructors<mail(uint64_t, const std::string_view, const std::string_view)>()
  );

  lua.new_usertype<postalservice>(
      "PostalService", sol::constructors<postalservice()>(),
      "post", &postalservice::post
  );

  lua.new_usertype<timermanager>(
      "TimeManager", sol::constructors<timermanager()>(),
      "set", &timermanager::set,
      "singleshot", &timermanager::singleshot,
      "clear", &timermanager::clear
  );

  lua.new_usertype<vector2d>(
      "Vector2D", sol::constructors<vector2d(), vector2d(double_t, double_t)>(),

      "x", sol::property(&vector2d::x, &vector2d::set_x),
      "y", sol::property(&vector2d::y, &vector2d::set_y),
      "magnitude", &vector2d::magnitude,
      "unit", &vector2d::unit,
      "dot", &vector2d::dot,

      sol::meta_function::addition, &vector2d::operator+,
      sol::meta_function::subtraction, &vector2d::operator-,

      "add_assign", &vector2d::operator+=,
      "sub_assign", &vector2d::operator-=,
      "mul_assign", &vector2d::operator*=,
      "div_assign", &vector2d::operator/=,

      sol::meta_function::equal_to, &vector2d::operator==,

      "zero", &vector2d::zero,
      "moving", &vector2d::moving,
      "right", &vector2d::right,
      "left", &vector2d::left
  );

  const auto script = storage::io::read("scripts/main.lua");

  lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}
