#include "eventreceiver.hpp"

#include "event.hpp"

void eventreceiver::on_quit() {}

void eventreceiver::on_keydown(const keyevent &event) {
  UNUSED(event);
}

void eventreceiver::on_keyup(const keyevent &event) {
  UNUSED(event);
}