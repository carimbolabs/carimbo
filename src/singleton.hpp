#pragma once
#ifndef _singleton_hpp
#define _singleton_hpp

#include "common.hpp"

template <typename T>
class singleton {
public:
  virtual ~singleton() = default;

  static std::shared_ptr<T> instance();
};

// #include "singleton.cpp"

#endif