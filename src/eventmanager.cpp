#include "eventmanager.hpp"

#include "event.hpp"
#include "eventreceiver.hpp"
#include "helpers.hpp"
#include "postalservice.hpp"
#include <iostream>

using namespace input;

eventmanager::eventmanager() {
  const auto number = SDL_NumJoysticks();
  for (auto id = 0; id < number; ++id) {
    if (!SDL_IsGameController(id)) {
      continue;
    }

    if (auto controller = SDL_GameControllerOpen(id)) {
      _controllers.emplace(id, gamecontroller_ptr(controller));
    }
  }
}

void eventmanager::update(double_t delta) {
  UNUSED(delta);

  static std::unordered_map<Uint8, SDL_Keycode> mapping = {
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
          [](const std::shared_ptr<eventreceiver> receiver) {
            receiver->on_quit();
          });
      break;

    case SDL_KEYDOWN:
      std::for_each(
          _receivers.begin(),
          _receivers.end(),
          [&event](const std::shared_ptr<eventreceiver> receiver) {
            receiver->on_keydown(keyevent(event.key.keysym.sym));
          });
      break;

    case SDL_KEYUP:
      std::for_each(
          _receivers.begin(),
          _receivers.end(),
          [&event](const std::shared_ptr<eventreceiver> receiver) {
            receiver->on_keyup(keyevent(event.key.keysym.sym));
          });
      break;

    case SDL_CONTROLLERDEVICEADDED: {
      if (!SDL_IsGameController(event.cdevice.which)) {
        break;
      }

      const auto controller = SDL_GameControllerOpen(event.cdevice.which);
      if (!controller) {
        break;
      }

      const auto joystick = SDL_GameControllerGetJoystick(controller);
      const auto id = SDL_JoystickInstanceID(joystick);

      _controllers[id] = gamecontroller_ptr(controller);
    } break;

    case SDL_CONTROLLERDEVICEREMOVED: {
      const auto it = _controllers.find(event.cdevice.which);

      if (it != _controllers.end()) {
        _controllers.erase(it);
      }
    } break;

    case SDL_CONTROLLERBUTTONDOWN: {
      if (const auto it = mapping.find(event.cbutton.button); it != mapping.end()) {
        std::for_each(
            _receivers.begin(),
            _receivers.end(),
            [&it](std::shared_ptr<eventreceiver> receiver) {
              receiver->on_keydown(keyevent(it->second));
            });
      }
    } break;

    case SDL_CONTROLLERBUTTONUP: {
      if (const auto it = mapping.find(event.cbutton.button); it != mapping.end()) {
        std::for_each(
            _receivers.begin(),
            _receivers.end(),
            [&it](std::shared_ptr<eventreceiver> receiver) {
              receiver->on_keyup(keyevent(it->second));
            });
      }
    } break;

    default:
      switch (event.type) {
      case input::eventtype::mail: {
        auto *ptr = static_cast<framework::mail *>(event.user.data1);

        if (ptr) {
          std::cout << " >>> UHUL " << ptr->body << " to " << ptr->to << std::endl;

          std::for_each(
              _receivers.begin(),
              _receivers.end(),
              [&ptr](const std::shared_ptr<eventreceiver> receiver) {
                receiver->on_mail(mailevent(ptr->to, ptr->body));
              });

          delete ptr;
        }
      } break;
      }
      break;
    }
  }
}

void eventmanager::add_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.emplace_back(std::move(receiver));
}

void eventmanager::remove_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.remove(receiver);
}
