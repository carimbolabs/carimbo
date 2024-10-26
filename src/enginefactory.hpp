#pragma once

#include "common.hpp"
#include <memory>
#include <string>

namespace framework {
class engine;

class enginefactory {
public:
  enginefactory() = default;
  virtual ~enginefactory() = default;

  enginefactory &set_title(const std::string &title) noexcept;
  enginefactory &set_width(int32_t width) noexcept;
  enginefactory &set_height(int32_t height) noexcept;
  enginefactory &set_fullscreen(bool fullscreen) noexcept;

  std::shared_ptr<engine> create();

private:
  std::string _title{"Untitled"};
  int32_t _width{800};
  int32_t _height{600};
  bool _fullscreen{false};
};
}
