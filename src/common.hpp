#pragma once
#ifndef _common_hpp
#define _common_hpp

#ifdef DEBUG
#define SOL_ALL_SAFETIES_ON 1
#endif

#define NOMINMAX

extern "C" {
#include <SDL2/SDL.h>
#include <avif/avif.h>
#include <curl/curl.h>
#include <ogg/ogg.h>
#include <physfs.h>
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
} // namespace audio

namespace framework {
class application;
class engine;
class enginefactory;
class entity;
class entitymanager;
class framerate;
class loopable;
class resourcemanager;
class scriptengine;
class statemanager;
class timermanager;
enum class resourcetype;
} // namespace framework

namespace storage {
class filesystem;
class io;
} // namespace storage

namespace geometry {
class point;
class rect;
class size;
} // namespace geometry

namespace graphics {
class pixmap;
class pixmappool;
class renderer;
class window;
} // namespace graphics

namespace input {
class eventmanager;
class eventreceiver;
} // namespace input

#endif
