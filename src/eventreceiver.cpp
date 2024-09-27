#include "eventreceiver.hpp"

#include "event.hpp"

using namespace input;

void eventreceiver::on_quit() {}

void eventreceiver::on_keydown(const keyevent &event) { UNUSED(event); }

void eventreceiver::on_keyup(const keyevent &event) { UNUSED(event); }
