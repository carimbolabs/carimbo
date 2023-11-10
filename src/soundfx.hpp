#pragma once
#ifndef _soundfx_hpp
#define _soundfx_hpp

#include "common.hpp"

class soundfx {
public:
  soundfx(std::string_view filename);
  ~soundfx();

  void play() const;

  std::vector<uint8_t> buffer;

private:
};

#endif
