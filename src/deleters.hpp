#pragma once

#include "common.hpp"

struct SDL_Deleter {
  inline void operator()(SDL_Surface *ptr) {
    if (ptr) {
      SDL_FreeSurface(ptr);
    }
  }

  inline void operator()(SDL_Texture *ptr) {
    if (ptr) {
      SDL_DestroyTexture(ptr);
    }
  }

  inline void operator()(SDL_Renderer *ptr) {
    if (ptr) {
      SDL_DestroyRenderer(ptr);
    }
  }

  inline void operator()(SDL_Window *ptr) {
    if (ptr) {
      SDL_DestroyWindow(ptr);
    }
  }

  inline void operator()(SDL_RWops *ptr) {
    if (ptr) {
      SDL_RWclose(ptr);
    }
  }

  inline void operator()(SDL_GameController *ptr) const {
    if (ptr) {
      SDL_GameControllerClose(ptr);
    }
  }

  inline void operator()(spng_ctx *ptr) {
    if (ptr) {
      spng_ctx_free(ptr);
    }
  }
};
