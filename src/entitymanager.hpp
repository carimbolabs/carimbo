#pragma once

#include "common.hpp"
#include "eventreceiver.hpp"

namespace framework {
class entitymanager : public input::eventreceiver {
public:
  entitymanager() = default;
  ~entitymanager() = default;

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  std::shared_ptr<entity> spawn(const std::string &kind);

  void destroy(const std::weak_ptr<entity> entity);

  std::shared_ptr<entity> find(uint64_t id) const;

  void update(double_t delta);

  void draw();

protected:
  virtual void on_mail(const input::mailevent &event);

private:
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::list<std::shared_ptr<entity>> _entities;
  std::atomic<uint64_t> _counter{0};
};
}
