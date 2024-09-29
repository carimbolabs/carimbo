#include "audiodevice.hpp"

using namespace audio;

audiodevice::audiodevice() : device(nullptr, [](ALCdevice *device) {
                               if (device) {
                                 alcCloseDevice(device);
                               }
                             }),
                             context(nullptr, [](ALCcontext *context) {
                               if (context) {
                                 alcDestroyContext(context);
                               }
                             }) {

  device.reset(alcOpenDevice(nullptr));
  if (!device) {
    throw std::runtime_error("Failed to open ALC device");
  }

  context.reset(alcCreateContext(device.get(), nullptr));
  if (!context) {
    throw std::runtime_error("Failed to create ALC context");
  }

  alcMakeContextCurrent(context.get());
  std::cout << "ALC device and context initialized successfully." << std::endl;

  // SDL_AudioSpec spec{};
  // spec.format = AUDIO_S16SYS;
  // spec.freq = 44100;
  // spec.channels = 2;
  // spec.samples = 4096;
  // _id = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);

  // if (_id == 0) {
  //   throw std::runtime_error(
  //       fmt::format("[SDL_OpenAudioDevice] error while opening audio device: {}", SDL_GetError()));
  // }
}

audiodevice::~audiodevice() {
  std::cout << ">>> audiodevice::~audiodevice()" << std::endl;
  if (context) {
    alcMakeContextCurrent(nullptr);
    std::cout << "ALC context unset successfully." << std::endl;
  }

  /* SDL_CloseAudioDevice(0); */
}

// uint32_t audiodevice::id() const { return _id; }
