#pragma once
#ifndef _filesystem_hpp
#define _filesystem_hpp

#include "internal.hpp"

class filesystem {
public:
  static void mount(const std::string &filename, const std::string &mountpoint);

private:
  filesystem() = default;
  ~filesystem() = default;
};

#endif