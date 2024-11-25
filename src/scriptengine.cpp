#include "scriptengine.hpp"

#include "color.hpp"
#include "common.hpp"
#include "engine.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"
#include "event.hpp"
#include "io.hpp"
#include "label.hpp"
#include "loopable.hpp"
#include "point.hpp"
#include "postalservice.hpp"
#include "soundmanager.hpp"
#include "ticks.hpp"
#include "vector2d.hpp"
#include "widget.hpp"
#include <sol/overload.hpp>

using namespace framework;
using namespace graphics;
using namespace math;

class loopable_proxy : public loopable {
public:
  loopable_proxy(sol::function lua_func) : function(lua_func) {}

  void loop(float_t delta) noexcept override {
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
      "move", &entity::move,
      "velocity", sol::property(&entity::get_velocity),
      "on_update", &entity::set_onupdate,
      "on_animationfinished", &entity::set_onanimationfinished,
      "on_mail", &entity::set_onmail,
      "set_flip", &entity::set_flip,
      "set_action", &entity::set_action,
      "unset_action", &entity::unset_action,
      "set_placement", &entity::set_placement
  );

  lua.new_usertype<entitymanager>(
      "EntityManager",
      "spawn", &entitymanager::spawn,
      "destroy", &entitymanager::destroy
  );

  lua.new_usertype<engine>(
      "Engine",
      "add_loopable", &engine::add_loopable,
      "entitymanager", &engine::entitymanager,
      "flush", &engine::flush,
      "fontfactory", &engine::fontfactory,
      "width", sol::property(&engine::width),
      "height", sol::property(&engine::height),
      "is_keydown", &engine::is_keydown,
      "overlay", &engine::overlay,
      "run", &engine::run,
      "set_scene", &engine::set_scene,
      "soundmanager", &engine::soundmanager,
      "ticks", &ticks,
      "prefetch", [](engine &engine, sol::table table) {
        std::vector<std::string> filenames;
        filenames.reserve(table.size());
        for (const auto &item : table | std::views::all) {
          filenames.emplace_back(item.second.as<std::string>());
        }
        engine.prefetch(filenames);
      }
  );

  lua.new_usertype<overlay>(
      "Overlay",
      "add", &overlay::add

      // "create", &overlay::create,
      // "destroy", &overlay::destroy
  );

  lua.new_enum(
      "WidgetType",
      "label", widgettype::label
  );

  lua.new_usertype<font>(
      "Font",
      sol::constructors<font()>()
  );

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_gravity", &enginefactory::set_gravity,
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
      "none", flip::none,
      "horizontal", flip::horizontal,
      "vertical", flip::vertical,
      "both", flip::both
  );

  lua.new_usertype<color>(
      "Color",
      "color", sol::constructors<color(const std::string &)>(),

      "r", sol::property(&color::r, &color::set_r),
      "g", sol::property(&color::g, &color::set_g),
      "b", sol::property(&color::b, &color::set_b),
      "a", sol::property(&color::a, &color::set_a),

      sol::meta_function::equal_to, &color::operator==, // sol::meta_function::not_equal_to, &color::operator!=,

      sol::meta_function::to_string, [](const color &c) {
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

  lua.new_usertype<math::vector2d>(
      "Vector2D", sol::constructors<math::vector2d(), math::vector2d(double_t, double_t)>(),

      "x", sol::property(&math::vector2d::x, &math::vector2d::set_x),
      "y", sol::property(&math::vector2d::y, &math::vector2d::set_y),
      "magnitude", &math::vector2d::magnitude,
      "unit", &math::vector2d::unit,
      "dot", &math::vector2d::dot,

      sol::meta_function::addition, &math::vector2d::operator+,
      sol::meta_function::subtraction, &math::vector2d::operator-,

      "add_assign", &math::vector2d::operator+=,
      "sub_assign", &math::vector2d::operator-=,
      "mul_assign", &math::vector2d::operator*=,
      "div_assign", &math::vector2d::operator/=,

      sol::meta_function::equal_to, &math::vector2d::operator==,

      "zero", &math::vector2d::zero,
      "moving", &math::vector2d::moving,
      "right", &math::vector2d::right,
      "left", &math::vector2d::left
  );

  lua.new_usertype<label>(
      "Label",
      // sol::constructors<label()>(),
      sol::factories([] {
        return std::make_shared<label>();
      }),
      sol::base_classes, sol::bases<widget>(),
      "set_font", &label::set_font,
      "set_placement", &label::set_placement,
      "set", &label::set,
      "set_with_placement", &label::set_with_placement
  );

  lua.new_usertype<widget>(
      "Widget",
      sol::no_constructor
  );

  lua.new_usertype<fontfactory>(
      "FontFactory",
      "get", &fontfactory::get
  );

  lua.set_function("to_widget", [](std::shared_ptr<label> label) -> std::shared_ptr<widget> {
    return std::static_pointer_cast<widget>(label);
  });

  const auto script = storage::io::read("scripts/main.lua");

  lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}
