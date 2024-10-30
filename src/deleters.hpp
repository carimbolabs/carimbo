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

struct Box2D_Deleter {
  void operator()(b2WorldId *ptr) const noexcept {
    if (ptr) {
      delete ptr;
    }
  }

  // void operator()(b2BodyId *ptr) const noexcept {
  //   if (ptr) {
  //     const auto world = ptr->world0
  //     if (world) {
  //       world->DestroyBody(ptr);
  //     }
  //   }
  // }

  // void operator()(b2Fixture *ptr) const noexcept {
  //   if (ptr) {
  //     b2Body *body = ptr->GetBody();
  //     if (body) {
  //       body->DestroyFixture(ptr);
  //     }
  //   }
  // }

  // void operator()(b2Joint *ptr) const noexcept {
  //   if (ptr) {
  //     b2World *world = ptr->GetBodyA()->GetWorld(); // ou ptr->GetBodyB()->GetWorld()
  //     if (world) {
  //       world->DestroyJoint(ptr);
  //     }
  //   }
  // }

  // void operator()(b2Shape *ptr) const noexcept {
  //   if (ptr) {
  //     delete ptr;
  //   }
  // }
};
