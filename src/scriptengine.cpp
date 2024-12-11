#include "scriptengine.hpp"

#include "color.hpp"
#include "common.hpp"
#include "enginefactory.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"
#include "entityprops.hpp"
#include "event.hpp"
#include "io.hpp"
#include "label.hpp"
#include "loopable.hpp"
#include "point.hpp"
#include "postalservice.hpp"
#include "socket.hpp"
#include "soundmanager.hpp"
#include "vector2d.hpp"
#include "widget.hpp"

using namespace audio;
using namespace framework;
using namespace input;
using namespace graphics;
using namespace math;
using namespace storage;
using namespace network;

sol::table require(sol::state &lua, std::string_view module) {
  const auto data = io::read(std::format("scripts/{}.lua", module));
  const auto script = std::string(data.begin(), data.end());
  const auto result = lua.script(script);

  return result.get<sol::table>();
}

class lua_loopable : public loopable {
public:
  explicit lua_loopable(sol::function function)
      : _function(std::move(function)) {}

  virtual ~lua_loopable() = default;

  void loop(float_t delta) noexcept override {
    UNUSED(delta);

    _function();
  }

private:
  sol::function _function;
};

auto _to_lua(const nlohmann::json &value, sol::state_view lua) -> sol::object {
  switch (value.type()) {
  case nlohmann::json::value_t::object: {
    auto t = lua.create_table();
    for (const auto &[k, v] : value.items()) {
      t[k] = _to_lua(v, lua);
    }
    return t;
  }
  case nlohmann::json::value_t::array: {
    auto t = lua.create_table();
    for (size_t i = 0; i < value.size(); ++i) {
      t[i + 1] = _to_lua(value[i], lua);
    }
    return t;
  }
  case nlohmann::json::value_t::string:
    return sol::make_object(lua, value.get<std::string>());
  case nlohmann::json::value_t::boolean:
    return sol::make_object(lua, value.get<bool>());
  case nlohmann::json::value_t::number_integer:
    return sol::make_object(lua, value.get<int64_t>());
  case nlohmann::json::value_t::number_unsigned:
    return sol::make_object(lua, value.get<uint64_t>());
  case nlohmann::json::value_t::number_float:
    return sol::make_object(lua, value.get<double>());
  default:
    return sol::lua_nil;
  }
}

auto _to_json(const sol::object &value) -> nlohmann::json {
  switch (value.get_type()) {
  case sol::type::table: {
    const auto lua_table = value.as<sol::table>();
    if (std::ranges::all_of(lua_table, [](const auto &pair) { return pair.first.get_type() == sol::type::number && pair.first.template as<size_t>() >= 1; })) {
      nlohmann::json j = nlohmann::json::array();
      for (const auto &pair : lua_table) {
        j.push_back(_to_json(pair.second));
      }
      return j;
    }
    nlohmann::json j = nlohmann::json::object();
    for (const auto &pair : lua_table) {
      j[pair.first.as<std::string>()] = _to_json(pair.second);
    }
    return j;
  }
  case sol::type::string:
    return value.as<std::string>();
  case sol::type::boolean:
    return value.as<bool>();
  case sol::type::number: {
    const auto num = value.as<double>();
    return std::trunc(num) == num ? static_cast<int64_t>(num) : num;
  }
  default:
    return nullptr;
  }
}

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua["require"] = [&lua](std::string_view module) {
    return require(lua, module);
  };

  lua["JSON"] = lua.create_table_with(
      "parse",
      [](const std::string &json_str, sol::this_state state) {
        auto j = nlohmann::json::parse(json_str);
        sol::state_view lua(state);

        return _to_lua(j, lua);
      },
      "stringify",
      [](const sol::table &table) {
        nlohmann::json result;
        for (const auto &pair : table) {
          result[pair.first.as<std::string>()] = _to_json(pair.second);
        }
        return result.dump();
      }
  );

  lua.new_usertype<soundmanager>(
      "SoundManager",
      "play", &soundmanager::play,
      "stop", &soundmanager::stop
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

  lua.new_usertype<resourcemanager>(
      "ResourceManager",
      "flush", &resourcemanager::flush,
      "prefetch", [](std::shared_ptr<resourcemanager> manager, sol::table table) {
        std::vector<std::string> filenames(table.size());
        std::ranges::transform(
            table,
            filenames.begin(),
            [](const auto &item) {
              return item.second.template as<std::string>();
            }
        );
        manager->prefetch(std::move(filenames));
      }
  );

  lua.new_usertype<statemanager>(
      "StateManager",
      "is_keydown", &statemanager::is_keydown
  );

  lua.new_usertype<scenemanager>(
      "SceneManager",
      "set", &scenemanager::set
  );

  lua.new_enum(
      "WidgetType",
      "label", widgettype::label
  );

  lua.new_usertype<overlay>(
      "Overlay",
      "create", &overlay::create,
      "destroy", &overlay::destroy
  );

  lua.new_usertype<engine>(
      "Engine",
      "add_loopable", &engine::add_loopable,
      "entitymanager", &engine::entitymanager,
      "fontfactory", &engine::fontfactory,
      "overlay", &engine::overlay,
      "resourcemanager", &engine::resourcemanager,
      "soundmanager", &engine::soundmanager,
      "statemanager", &engine::statemanager,
      "scenemanager", &engine::scenemanager,
      "run", &engine::run
  );

  lua.new_usertype<font>(
      "Font",
      sol::constructors<font()>()
  );

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "with_title", &enginefactory::with_title,
      "with_width", &enginefactory::with_width,
      "with_height", &enginefactory::with_height,
      "with_gravity", &enginefactory::with_gravity,
      "with_fullscreen", &enginefactory::with_fullscreen,
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

  lua.new_usertype<socket>(
      "Socket",
      sol::constructors<socket()>(),
      "emit", [](socket &sio, const std::string &event, sol::table data, sol::this_state state) {
          sol::state_view lua(state);
          const auto j = _to_json(data);
          sio.emit(event, j.dump()); },
      "on", [](socket &sio, const std::string &event, sol::function callback, sol::this_state state) {
          sol::state_view lua(state);
          sio.on(event, [callback, lua](const std::string &data) {
              const auto j = nlohmann::json::parse(data);
              callback(_to_lua(j, lua));
          }); },
      "rpc", [](socket &sio, const std::string &method, sol::table arguments, sol::function callback, sol::this_state state) {
          sol::state_view lua(state);
          const auto args_json = _to_json(arguments);
          sio.rpc(method, args_json.dump(), [callback, lua](const std::string &response) {
            const auto j = nlohmann::json::parse(response);
            callback(_to_lua(j, lua));
          }); }
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
      "w", keyevent::w,
      "a", keyevent::a,
      "s", keyevent::s,
      "d", keyevent::d,
      "space", keyevent::space
  );

  lua.new_usertype<mail>(
      "Mail",
      sol::constructors<mail(std::shared_ptr<entity>, const std::string_view, const std::string_view)>()
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

  lua.new_usertype<label>(
      "Label",
      sol::factories([] {
        return std::make_shared<label>();
      }),
      sol::base_classes, sol::bases<widget>(),
      "set_font", &label::set_font,
      "set_placement", &label::set_placement,
      "set", sol::overload(&label::set, &label::set_with_placement)
  );

  lua.new_usertype<widget>(
      "Widget",
      sol::no_constructor
  );

  lua.new_usertype<fontfactory>(
      "FontFactory",
      "get", &fontfactory::get
  );

  const auto script = storage::io::read("scripts/main.lua");

  lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));

  lua["setup"]();
  const auto loop = lua["loop"].get<sol::function>();
  const auto engine = lua["engine"].get<framework::engine *>();
  engine->add_loopable(std::make_shared<lua_loopable>(std::move(loop)));
  lua["run"]();
}
