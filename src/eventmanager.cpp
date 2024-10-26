#include "eventmanager.hpp"

using namespace input;

eventmanager::eventmanager() {
  const auto number = SDL_NumJoysticks();
  for (auto id = 0; id < number; ++id) {
    if (SDL_IsGameController(id)) {
      if (auto controller = SDL_GameControllerOpen(id)) {
        _controllers.emplace(id, gamecontroller_ptr(controller));
      }
    }
  }
}

void eventmanager::update(double_t delta) {
  UNUSED(delta);

  static const std::unordered_map<Uint8, SDL_Keycode> mapping = {
      {SDL_CONTROLLER_BUTTON_DPAD_UP, SDLK_w},
      {SDL_CONTROLLER_BUTTON_DPAD_LEFT, SDLK_a},
      {SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDLK_s},
      {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, SDLK_d},
      {SDL_CONTROLLER_BUTTON_A, SDLK_SPACE},
      {SDL_CONTROLLER_BUTTON_B, SDLK_SPACE},
  };

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      std::for_each(
          _receivers.begin(),
          _receivers.end(),
          [](const auto &receiver) {
            receiver->on_quit();
          }
      );
      break;

    case SDL_KEYDOWN:
      std::for_each(
          _receivers.begin(),
          _receivers.end(),
          [&event](const auto &receiver) {
            receiver->on_keydown(keyevent(event.key.keysym.sym));
          }
      );
      break;

    case SDL_KEYUP:
      std::for_each(
          _receivers.begin(),
          _receivers.end(),
          [&event](const auto &receiver) {
            receiver->on_keyup(keyevent(event.key.keysym.sym));
          }
      );
      break;

    case SDL_CONTROLLERDEVICEADDED:
      if (SDL_IsGameController(event.cdevice.which)) {
        if (auto controller = SDL_GameControllerOpen(event.cdevice.which)) {
          const auto joystick = SDL_GameControllerGetJoystick(controller);
          const auto id = SDL_JoystickInstanceID(joystick);
          _controllers[id] = gamecontroller_ptr(controller);
        }
      }
      break;

    case SDL_CONTROLLERDEVICEREMOVED:
      _controllers.erase(event.cdevice.which);
      break;

    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP: {
      const auto it = mapping.find(event.cbutton.button);
      if (it != mapping.end()) {
        const auto action = (event.type == SDL_CONTROLLERBUTTONDOWN) ? &eventreceiver::on_keydown : &eventreceiver::on_keyup;
        std::for_each(
            _receivers.begin(),
            _receivers.end(),
            [&it, action](const auto &receiver) {
              (receiver.get()->*action)(keyevent(it->second));
            }
        );
      }
    } break;

    case SDL_CONTROLLERAXISMOTION: {
      static const auto threshold = 8000;
      static const auto deadzone = 4000;
      const auto axis = event.caxis.axis;
      const auto value = event.caxis.value;

      if (axis == SDL_CONTROLLER_AXIS_LEFTY) {
        if (value < -threshold) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keydown(keyevent(SDLK_w));
          });
        } else if (value > threshold) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keydown(keyevent(SDLK_s));
          });
        } else if (abs(value) < deadzone) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keyup(keyevent(SDLK_w));
            receiver->on_keyup(keyevent(SDLK_s));
          });
        }
      } else if (axis == SDL_CONTROLLER_AXIS_LEFTX) {
        if (value < -threshold) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keydown(keyevent(SDLK_a));
          });
        } else if (value > threshold) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keydown(keyevent(SDLK_d));
          });
        } else if (abs(value) < deadzone) {
          std::for_each(_receivers.begin(), _receivers.end(), [](const auto &receiver) {
            receiver->on_keyup(keyevent(SDLK_a));
            receiver->on_keyup(keyevent(SDLK_d));
          });
        }
      }
    } break;

    case input::eventtype::mail: {
      auto *ptr = static_cast<framework::mail *>(event.user.data1);
      if (ptr) {
        std::for_each(
            _receivers.begin(),
            _receivers.end(),
            [&ptr](const auto &receiver) {
              receiver->on_mail(mailevent(ptr->to, ptr->body));
            }
        );
        delete ptr;
      }
    } break;

    default:
      break;
    }
  }
}

void eventmanager::add_receiver(std::shared_ptr<eventreceiver> receiver) noexcept {
  _receivers.emplace_back(std::move(receiver));
}

void eventmanager::remove_receiver(std::shared_ptr<eventreceiver> receiver) noexcept {
  _receivers.remove(receiver);
}
