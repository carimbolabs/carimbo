#include "audiomanager.hpp"

audiomanager::audiomanager() {
  SDL_AudioSpec spec{};
  spec.format = AUDIO_S16SYS;
  spec.freq = 44100;
  spec.channels = 2;
  spec.samples = 4096;
  _id = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);

  if (_id == 0) {
    throw std::runtime_error(fmt::format("[SDL_OpenAudioDevice] error while opening audio device: {}", SDL_GetError()));
  }
}

audiomanager::~audiomanager() {
  SDL_CloseAudioDevice(0);
}

uint32_t audiomanager::get_device() const {
  return _id;
}
