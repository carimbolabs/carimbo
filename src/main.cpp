#include "application.hpp"

#include "common.hpp"
#include "querybuilder.hpp"

class socketio {
public:
  explicit socketio(const std::string &url) {
    if (!emscripten_websocket_is_supported()) {
      throw std::runtime_error("WebSocket is not supported in this environment.");
    }

    std::cout << "url " << url << std::endl;

    EmscriptenWebSocketCreateAttributes attributes = {
        url.c_str(), nullptr, true
    };
    socket = emscripten_websocket_new(&attributes);
    if (socket <= 0) {
      throw std::runtime_error("Failed to create WebSocket.");
    }

    emscripten_websocket_set_onopen_callback(socket, this, [](int, const EmscriptenWebSocketOpenEvent *event, void *user_data) -> EM_BOOL {
      UNUSED(event);
      const auto self = static_cast<socketio *>(user_data);

      std::string connectMessage = R"({"type":"connect"})"; // Exemplo de formato JSON
      emscripten_websocket_send_utf8_text(event->socket, connectMessage.c_str());

      if (self->on_open) self->on_open();
      return true;
    });

    emscripten_websocket_set_onmessage_callback(socket, this, [](int, const EmscriptenWebSocketMessageEvent *event, void *user_data) -> EM_BOOL {
      auto self = static_cast<socketio *>(user_data);
      if (event->isText && self->on_message) {
        std::string message(event->data, event->data + event->numBytes);
        self->on_message(message);
      }
      return true;
    });

    emscripten_websocket_set_onclose_callback(socket, this, [](int, const EmscriptenWebSocketCloseEvent *event, void *user_data) -> EM_BOOL {
      auto self = static_cast<socketio *>(user_data);
      if (self->on_close) self->on_close(event->reason);
      return true;
    });

    emscripten_websocket_set_onerror_callback(socket, this, [](int, const EmscriptenWebSocketErrorEvent *, void *user_data) -> EM_BOOL {
      auto self = static_cast<socketio *>(user_data);
      if (self->on_error) self->on_error();
      return true;
    });
  }

  ~socketio() {
    if (socket > 0) {
      emscripten_websocket_close(socket, 1000, "Normal closure");
      emscripten_websocket_delete(socket);
    }
  }

  void emit(const std::string &event, const std::string &message) {
    if (socket > 0) {
      const auto packet = fmt::format("42[\"{}\",\"{}\"]", event, message);
      emscripten_websocket_send_utf8_text(socket, packet.data());
    }
  }

  void set_on_open(const std::function<void()> &callback) {
    on_open = callback;
  }

  void set_on_message(const std::function<void(const std::string &)> &callback) {
    on_message = callback;
  }

  void set_on_close(const std::function<void(const std::string &)> &callback) {
    on_close = callback;
  }

  void set_on_error(const std::function<void()> &callback) {
    on_error = callback;
  }

private:
  EMSCRIPTEN_WEBSOCKET_T socket;
  std::function<void()> on_open;
  std::function<void(const std::string &)> on_message;
  std::function<void(const std::string &)> on_close;
  std::function<void()> on_error;
};

int main(int argc, char **argv) {
  network::querybuilder qb;
  const auto query = qb.add("EIO", "4")
                         .add("transport", "websocket")
                         .build();

  socketio io(fmt::format("{}/{}/?{}", "ws://localhost:9000", "socket.io", query));

  io.set_on_open([]() {
    std::cout << "Connected to the server." << std::endl;
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

  framework::application app(argc, std::move(argv));

  return app.run();
}
