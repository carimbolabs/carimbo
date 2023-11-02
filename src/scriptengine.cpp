#include "scriptengine.hpp"

// class Person {
// public:
//   virtual ~Person() = default;

//   virtual void say() = 0;
// };

// class PersonWrapper : public Person {
// public:
//   PersonWrapper() = default;
//   virtual ~PersonWrapper() = default;

//   virtual void say() override {}
// };

// class World {
// public:
//   virtual ~World() = default;

//   void add_person(std::shared_ptr<PersonWrapper> person) {
//     _people.emplace_back(person);
//   }

//   void say() {
//     std::for_each(_people.begin(), _people.end(), [](const auto &person) {
//       person->say();
//     });
//   }

// private:
//   std::list<std::shared_ptr<PersonWrapper>> _people;
//   // std::list<Person> _people;
// };

// class Humano {
// public:
//   Humano(std::string name) : name(name) {}
//   virtual std::string getName() { return name; }

// private:
//   std::string name;
// };

// class Person : public Humano {
// public:
//   Person(std::string name) : Humano(name) {}
//   std::string getName() override { return "Person: " + Humano::getName(); }
// };

// class PersonManager {
// public:
//   void add(std::shared_ptr<Humano> humano) {
//     humanos.push_back(humano);
//   }

//   void printAllNames() {
//     for (auto &humano : humanos) {
//       std::cout << humano->getName() << std::endl;
//     }
//   }

// private:
//   std::vector<std::shared_ptr<Humano>> humanos;
// };

class Person {
public:
  Person(std::string name) : name(name) {}

  void set_on_say(std::function<void(std::string)> on_say) {
    on_say_ = on_say;
  }

  void say() {
    if (on_say_) {
      on_say_(name);
    }
  }

private:
  std::string name;
  std::function<void(std::string)> on_say_;
};

class World {
public:
  void add_person(std::shared_ptr<Person> person) {
    _people.emplace_back(person);
  }

  void say() {
    std::for_each(_people.begin(), _people.end(), [](const auto &person) {
      person->say();
    });
  }

private:
  std::list<std::shared_ptr<Person>> _people;
};

void scriptengine::run() {
  sol::state lua;

  lua.open_libraries();

  lua.new_usertype<Person>("Person",
                           "new", sol::factories([](std::string name) {
                             return std::make_shared<Person>(name);
                           }),
                           "set_on_say", &Person::set_on_say);

  lua.new_usertype<World>("World",
                          "new", sol::factories([]() {
                            return std::make_shared<World>();
                          }),
                          "add_person", &World::add_person,
                          "say", &World::say);

  // lua.new_usertype<Humano>("Humano",
  //                          "new", sol::factories([](std::string name) {
  //                            return std::make_shared<Humano>(name);
  //                          }),
  //                          "getName", &Humano::getName);

  // lua.new_usertype<Person>("Person",
  //                          "new", sol::factories([](std::string name) {
  //                            return std::make_shared<Person>(name);
  //                          }));

  // lua.new_usertype<PersonManager>("PersonManager",
  //                                 "add", &PersonManager::add,
  //                                 "printAllNames", &PersonManager::printAllNames);

  // lua.new_usertype<Person>(
  //     "Person",
  //     "say", &Person::say);

  // lua.new_usertype<PersonWrapper>(
  //     "PersonWrapper",
  //     sol::constructors<std::shared_ptr<PersonWrapper>()>(),
  //     "say", &PersonWrapper::say);

  // lua.new_usertype<World>(
  //     "World",
  //     sol::constructors<World()>(),
  //     "add_person", &World::add_person,
  //     "say", &World::say);

  /* sol::usertype<engine> engine_type = */ lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run);

  lua.new_usertype<enginefactory>(
      "EngineFactory",
      sol::constructors<enginefactory()>(),
      "set_title", &enginefactory::set_title,
      "set_width", &enginefactory::set_width,
      "set_height", &enginefactory::set_height,
      "set_fullscreen", &enginefactory::set_fullscreen,
      "create", &enginefactory::create);

  lua.script(R"(
    local world = World.new()

    local person = Person.new("Person 1")
    person:set_on_say(function(name)
      print("Person 1: " .. name)
    end)

    local person2 = Person.new("Person 2")
    person2:set_on_say(function(name)
      print("Person 2: " .. name)
    end)

    world:add_person(person)
    world:add_person(person2)
    world:say()
  )");

  /*
      local engine = EngineFactory.new()
        :set_title("Carimbo")
        :set_width(800)
        :set_height(600)
        :set_fullscreen(false)
        :create()

    engine:run()

  */
  // const script = file::read("scripts/main.lua");
  // _lua.script(std::string_view(reinterpret_cast<const char *>(script.data()), script.size()));
}