#include "application.hpp"

#include "querybuilder.hpp"

#if 0
class socketio {
public:
  explicit socketio(const std::string &url)
      : _url(url) {
    connect();
  }

  ~socketio() {
    disconnect();
  }

  void emit(const std::string &event, const std::string &message) {
    const auto packet = fmt::format("2[\"{}\",{{\"message\":\"{}\"}}]", event, message);
    emscripten_websocket_send_utf8_text(_socket, packet.c_str());
  }

  void subscribe(const std::string &event, const std::function<void(const std::string &)> &callback) {
    _subscriptions[event] = callback;

    const auto packet = fmt::format("2[\"subscribe\",{{\"event\":\"{}\"}}]", event);
    emscripten_websocket_send_utf8_text(_socket, packet.c_str());
  }

  void set_on_open(const std::function<void()> &callback) {
    _on_open = callback;
  }

  void set_on_message(const std::function<void(const std::string &)> &callback) {
    _on_message = callback;
  }

  void set_on_close(const std::function<void(const std::string &)> &callback) {
    _on_close = callback;
  }

  void set_on_error(const std::function<void()> &callback) {
    _on_error = callback;
  }

private:
  void connect() {
    EmscriptenWebSocketCreateAttributes attributes = {
        _url.c_str(),
        nullptr,
        true
    };

    _socket = emscripten_websocket_new(&attributes);
    if (_socket <= 0) [[unlikely]] {
      throw std::runtime_error("Failed to create WebSocket.");
    }

    emscripten_websocket_set_onopen_callback(_socket, this, [](int, const EmscriptenWebSocketOpenEvent *event, void *data) -> EM_BOOL {
      UNUSED(event);

      const auto self = static_cast<socketio *>(data);

      constexpr auto packet = "0";
      emscripten_websocket_send_utf8_text(event->socket, packet);

      if (self->_on_open) [[likely]] {
        self->_on_open();
      }

      return true;
    });

    emscripten_websocket_set_onmessage_callback(_socket, this, [](int, const EmscriptenWebSocketMessageEvent *event, void *data) -> EM_BOOL {
      const auto self = static_cast<socketio *>(data);

      if (event->isText && self->_on_message) [[likely]] {
        const std::string message(event->data, event->data + event->numBytes);
        self->_on_message(message);
      }

      return true;
    });

    emscripten_websocket_set_onclose_callback(_socket, this, [](int, const EmscriptenWebSocketCloseEvent *event, void *data) -> EM_BOOL {
      const auto self = static_cast<socketio *>(data);

      if (self->_on_close) [[likely]] {
        self->_on_close(event->reason);
      }

      self->disconnect();
      // self->connect();

      return true;
    });

    emscripten_websocket_set_onerror_callback(_socket, this, [](int, const EmscriptenWebSocketErrorEvent *, void *data) -> EM_BOOL {
      const auto self = static_cast<socketio *>(data);

      if (self->_on_error) [[likely]] {
        self->_on_error();
      }

      return true;
    });
  }

  void disconnect() {
    if (_socket > 0) [[likely]] {
      constexpr auto packet = "1";
      emscripten_websocket_send_utf8_text(_socket, packet);

      emscripten_websocket_close(_socket, 1000, "Normal closure");
      emscripten_websocket_delete(_socket);
      _socket = 0;
    }
  }

private:
  EMSCRIPTEN_WEBSOCKET_T _socket;
  std::string _url;
  std::function<void()> _on_open;
  std::function<void(const std::string &)> _on_message;
  std::function<void(const std::string &)> _on_close;
  std::function<void()> _on_error;
  std::unordered_map<std::string, std::function<void(const std::string &)>> _subscriptions;
};
#endif

int main(int argc, char **argv) {
  network::querybuilder qb;
  const auto query = qb
                         .add("EIO", "4")
                         .add("transport", "websocket")
                         .build();

  const auto url = fmt::format("{}/{}/?{}", "ws://localhost:9000", "socket.io", query);

#if 0
  socketio io(url);

  io.set_on_open([&]() {
    std::cout << "Connected to the server." << std::endl;

    io.subscribe("myevent", [](const std::string &data) {
      std::cout << "Received custom event data: " << data << std::endl;
    });
  });

  io.set_on_message([](const std::string &message) {
    std::cout << "Message received: " << message << std::endl;
  });

  io.set_on_close([](const std::string &reason) {
    std::cout << "Connection closed. Reason: " << reason << std::endl;
  });

  io.set_on_error([]() {
    std::cerr << "An error occurred." << std::endl;
  });

  // io.emit("echo", "Hello, Server!");

#endif

  framework::application app(argc, std::move(argv));

  return app.run();
}
