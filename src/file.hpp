#pragma once
#ifndef _file_hpp
#define _file_hpp

#include "common.hpp"

class file {
public:
  file() = default;
  ~file() = default;

  static const std::vector<uint8_t> read(const std::string &filename);
};

#endif