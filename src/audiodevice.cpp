#include "audiodevice.hpp"

using namespace audio;

audiodevice::audiodevice() {
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

audiodevice::~audiodevice() {
  SDL_CloseAudioDevice(0);
}

uint32_t audiodevice::id() const {
  return _id;
}
