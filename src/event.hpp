#pragma once

#include "common.hpp"

namespace input {
enum class keyevent : int32_t {
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
  space = SDLK_SPACE,
};

enum class mouseevent : int32_t {};

enum class joysticevent {};
}
