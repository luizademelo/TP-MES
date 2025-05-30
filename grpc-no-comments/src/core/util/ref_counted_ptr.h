
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_REF_COUNTED_PTR_H
#define GRPC_SRC_CORE_UTIL_REF_COUNTED_PTR_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <iosfwd>
#include <type_traits>
#include <utility>

#include "absl/hash/hash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"

namespace grpc_core {

template <typename T>
class RefCountedPtr {
 public:
  RefCountedPtr() {}

  RefCountedPtr(std::nullptr_t) {}

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  explicit RefCountedPtr(Y* value) : value_(value) {}

  RefCountedPtr(RefCountedPtr&& other) noexcept {
    value_ = other.value_;
    other.value_ = nullptr;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>

  RefCountedPtr(RefCountedPtr<Y>&& other) noexcept {
    value_ = static_cast<T*>(other.value_);
    other.value_ = nullptr;
  }

  RefCountedPtr& operator=(RefCountedPtr&& other) noexcept {
    reset(std::exchange(other.value_, nullptr));
    return *this;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  RefCountedPtr& operator=(RefCountedPtr<Y>&& other) noexcept {
    reset(std::exchange(other.value_, nullptr));
    return *this;
  }

  RefCountedPtr(const RefCountedPtr& other) {
    if (other.value_ != nullptr) other.value_->IncrementRefCount();
    value_ = other.value_;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>

  RefCountedPtr(const RefCountedPtr<Y>& other) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    if (other.value_ != nullptr) other.value_->IncrementRefCount();
    value_ = static_cast<T*>(other.value_);
  }

  RefCountedPtr& operator=(const RefCountedPtr& other) {
    // Note: Order of reffing and unreffing is important here in case value_

    if (other.value_ != nullptr) other.value_->IncrementRefCount();
    reset(other.value_);
    return *this;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  RefCountedPtr& operator=(const RefCountedPtr<Y>& other) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    // Note: Order of reffing and unreffing is important here in case value_

    if (other.value_ != nullptr) other.value_->IncrementRefCount();
    reset(other.value_);
    return *this;
  }

  ~RefCountedPtr() {
    if (value_ != nullptr) value_->Unref();
  }

  RefCountedPtr<T> Ref(const DebugLocation& location, const char* reason) {
    if (value_ != nullptr) value_->IncrementRefCount(location, reason);
    return RefCountedPtr<T>(value_);
  }

  void swap(RefCountedPtr& other) { std::swap(value_, other.value_); }

  void reset(T* value = nullptr) {
    T* old_value = std::exchange(value_, value);
    if (old_value != nullptr) old_value->Unref();
  }
  void reset(const DebugLocation& location, const char* reason,
             T* value = nullptr) {
    T* old_value = std::exchange(value_, value);
    if (old_value != nullptr) old_value->Unref(location, reason);
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  void reset(Y* value = nullptr) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    reset(static_cast<T*>(value));
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  void reset(const DebugLocation& location, const char* reason,
             Y* value = nullptr) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    reset(location, reason, static_cast<T*>(value));
  }

  T* release() { return std::exchange(value_, nullptr); }

  T* get() const { return value_; }

  T& operator*() const { return *value_; }
  T* operator->() const { return value_; }

  template <typename Y,
            std::enable_if_t<std::is_base_of<T, Y>::value, bool> = true>
  RefCountedPtr<Y> TakeAsSubclass() {
    return RefCountedPtr<Y>(DownCast<Y*>(release()));
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator==(const RefCountedPtr<Y>& other) const {
    return value_ == other.value_;
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator==(const Y* other) const {
    return value_ == other;
  }

  bool operator==(std::nullptr_t) const { return value_ == nullptr; }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator!=(const RefCountedPtr<Y>& other) const {
    return value_ != other.value_;
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator!=(const Y* other) const {
    return value_ != other;
  }

  bool operator!=(std::nullptr_t) const { return value_ != nullptr; }

 private:
  template <typename Y>
  friend class RefCountedPtr;

  T* value_ = nullptr;
};

template <typename T>
class WeakRefCountedPtr {
 public:
  WeakRefCountedPtr() {}

  WeakRefCountedPtr(std::nullptr_t) {}

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  explicit WeakRefCountedPtr(Y* value) {
    value_ = value;
  }

  WeakRefCountedPtr(WeakRefCountedPtr&& other) noexcept {
    value_ = other.value_;
    other.value_ = nullptr;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>

  WeakRefCountedPtr(WeakRefCountedPtr<Y>&& other) noexcept {
    value_ = static_cast<T*>(other.value_);
    other.value_ = nullptr;
  }

  WeakRefCountedPtr& operator=(WeakRefCountedPtr&& other) noexcept {
    reset(std::exchange(other.value_, nullptr));
    return *this;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  WeakRefCountedPtr& operator=(WeakRefCountedPtr<Y>&& other) noexcept {
    reset(std::exchange(other.value_, nullptr));
    return *this;
  }

  WeakRefCountedPtr(const WeakRefCountedPtr& other) {
    if (other.value_ != nullptr) other.value_->IncrementWeakRefCount();
    value_ = other.value_;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>

  WeakRefCountedPtr(const WeakRefCountedPtr<Y>& other) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    if (other.value_ != nullptr) other.value_->IncrementWeakRefCount();
    value_ = static_cast<T*>(other.value_);
  }

  WeakRefCountedPtr& operator=(const WeakRefCountedPtr& other) {
    // Note: Order of reffing and unreffing is important here in case value_

    if (other.value_ != nullptr) other.value_->IncrementWeakRefCount();
    reset(other.value_);
    return *this;
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  WeakRefCountedPtr& operator=(const WeakRefCountedPtr<Y>& other) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    // Note: Order of reffing and unreffing is important here in case value_

    if (other.value_ != nullptr) other.value_->IncrementWeakRefCount();
    reset(other.value_);
    return *this;
  }

  ~WeakRefCountedPtr() {
    if (value_ != nullptr) value_->WeakUnref();
  }

  WeakRefCountedPtr<T> WeakRef(const DebugLocation& location,
                               const char* reason) {
    if (value_ != nullptr) value_->IncrementWeakRefCount(location, reason);
    return WeakRefCountedPtr<T>(value_);
  }

  void swap(WeakRefCountedPtr& other) { std::swap(value_, other.value_); }

  void reset(T* value = nullptr) {
    T* old_value = std::exchange(value_, value);
    if (old_value != nullptr) old_value->WeakUnref();
  }
  void reset(const DebugLocation& location, const char* reason,
             T* value = nullptr) {
    T* old_value = std::exchange(value_, value);
    if (old_value != nullptr) old_value->WeakUnref(location, reason);
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  void reset(Y* value = nullptr) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    reset(static_cast<T*>(value));
  }
  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  void reset(const DebugLocation& location, const char* reason,
             Y* value = nullptr) {
    static_assert(std::has_virtual_destructor<T>::value,
                  "T does not have a virtual dtor");
    reset(location, reason, static_cast<T*>(value));
  }

  T* release() { return std::exchange(value_, nullptr); }

  T* get() const { return value_; }

  T& operator*() const { return *value_; }
  T* operator->() const { return value_; }

  template <typename Y,
            std::enable_if_t<std::is_base_of<T, Y>::value, bool> = true>
  WeakRefCountedPtr<Y> TakeAsSubclass() {
    return WeakRefCountedPtr<Y>(static_cast<Y*>(release()));
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator==(const WeakRefCountedPtr<Y>& other) const {
    return value_ == other.value_;
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator==(const Y* other) const {
    return value_ == other;
  }

  bool operator==(std::nullptr_t) const { return value_ == nullptr; }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator!=(const WeakRefCountedPtr<Y>& other) const {
    return value_ != other.value_;
  }

  template <typename Y,
            std::enable_if_t<std::is_convertible<Y*, T*>::value, bool> = true>
  bool operator!=(const Y* other) const {
    return value_ != other;
  }

  bool operator!=(std::nullptr_t) const { return value_ != nullptr; }

 private:
  template <typename Y>
  friend class WeakRefCountedPtr;

  T* value_ = nullptr;
};

template <typename T, typename... Args>
inline RefCountedPtr<T> MakeRefCounted(Args&&... args) {
  return RefCountedPtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
bool operator<(const RefCountedPtr<T>& p1, const RefCountedPtr<T>& p2) {
  return p1.get() < p2.get();
}

template <typename T>
bool operator<(const WeakRefCountedPtr<T>& p1, const WeakRefCountedPtr<T>& p2) {
  return p1.get() < p2.get();
}

template <typename H, typename T>
H AbslHashValue(H h, const RefCountedPtr<T>& p) {
  return H::combine(std::move(h), p.get());
}

template <typename H, typename T>
H AbslHashValue(H h, const WeakRefCountedPtr<T>& p) {
  return H::combine(std::move(h), p.get());
}

template <typename T>
struct RefCountedPtrHash {
  using is_transparent = void;
  size_t operator()(const RefCountedPtr<T>& p) const {
    return absl::Hash<RefCountedPtr<T>>{}(p);
  }
  size_t operator()(const WeakRefCountedPtr<T>& p) const {
    return absl::Hash<WeakRefCountedPtr<T>>{}(p);
  }
  size_t operator()(T* p) const { return absl::Hash<T*>{}(p); }
  size_t operator()(const T* p) const { return absl::Hash<const T*>{}(p); }
};
template <typename T>
struct RefCountedPtrEq {
  using is_transparent = void;
  bool operator()(const RefCountedPtr<T>& p1,
                  const RefCountedPtr<T>& p2) const {
    return p1 == p2;
  }
  bool operator()(const WeakRefCountedPtr<T>& p1,
                  const WeakRefCountedPtr<T>& p2) const {
    return p1 == p2;
  }
  bool operator()(const RefCountedPtr<T>& p1,
                  const WeakRefCountedPtr<T>& p2) const {
    return p1 == p2.get();
  }
  bool operator()(const WeakRefCountedPtr<T>& p1,
                  const RefCountedPtr<T>& p2) const {
    return p1 == p2.get();
  }
  bool operator()(const RefCountedPtr<T>& p1, const T* p2) const {
    return p1 == p2;
  }
  bool operator()(const WeakRefCountedPtr<T>& p1, const T* p2) const {
    return p1 == p2;
  }
  bool operator()(const T* p1, const RefCountedPtr<T>& p2) const {
    return p2 == p1;
  }
  bool operator()(const T* p1, const WeakRefCountedPtr<T>& p2) const {
    return p2 == p1;
  }
};

template <typename T>
struct WeakRefCountedPtrHash {
  using is_transparent = void;
  size_t operator()(const WeakRefCountedPtr<T>& p) const {
    return absl::Hash<WeakRefCountedPtr<T>>{}(p);
  }
  size_t operator()(T* p) const { return absl::Hash<T*>{}(p); }
  size_t operator()(const T* p) const { return absl::Hash<const T*>{}(p); }
};
template <typename T>
struct WeakRefCountedPtrEq {
  using is_transparent = void;
  bool operator()(const WeakRefCountedPtr<T>& p1,
                  const WeakRefCountedPtr<T>& p2) const {
    return p1 == p2;
  }
  bool operator()(const WeakRefCountedPtr<T>& p1, const T* p2) const {
    return p1 == p2;
  }
  bool operator()(const T* p1, const WeakRefCountedPtr<T>& p2) const {
    return p2 == p1;
  }
};

}

#endif
