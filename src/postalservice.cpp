#include "postalservice.hpp"

using namespace framework;

void postalservice::post(const mail &message) {
  SDL_Event event{};
  event.type = input::eventtype::mail;

  auto *ptr = new mail(message);
  event.user.data1 = static_cast<void *>(ptr);

  SDL_PushEvent(&event);
}
