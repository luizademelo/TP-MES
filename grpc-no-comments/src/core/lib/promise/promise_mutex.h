// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_PROMISE_MUTEX_H
#define GRPC_SRC_CORE_LIB_PROMISE_PROMISE_MUTEX_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {

template <typename T>
class PromiseMutex {
 public:
  class Lock {
   public:
    Lock() {}
    ~Lock() {
      if (mutex_ != nullptr) {
        CHECK(mutex_->locked_);
        mutex_->locked_ = false;
        mutex_->waiter_.Wake();
      }
    }

    Lock(Lock&& other) noexcept
        : mutex_(std::exchange(other.mutex_, nullptr)) {}
    Lock& operator=(Lock&& other) noexcept {
      std::swap(mutex_, other.mutex_);
      return *this;
    }

    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) noexcept = delete;

    T* operator->() {
      DCHECK_NE(mutex_, nullptr);
      return &mutex_->value_;
    }
    T& operator*() {
      DCHECK_NE(mutex_, nullptr);
      return mutex_->value_;
    }

   private:
    friend class PromiseMutex;
    explicit Lock(PromiseMutex* mutex) : mutex_(mutex) {
      DCHECK(!mutex_->locked_);
      mutex_->locked_ = true;
    }
    PromiseMutex* mutex_ = nullptr;
  };

  PromiseMutex() = default;
  explicit PromiseMutex(T value) : value_(std::move(value)) {}
  ~PromiseMutex() { DCHECK(!locked_); }

  auto Acquire() {
    return [this]() -> Poll<Lock> {
      if (locked_) return waiter_.pending();
      return Lock(this);
    };
  }

 private:
  bool locked_ = false;
  IntraActivityWaiter waiter_;
  GPR_NO_UNIQUE_ADDRESS T value_;
};

}

#endif
