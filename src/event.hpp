#pragma once
#ifndef _event_hpp
#define _event_hpp

#include "common.hpp"

enum class eventtype {
  quit,
  keydown,
  keyup,
  mousemotion,
  mousebuttondown,
  mousebuttonup,
  mousewheel,
  windowevent,
};

enum class keyevent : int32_t {
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
};

struct event {
  eventtype type;
  union {
    struct {
      keyevent key;
    } keyevent;
  } data;
};

#endif