#include "postalservice.hpp"

using namespace framework;

void postalservice::post(const mail &message) noexcept {
  SDL_Event event{};
  event.type = input::eventtype::mail;

  auto ptr = std::make_unique<mail>(message);
  event.user.data1 = ptr.release();
  SDL_PushEvent(&event);
}
