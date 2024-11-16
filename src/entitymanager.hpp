#pragma once

#include "common.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"
#include "world.hpp"

namespace framework {
class entitymanager : public input::eventreceiver {
public:
  explicit entitymanager(std::shared_ptr<world> world);
  ~entitymanager();

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager) noexcept;

  std::shared_ptr<entity> spawn(const std::string &kind);

  void destroy(const std::weak_ptr<entity> entity) noexcept;

  std::shared_ptr<entity> find(uint64_t id) const noexcept;

  void update(float_t delta);

  void draw() noexcept;

protected:
  virtual void on_mail(const input::mailevent &event) noexcept override;

private:
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::shared_ptr<world> _world;
  std::list<std::shared_ptr<entity>> _entities;
  std::atomic<uint64_t> _counter{0};
};
}
