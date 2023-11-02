#pragma once
#ifndef _enginefactory_hpp
#define _enginefactory_hpp

#include "common.hpp"
#include "engine.hpp"
#include "entitymanager.hpp"
#include "eventmanager.hpp"
#include "resourcemanager.hpp"

class enginefactory {
public:
  enginefactory() = default;

  virtual ~enginefactory() = default;

  void set_foo(const std::string &foo) {
    std::cout << "foo: " << foo << std::endl;
  }

  enginefactory &set_title(const std::string &title);

  enginefactory &set_width(int32_t width);

  enginefactory &set_height(int32_t height);

  enginefactory &set_fullscreen(bool fullscreen);

  std::shared_ptr<engine> create();

private:
  std::string _title;
  int32_t _width;
  int32_t _height;
  bool _fullscreen;
};

#endif