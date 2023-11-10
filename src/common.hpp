#pragma once
#ifndef _common_hpp
#define _common_hpp

#ifdef DEBUG
#define SOL_ALL_SAFETIES_ON 1
#endif

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
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include <fmt/core.h>
#include <sol/sol.hpp>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "constants.hpp"
#include "deleters.hpp"
#include "helpers.hpp"
#include "types.hpp"

class application;
class audiomanager;
class engine;
class enginefactory;
class entity;
class entitymanager;
class eventmanager;
class eventreceiver;
class filesystem;
class framerate;
class io;
class loopable;
class pixmap;
class pixmappool;
class renderer;
class resourcemanager;
class scriptengine;
class soundfx;
class soundmanager;
class statemanager;
class timermanager;
class window;

#endif
