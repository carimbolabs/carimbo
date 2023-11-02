#pragma once
#ifndef _common_hpp
#define _common_hpp

// #define SOL_ALL_SAFETIES_ON 1

extern "C" {
#include <SDL2/SDL.h>
#include <avif/avif.h>
#include <curl/curl.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <physfs.h>
}

#include <fmt/core.h>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <pybind11/embed.h>
#include <string>
#include <unordered_map>

#include "constants.hpp"
#include "deleters.hpp"
#include "types.hpp"

#endif
