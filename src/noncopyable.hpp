#pragma once

class noncopyable {
public:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
  noncopyable(noncopyable &&) = default;
  noncopyable &operator=(noncopyable &&) = default;
};
