#include "eventmanager.hpp"

#include "event.hpp"
#include "eventreceiver.hpp"

using namespace input;

eventmanager::eventmanager() {
  const auto number = SDL_NumJoysticks();
  for (auto id = 0; id < number; ++id) {
    if (!SDL_IsGameController(id)) {
      continue;
    }
    const auto controller = SDL_GameControllerOpen(id);
    if (!controller) {
      continue;
    }
    _controllers[id] = gamecontroller_ptr(controller);
  }
}

void eventmanager::update() {
  static std::unordered_map<Uint8, SDL_Keycode> mapping = {
      {SDL_CONTROLLER_BUTTON_DPAD_UP, SDLK_w},
      {SDL_CONTROLLER_BUTTON_DPAD_LEFT, SDLK_a},
      {SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDLK_s},
      {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, SDLK_d}};

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      std::for_each(_receivers.begin(), _receivers.end(),
                    [](const std::shared_ptr<eventreceiver> receiver) {
                      receiver->on_quit();
                    });
      break;

    case SDL_KEYDOWN:
      std::for_each(_receivers.begin(), _receivers.end(),
                    [&event](const std::shared_ptr<eventreceiver> receiver) {
                      receiver->on_keydown(keyevent(event.key.keysym.sym));
                    });
      break;

    case SDL_KEYUP:
      std::for_each(_receivers.begin(), _receivers.end(),
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

      std::cout << "Controller added: " << id << std::endl;

      // const auto controller = SDL_GameControllerOpen(event.cdevice.which);
      // if (controller == nullptr) {
      //   throw std::runtime_error(fmt::format(
      //       "[SDL_GameControllerOpen] could not open game controller: {}",
      //       SDL_GetError()));
      // }
    } break;

    case SDL_CONTROLLERDEVICEREMOVED: {
      const auto it = _controllers.find(event.cdevice.which);

      if (it != _controllers.end()) {
        _controllers.erase(it);
      }
    } break;

    case SDL_CONTROLLERBUTTONDOWN: {
      const auto it = mapping.find(event.cbutton.button);
      if (it != mapping.end()) {
        std::for_each(_receivers.begin(), _receivers.end(),
                      [&it](std::shared_ptr<eventreceiver> receiver) {
                        receiver->on_keydown(keyevent(it->second));
                      });
      }
    } break;

    case SDL_CONTROLLERBUTTONUP: {
      const auto it = mapping.find(event.cbutton.button);
      if (it != mapping.end()) {
        std::for_each(_receivers.begin(), _receivers.end(),
                      [&it](std::shared_ptr<eventreceiver> receiver) {
                        receiver->on_keyup(keyevent(it->second));
                      });
      }
    } break;
    }
  }
}

void eventmanager::add_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.emplace_back(receiver);
}

void eventmanager::remove_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.remove(receiver);
}
