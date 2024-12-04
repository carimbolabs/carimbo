#include "socketio.hpp"

using namespace network;

socketio::socketio(const std::string &url)
    : _url(url), _socket(0) {}

socketio::~socketio() {
  disconnect();
}

void socketio::connect() {
  EmscriptenWebSocketCreateAttributes attrs = {
      _url.c_str(),
      nullptr,
      true
  };

  _socket = emscripten_websocket_new(&attrs);

  emscripten_websocket_set_onopen_callback(_socket, this, [](int, const EmscriptenWebSocketOpenEvent *event, void *data) {
    UNUSED(event);

    const auto *self = static_cast<socketio *>(data);

    self->invoke("connect");

    return EMSCRIPTEN_RESULT_SUCCESS;
  });

  emscripten_websocket_set_onmessage_callback(_socket, this, [](int, const EmscriptenWebSocketMessageEvent *event, void *data) {
    if (!event->isText) {
      return EMSCRIPTEN_RESULT_SUCCESS;
    }

    const auto *self = static_cast<socketio *>(data);

    const auto message = std::string(reinterpret_cast<const char *>(event->data), event->numBytes - 1);

    static const std::string zero = "0";
    if (message.starts_with(zero)) {
      self->send(zero);
    }

    static const std::string ping = "2";
    static const std::string pong = "3";
    if (message == ping) {
      self->send(pong);
    }

    static const std::string event_prefix = "42";
    if (message.starts_with(event_prefix)) {
      const auto start = message.find('[');
      const auto end = message.rfind(']');
      if (start != std::string::npos && end != std::string::npos) {
        const auto payload = message.substr(start + 1, end - start - 1);
        const auto separator = payload.find(',');
        if (separator != std::string::npos) {
          const auto event = payload.substr(1, separator - 2);
          const auto data = payload.substr(separator + 2, payload.size() - separator - 3);
          self->invoke(event, data);
        }
      }
    }

    return EMSCRIPTEN_RESULT_SUCCESS;
  });

  emscripten_websocket_set_onerror_callback(_socket, this, [](int, const EmscriptenWebSocketErrorEvent *event, void *data) {
    UNUSED(event);
    const auto *self = static_cast<socketio *>(data);
    fmt::print("Error occurred on WebSocket connected to {}\n", self->_url);
    self->invoke("error", "WebSocket error occurred");
    return EMSCRIPTEN_RESULT_SUCCESS;
  });

  emscripten_websocket_set_onclose_callback(_socket, this, [](int, const EmscriptenWebSocketCloseEvent *, void *data) {
    const auto *self = static_cast<socketio *>(data);
    fmt::print("Disconnected from {}\n", self->_url);
    self->invoke("disconnect");
    return EMSCRIPTEN_RESULT_SUCCESS;
  });
}

void socketio::disconnect() {
  constexpr int close_code = 1000;
  constexpr const char *reason = "Client disconnecting";

  if (_socket) {
    emscripten_websocket_close(_socket, close_code, reason);
    emscripten_websocket_delete(_socket);
    _socket = 0;
    invoke("disconnect");
  }
}

void socketio::emit(const std::string &event, const std::string &data) {
  send(fmt::format("42[\"{}\",\"{}\"]", event, data));
}

void socketio::on(const std::string &event, EventCallback callback) {
  _callbacks[event].push_back(std::move(callback));
}

void socketio::send(const std::string &message) const {
  if (_socket) {
    emscripten_websocket_send_utf8_text(_socket, message.c_str());
  }
}

void socketio::invoke(const std::string &event, const std::string &data) const {
  const auto it = _callbacks.find(event);
  if (it != _callbacks.end()) {
    for (const auto &callback : it->second) {
      callback(data);
    }
  }
}
