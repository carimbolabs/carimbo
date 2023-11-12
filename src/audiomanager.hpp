#pragma once
#ifndef _audiomanager_hpp
#define _audiomanager_hpp

#include "common.hpp"

class audiomanager {
public:
  audiomanager();
  virtual ~audiomanager();

  uint32_t get_device() const;

private:
  uint32_t _id;
};

#endif