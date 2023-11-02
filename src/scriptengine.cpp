#include "scriptengine.hpp"

class Person : public std::enable_shared_from_this<Person> {
public:
  Person(std::string name) : name(name) {}

  void set_sayfn(const std::function<void(std::shared_ptr<Person>, std::string)> &on_say) {
    on_say_ = on_say;
  }

  void doit() {
    std::cout << "Do!" << std::endl;
  }

  std::string get_name() const {
    return name;
  }

  void say() {
    if (on_say_) {
      on_say_(shared_from_this(), name);
    }
  }

  std::string name;
  std::function<void(std::shared_ptr<Person>, std::string)> on_say_;
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
                           "set_sayfn", &Person::set_sayfn,
                           "doit", &Person::doit,
                           "get_name", &Person::get_name,
                           "on_say", &Person::on_say_);

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

  lua.new_usertype<engine>(
      "Engine",
      "run", &engine::run,
      "spawn", &engine::spawn);

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
      "on_update", &entity::set_fn);
  //"set_id", &entity::set_id);

  lua.script(R"(
    local world = World.new()

    local person = Person.new("P1")
    person:set_sayfn(function(self, name)
      person:doit()
      print("Person 1: " .. name)
    end)


    local person2 = Person.new("P2")

    person2:set_sayfn(function(self, name)
      print(self:get_name() .. " -> ".. "Person 2: " .. name)
    end)

    world:add_person(person)
    world:add_person(person2)
    world:say()

    local engine = EngineFactory.new()
      :set_title("Carimbo")
      :set_width(800)
      :set_height(600)
      :set_fullscreen(false)
      :create()

    local entity = engine:spawn()
    entity:on_update(function(self)
      print("update")
    end)

    print(entity)

    engine:run()
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