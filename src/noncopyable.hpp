#pragma once
#ifndef _noncopyable_hpp_
#define _noncopyable_hpp_

class noncopyable {
public:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};

#endif