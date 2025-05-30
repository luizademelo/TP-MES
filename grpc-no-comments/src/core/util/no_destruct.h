// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_NO_DESTRUCT_H
#define GRPC_SRC_CORE_UTIL_NO_DESTRUCT_H

#include <grpc/support/port_platform.h>

#include <type_traits>
#include <utility>

#include "src/core/util/construct_destruct.h"

namespace grpc_core {

template <typename T>
class NoDestruct {
 public:
  template <typename... Args>
  explicit NoDestruct(Args&&... args) {
    static_assert(std::is_trivially_destructible<NoDestruct<T>>::value,
                  "NoDestruct must be trivially destructible");
    Construct(reinterpret_cast<T*>(&space_), std::forward<Args>(args)...);
  }
  NoDestruct(const NoDestruct&) = delete;
  NoDestruct& operator=(const NoDestruct&) = delete;
  ~NoDestruct() = default;

  T* operator->() { return get(); }
  const T* operator->() const { return get(); }
  T& operator*() { return *get(); }
  const T& operator*() const { return *get(); }

  T* get() { return reinterpret_cast<T*>(&space_); }
  const T* get() const { return reinterpret_cast<const T*>(&space_); }

 private:
  alignas(T) char space_[sizeof(T)];
};

template <typename T>
class NoDestructSingleton {
 public:
  static T* Get() { return &*value_; }

 private:
  NoDestructSingleton() = delete;
  ~NoDestructSingleton() = delete;

  static NoDestruct<T> value_;
};

template <typename T>
NoDestruct<T> NoDestructSingleton<T>::value_;

}

#endif
