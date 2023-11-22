#include "eventmanager.hpp"

#include "event.hpp"
#include "eventreceiver.hpp"

using namespace input;

void eventmanager::update() {
  SDL_Event event;

  SDL_PollEvent(&event);

  // while (SDL_PollEvent(&event)) {
  //  switch (event.type) {
  //  case SDL_QUIT:
  //    std::for_each(_receivers.begin(), _receivers.end(),
  //                  std::bind(&eventreceiver::on_quit, std::placeholders::_1));
  //    break;

  // case SDL_KEYDOWN:
  //   std::for_each(_receivers.begin(), _receivers.end(),
  //                 std::bind(&eventreceiver::on_keydown, std::placeholders::_1, keyevent(event.key.keysym.sym)));
  //   break;

  // case SDL_KEYUP:
  //   std::for_each(_receivers.begin(), _receivers.end(),
  //                 std::bind(&eventreceiver::on_keyup, std::placeholders::_1, keyevent(event.key.keysym.sym)));
  //   break;
  // }
  //}
}

void eventmanager::add_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.emplace_back(receiver);
}

void eventmanager::remove_receiver(std::shared_ptr<eventreceiver> receiver) {
  _receivers.remove(receiver);
}