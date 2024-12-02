#pragma once

#include "common.hpp"

namespace network {
class querybuilder {
public:
  querybuilder &add(const std::string &key, const std::string &value) noexcept;

  [[nodiscard]] std::string build() const noexcept;

private:
  std::unordered_map<std::string, std::string> _parameters;
};
}
