#pragma once

#include "common.hpp"

namespace network {
struct networkrequest {
  std::string url;
  std::string method;
  std::string body;
  std::unordered_map<std::string, std::string> headers;
  std::function<void(const std::string &, long)> callback;
};

class networkmanager {
public:
  networkmanager();
  ~networkmanager();

  void send(const networkrequest &request);
};
}
