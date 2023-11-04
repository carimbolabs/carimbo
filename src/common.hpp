#pragma once
#ifndef _common_hpp
#define _common_hpp

#define SOL_ALL_SAFETIES_ON 1

extern "C" {
#include <SDL2/SDL.h>
#include <avif/avif.h>
#include <curl/curl.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <physfs.h>
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

#include "constants.hpp"
#include "deleters.hpp"
#include "types.hpp"

// #include <mimalloc-new-delete.h>
// #include <mimalloc-override.h>

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
