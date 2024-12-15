#include "socket.hpp"

using namespace network;

using json = nlohmann::json;

socket::socket() noexcept {
  _queue.reserve(8);

  const auto url = "http://" + std::string(emscripten_run_script_string("window.location.hostname")) + ":3000/socket";
  EmscriptenWebSocketCreateAttributes attrs = {
      url.c_str(),
      nullptr,
      true
  };

  _socket = emscripten_websocket_new(&attrs);

  emscripten_websocket_set_onopen_callback(
      _socket,
      this,
      [](int, const EmscriptenWebSocketOpenEvent *event, void *data) noexcept {
        UNUSED(event);
        auto *self = static_cast<socket *>(data);

        self->_connected = true;

        for (const auto &message : self->_queue) {
          self->send(message);
        }
        self->_queue.clear();

        self->invoke("connect");

        return 0;
      }
  );

  emscripten_websocket_set_onmessage_callback(
      _socket,
      this,
      [](int, const EmscriptenWebSocketMessageEvent *event, void *data) noexcept {
        if (!event->isText) [[unlikely]] {
          return 0;
        }

        auto *self = static_cast<socket *>(data);
        const auto buffer = std::string(reinterpret_cast<const char *>(event->data), event->numBytes - 1);
        const auto j = json::parse(buffer, nullptr, false);
        if (j.is_discarded()) [[unlikely]] {
          return 0;
        }

        if (const auto &command = j.value("command", std::string{}); command == "ping") {
          self->send(R"({"command": "pong"})");
          return 0;
        }

        if (const auto &event = j.value("event", json::object()); !event.empty()) {
          self->invoke(
              event.at("topic").get_ref<const std::string &>(),
              event.at("data").dump()
          );

          return 0;
        }

        if (const auto &rpc = j.value("rpc", json::object()); !rpc.empty() && rpc.contains("response")) {
          const auto response = rpc.at("response");
          self->invoke(
              std::to_string(response.at("id").get<uint64_t>()),
              response.at("result").dump()
          );

          return 0;
        }

        return 0;
      }
  );

  emscripten_websocket_set_onerror_callback(
      _socket,
      this,
      [](int, const EmscriptenWebSocketErrorEvent *event, void *data) noexcept {
        UNUSED(event);
        const auto self = static_cast<socket *>(data);
        self->invoke("error", "WebSocket error occurred");
        return 0;
      }
  );

  emscripten_websocket_set_onclose_callback(
      _socket,
      this,
      [](int, const EmscriptenWebSocketCloseEvent *event, void *data) noexcept {
        UNUSED(event);
        const auto *self = static_cast<socket *>(data);
        self->invoke("disconnect");
        return 0;
      }
  );
}

socket::~socket() noexcept {
  constexpr int code = 1000;
  constexpr const char *reason = "Client disconnecting";

  if (_socket) {
    emscripten_websocket_close(_socket, code, reason);
    emscripten_websocket_delete(_socket);
    _socket = 0;
    invoke("disconnect");
  }
}

void socket::emit(const std::string &topic, const std::string &data) noexcept {
  std::ostringstream oss;
  oss << R"({"event": {"topic": ")" << topic << R"(", "data": )" << data << R"(}})";
  send(oss.str());
}

void socket::on(const std::string &topic, std::function<void(const std::string &)> callback) noexcept {
  std::ostringstream oss;
  oss << R"({"subscribe": ")" << topic << R"("})";
  send(oss.str());
  _callbacks[topic].push_back(std::move(callback));
}

void socket::rpc(const std::string &method, const std::string &arguments, std::function<void(const std::string &)> callback) noexcept {
  std::ostringstream oss;
  oss << R"({"rpc": {"request": {"id": )" << ++counter
      << R"(, "method": ")" << method
      << R"(", "arguments": )" << arguments << R"(}}})";
  send(oss.str());

  _callbacks[std::to_string(counter)].push_back(std::move(callback));
}

void socket::send(const std::string &message) noexcept {
  if (!_connected) {
    _queue.emplace_back(message);
    return;
  }

  emscripten_websocket_send_utf8_text(_socket, message.c_str());
}

void socket::invoke(const std::string &event, const std::string &data) const noexcept {
  if (auto it = _callbacks.find(event); it != _callbacks.end()) {
    for (const auto &callback : it->second) {
      callback(data);
    }
  }
}
