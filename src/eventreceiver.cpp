#include "eventreceiver.hpp"

using namespace input;

void eventreceiver::on_quit() noexcept {}

void eventreceiver::on_keydown(const keyevent &event) noexcept { UNUSED(event); }

void eventreceiver::on_keyup(const keyevent &event) noexcept { UNUSED(event); }

void eventreceiver::on_mail(const mailevent &event) noexcept { UNUSED(event); }
