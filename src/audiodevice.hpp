#pragma once
#ifndef _audiodevice_hpp
#define _audiodevice_hpp

#include "common.hpp"

class audiodevice {
public:
  audiodevice();
  virtual ~audiodevice();

  uint32_t id() const;

private:
  uint32_t _id;
};

#endif