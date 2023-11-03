#include "singleton.hpp"

template <typename T>
std::shared_ptr<T> singleton<T>::instance() {
  static std::once_flag flag;
  static std::shared_ptr<T> instance;

  std::call_once(flag, []() { instance = std::make_shared<T>(); });

  return instance;
}