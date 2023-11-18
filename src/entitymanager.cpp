#include "entitymanager.hpp"

#include "entity.hpp"
#include "resourcemanager.hpp"

using namespace framework;

std::random_device rd;
std::mt19937 generator(rd());

std::uniform_int_distribution<> distribution(0, 61);

const auto random_char = []() -> uint8_t {
  const auto value = distribution(generator);
  if (value < 10) return '0' + value;
  if (value < 36) return 'a' + value - 10;
  return 'A' + value - 36;
};

void entitymanager::set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) {
  _resourcemanager = resourcemanager;
}

std::shared_ptr<entity> entitymanager::spawn() {
  std::vector<uint8_t> buffer(16);
  for (auto &b : buffer) {
    b = random_char();
  }

  const auto e = entity::create({buffer.begin(), buffer.end()});
  std::cout << "Spawned entity: " << e->id() << std::endl;
  _entities.emplace_back(e);
  return e;
}

void entitymanager::destroy(const std::shared_ptr<entity> entity) {
  _entities.remove(entity);
}

std::shared_ptr<entity> entitymanager::find(const std::string &id) {
  for (auto entity : _entities) {
    if (entity->get_id() == id) {
      return entity;
    }
  }

  return nullptr;
}

void entitymanager::update() {
  for (auto entity : _entities) {
    entity->update();
  }
}

void entitymanager::draw() {
  for (auto entity : _entities) {
    entity->draw();
  }
}
