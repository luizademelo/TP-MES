// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SINGLE_SET_PTR_H
#define GRPC_SRC_CORE_UTIL_SINGLE_SET_PTR_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <memory>

#include "absl/log/check.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

template <class T, class Deleter = std::default_delete<T>>
class SingleSetPtr {
 public:
  SingleSetPtr() = default;
  explicit SingleSetPtr(T* p) : p_{p} {}
  explicit SingleSetPtr(std::unique_ptr<T, Deleter> p) : p_{p.release()} {}
  ~SingleSetPtr() { Delete(p_.load(std::memory_order_relaxed)); }

  SingleSetPtr(const SingleSetPtr&) = delete;
  SingleSetPtr& operator=(const SingleSetPtr&) = delete;
  SingleSetPtr(SingleSetPtr&& other) noexcept
      : p_(other.p_.exchange(nullptr)) {}
  SingleSetPtr& operator=(SingleSetPtr&& other) noexcept {
    Set(other.p_.exchange(nullptr, std::memory_order_acq_rel));
    return *this;
  }

  T* Set(T* ptr) {
    T* expected = nullptr;
    if (!p_.compare_exchange_strong(expected, ptr, std::memory_order_acq_rel,
                                    std::memory_order_acquire)) {
      Delete(ptr);
      return expected;
    }
    return ptr;
  }

  T* Set(std::unique_ptr<T, Deleter> ptr) { return Set(ptr.release()); }

  void Reset() { Delete(p_.exchange(nullptr, std::memory_order_acq_rel)); }

  bool is_set() const { return p_.load(std::memory_order_relaxed) != nullptr; }

  T* Get() const { return p_.load(std::memory_order_acquire); }

  T* operator->() const {
    T* p = Get();
    DCHECK_NE(p, nullptr);
    return p;
  }

  T& operator*() const { return *Get(); }

 private:
  static void Delete(T* p) {
    if (p == nullptr) return;
    Deleter()(p);
  }
  std::atomic<T*> p_{nullptr};
};

template <class T>
class SingleSetRefCountedPtr {
 public:
  SingleSetRefCountedPtr() = default;
  explicit SingleSetRefCountedPtr(RefCountedPtr<T> p) : p_{p.Release()} {}

  bool is_set() const { return p_.is_set(); }

  RefCountedPtr<T> GetOrCreate() {
    T* p = Get();
    if (p == nullptr) p = Set(MakeRefCounted<T>());
    return p->Ref();
  }
  T* Get() const { return p_.Get(); }

  T* operator->() const {
    T* p = Get();
    DCHECK_NE(p, nullptr);
    return p;
  }

  T& operator*() const { return *Get(); }

 private:
  struct UnrefDeleter {
    void operator()(T* p) { p->Unref(); }
  };

  T* Set(RefCountedPtr<T> p) { return p_.Set(p.release()); }

  SingleSetPtr<T, UnrefDeleter> p_;
};

}

#endif
