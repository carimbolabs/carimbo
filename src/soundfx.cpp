#include "soundfx.hpp"

soundfx::soundfx(std::string_view filename) {
  const auto buffer = io::read(filename);
}

void soundfx::play() const {
}
