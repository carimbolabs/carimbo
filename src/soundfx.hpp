#pragma soundfx
#ifndef _soundfx_hpp
#define _soundfx_hpp

#include "common.hpp"
#include "io.hpp"

class soundfx {
public:
  soundfx(std::string_view filename);
  ~soundfx() = default;

  void play() const;

private:
};

#endif
