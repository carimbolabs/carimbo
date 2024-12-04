#pragma once

#include "common.hpp"

namespace network {
class socketio {
public:
  using EventCallback = std::function<void(const std::string &)>;

  explicit socketio(const std::string &url);
  ~socketio();

  void connect();
  void disconnect();
  void emit(const std::string &topic, const std::string &data);
  void on(const std::string &topic, EventCallback callback);

private:
  void send(const std::string &message) const;
  void invoke(const std::string &event, const std::string &data = "") const;

  std::string _url;
  EMSCRIPTEN_WEBSOCKET_T _socket;
  std::unordered_map<std::string, std::vector<EventCallback>> _callbacks;
};
}
