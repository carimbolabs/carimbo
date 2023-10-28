#pragma once
#ifndef _deleter_hpp
#define _deleter_hpp

#include "internal.hpp"

struct SDL_Deleter {
  inline void operator()(SDL_Surface *ptr) {
    SDL_FreeSurface(ptr);
  }

  inline void operator()(SDL_Texture *ptr) {
    SDL_DestroyTexture(ptr);
  }

  inline void operator()(SDL_Renderer *ptr) {
    SDL_DestroyRenderer(ptr);
  }

  inline void operator()(SDL_Window *ptr) {
    SDL_DestroyWindow(ptr);
  }

  inline void operator()(SDL_RWops *ptr) {
    SDL_RWclose(ptr);
  }
};

#endif