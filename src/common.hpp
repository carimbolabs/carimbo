#pragma once

#ifdef DEBUG
#define SOL_ALL_SAFETIES_ON 1
#endif

#define NOMINMAX

extern "C" {
#include <AL/al.h>
#include <AL/alc.h>
// #include <AL/alext.h>
#include <SDL2/SDL.h>
#include <curl/curl.h>
#include <ogg/ogg.h>
#include <physfs.h>
#include <spng.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
}

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <sol/sol.hpp>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "constants.hpp"
#include "deleters.hpp"
#include "helpers.hpp"
#include "types.hpp"

namespace audio {
class audiodevice;
class soundfx;
class soundmanager;
}

namespace framework {
class application;
class engine;
class enginefactory;
class entity;
class entityprops;
class entitymanager;
class framerate;
class garbagecollector;
class loopable;
class resourcemanager;
class scriptengine;
class statemanager;
class timermanager;
}

namespace storage {
class filesystem;
class io;
}

namespace geometry {
class point;
class rect;
class size;
}

namespace graphics {
class pixmap;
class pixmappool;
class renderer;
class window;
}

namespace input {
class eventmanager;
class eventreceiver;
}

namespace math {
class vector2d;
}
