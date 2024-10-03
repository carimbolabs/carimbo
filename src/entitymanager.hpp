#pragma once

#include "common.hpp"
#include <cstdint>

namespace framework {
class entitymanager {
public:
  entitymanager() = default;
  ~entitymanager() = default;

  void set_resourcemanager(std::shared_ptr<resourcemanager> resourcemanager);

  std::shared_ptr<entity> spawn(const std::string &kind);

  void destroy(const std::shared_ptr<entity> entity);

  std::shared_ptr<entity> find(uint64_t id) const;

  void update(double delta) noexcept;

  void draw() noexcept;

private:
  std::shared_ptr<resourcemanager> _resourcemanager;
  std::list<std::shared_ptr<entity>> _entities;
  std::atomic<uint64_t> _counter{0};
};
}
