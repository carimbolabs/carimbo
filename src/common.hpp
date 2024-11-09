#pragma once

#ifdef DEBUG
#define SOL_ALL_SAFETIES_ON 1
#endif

#ifdef _WIN32
#define NOMINMAX
#endif

#include <AL/al.h>
#include <AL/alc.h>
#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>
#include <curl/curl.h>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <ogg/ogg.h>
#include <physfs.h>
#include <sol/sol.hpp>
#include <spng.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
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
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

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
class entitymanager;
class entityprops;
class framerate;
class garbagecollector;
class loopable;
class postalservice;
class resourcemanager;
class scenemanager;
class scriptengine;
class statemanager;
class timermanager;
}

namespace geometry {
class point;
class rect;
class size;
}

namespace graphics {
class effect;
class fontfactory;
class glyph;
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

using namespace std::literals;
