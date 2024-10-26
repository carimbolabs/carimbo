#pragma once

#include "common.hpp"

struct SDL_Deleter {
  void operator()(SDL_Surface *ptr) const noexcept {
    if (ptr) {
      SDL_FreeSurface(ptr);
    }
  }

  void operator()(SDL_Texture *ptr) const noexcept {
    if (ptr) {
      SDL_DestroyTexture(ptr);
    }
  }

  void operator()(SDL_Renderer *ptr) const noexcept {
    if (ptr) {
      SDL_DestroyRenderer(ptr);
    }
  }

  void operator()(SDL_Window *ptr) const noexcept {
    if (ptr) {
      SDL_DestroyWindow(ptr);
    }
  }

  void operator()(SDL_RWops *ptr) const noexcept {
    if (ptr) {
      SDL_RWclose(ptr);
    }
  }

  void operator()(SDL_GameController *ptr) const noexcept {
    if (ptr) {
      SDL_GameControllerClose(ptr);
    }
  }
};
