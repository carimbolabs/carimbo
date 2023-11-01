#pragma once
#ifndef _singleton_hpp
#define _singleton_hpp

#include "common.hpp"

template <typename T>
class singleton {
public:
  virtual ~singleton() = default;

  static std::shared_ptr<T> instance() {
    static std::once_flag flag;
    static std::shared_ptr<T> instance;

    std::call_once(flag, []() { instance = std::make_shared<T>(); });

    return instance;
  }
};

#endif