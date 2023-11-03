#pragma once
#ifndef _event_hpp
#define _event_hpp

#include "common.hpp"

enum class keyevent : int32_t {
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
};

enum class mouseevent : int32_t {};

enum class joysticevent {};

#endif