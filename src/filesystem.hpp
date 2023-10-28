#pragma once
#ifndef _filesystem_hpp
#define _filesystem_hpp

#include "internal.hpp"

class filesystem {
public:
  static void mount(const std::string_view &filename, const std::string_view &mountpoint);

private:
  filesystem() = default;
  ~filesystem() = default;
};

#endif