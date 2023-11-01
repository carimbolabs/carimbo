#include "scriptengine.hpp"

void scriptengine::run() {
  _lua.open_libraries(
      sol::lib::base,
      sol::lib::package,
      sol::lib::string,
      sol::lib::math,
      sol::lib::table,
      sol::lib::debug);

  _lua.new_enum("keyevent",
                "a", keyevent::a,
                "d", keyevent::d,
                "s", keyevent::s,
                "w", keyevent::w);

  // const auto m = motor::make();

  // m->get_eventmanager()->add_receiver(sm);

  const auto sm = std::shared_ptr<statemanager>(new statemanager());

  _lua.set_function("is_keydown", &statemanager::is_keydown, sm);

  const auto m = motor::instance();
  // m->get_eventmanager()->add_receiver(sm);

  _lua.new_usertype<motor>("motor",
                           "new", sol::factories(&motor::instance),
                           "add_loopable", &motor::add_loopable,
                           "init", &motor::init,
                           "run", &motor::run);

  // _lua.new_usertype<eventreceiver>("eventreceiver",
  //                                  "on_quit", &eventreceiver::on_quit,
  //                                  "on_keydown", &eventreceiver::on_keydown);

  const auto script = R"(
    local motor = motor.new()
    motor:init("Carimbo", 800, 600, false)

    print(is_keydown(keyevent.a))

    motor:run()
  )";

  // const auto script = io::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));

  _lua.script(script);
}