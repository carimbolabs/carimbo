#include "postalservice.hpp"

using namespace framework;

postalservice::postalservice() {
}

void postalservice::post(const std::string_view message, uint64_t to) {
  SDL_Event event{};
  event.type = static_cast<Uint32>(input::eventtype::mail);
  // event.type = _eventtype;
  // event.user.code = _eventcode;
  event.user.data1 = static_cast<void *>(new mail(to, message));

  SDL_PushEvent(&event);
}
