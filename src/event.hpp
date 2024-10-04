#pragma once

#include "common.hpp"

namespace input {
enum eventtype : Uint32 {
  mail = SDL_USEREVENT + 1,
};

enum class keyevent : int32_t {
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
  space = SDLK_SPACE,
};

enum class mouseevent : int32_t {};

enum class joysticevent : int32_t {
  dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP,
  dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
};
}
