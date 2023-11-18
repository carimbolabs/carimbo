#pragma once
#ifndef _filesystem_hpp
#define _filesystem_hpp

#include "common.hpp"

namespace storage {
class filesystem {
public:
  static void mount(std::string_view filename, std::string_view mountpoint);

private:
  constexpr filesystem() noexcept = default;
  ~filesystem() noexcept = default;
};
}

#endif