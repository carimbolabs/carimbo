#pragma once
#ifndef _io_hpp
#define _io_hpp

#include "common.hpp"

namespace storage {
class io {
public:
  io() = delete;
  ~io() = delete;

  static const std::vector<uint8_t> read(std::string_view filename);
};
}

#endif