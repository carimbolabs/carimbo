#include "scriptengine.hpp"

namespace py = pybind11;

// class Person {
// public:
//   virtual void say() = 0;
//   virtual ~Person() = default;
// };

// class PyPerson : public Person {
// public:
//   using Person::Person;

//   virtual void say() override {
//     PYBIND11_OVERRIDE_PURE(
//         void,
//         Person,
//         say);
//   }
// };

// class World {
// public:
//   void add(std::shared_ptr<Person> person) {
//     people.push_back(person);
//   }

//   void all() {
//     for (const auto &person : people) {
//       person->say();
//     }
//   }

// private:
//   std::list<std::shared_ptr<Person>> people;
// };

// PYBIND11_EMBEDDED_MODULE(carimbo, m) {
//   py::class_<Person, PyPerson, std::shared_ptr<Person>>(m, "Person")
//       .def(py::init<>())
//       .def("say", &Person::say);

//   py::class_<World>(m, "World")
//       .def(py::init<>())
//       .def("add", &World::add)
//       .def("all", &World::all);
// }

PYBIND11_EMBEDDED_MODULE(carimbo, module) {
  py::class_<engine, std::shared_ptr<engine>>(module, "Engine")
      .def("run", &engine::run);

  py::class_<enginefactory>(module, "EngineFactory")
      .def(py::init<>())
      .def("set_title", &enginefactory::set_title, py::return_value_policy::reference)
      .def("set_width", &enginefactory::set_width, py::return_value_policy::reference)
      .def("set_height", &enginefactory::set_height, py::return_value_policy::reference)
      .def("set_fullscreen", &enginefactory::set_fullscreen, py::return_value_policy::reference)
      .def("create", &enginefactory::create);
}

void scriptengine::run() {
  // py::scoped_interpreter guard{};

  // py::exec(R"(
  //   from carimbo import *

  //   engine = (
  //       EngineFactory()
  //       .set_title("Carimbo")
  //       .set_width(800)
  //       .set_height(600)
  //       .set_fullscreen(False)
  //       .create()
  //   )

  //   engine.run()
  // )");

  sol::state lua;

  // lua.open_libraries(
  //     sol::lib::base,
  //     sol::lib::package,
  //     sol::lib::string,
  //     sol::lib::math,
  //     sol::lib::table,
  //     sol::metatable);

  lua.open_libraries(sol::lib::base);

  sol::usertype<engine> engine_type = lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run);

  sol::usertype<enginefactory> enginefactory_type = lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create);

  lua.script(R"(
    local engine = EngineFactory.new()
        :set_title("Carimbo")
        :set_width(800)
        :set_height(600)
        :set_fullscreen(false)
        :create()

    engine:run()
  )");

  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}