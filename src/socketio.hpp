#pragma once

#include "common.hpp"

namespace network {
class socketio {
public:
  socketio();
  ~socketio();

  void emit(const std::string &topic, const std::string &data);
  void on(const std::string &topic, std::function<void(const std::string &)> callback);

private:
  void send(const std::string &message) const;
  void invoke(const std::string &event, const std::string &data = "") const;

  EMSCRIPTEN_WEBSOCKET_T _socket{0};
  std::unordered_map<std::string, std::vector<std::function<void(const std::string &)>>> _callbacks;
};
}
