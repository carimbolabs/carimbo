#pragma once

#include "common.hpp"

namespace framework {
struct mail {
  uint64_t to;
  std::shared_ptr<std::string> msg;

  mail(uint64_t to, const std::string_view message) : to(to), msg(std::make_shared<std::string>(message)) {}
};

class postalservice {
public:
  postalservice();

  void post(const std::string_view message, uint64_t to);

private:
  uint32_t _eventtype;
};
}
