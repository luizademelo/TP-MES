
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_REF_COUNTED_H
#define GRPC_SRC_CORE_UTIL_REF_COUNTED_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <cassert>
#include <cinttypes>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/atomic_utils.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class RefCount {
 public:
  using Value = intptr_t;

  RefCount() : RefCount(1) {}

  explicit RefCount(
      Value init,
      const char*
#ifndef NDEBUG

          trace
#endif
      = nullptr)
      :
#ifndef NDEBUG
        trace_(trace),
#endif
        value_(init) {
  }

  void Ref(Value n = 1) {
#ifndef NDEBUG
    const Value prior = value_.fetch_add(n, std::memory_order_relaxed);
    if (trace_ != nullptr) {
      LOG(INFO) << trace_ << ":" << this << " ref " << prior << " -> "
                << prior + n;
    }
#else
    value_.fetch_add(n, std::memory_order_relaxed);
#endif
  }
  void Ref(const DebugLocation& location, const char* reason, Value n = 1) {
#ifndef NDEBUG
    const Value prior = value_.fetch_add(n, std::memory_order_relaxed);
    if (trace_ != nullptr) {
      LOG(INFO) << trace_ << ":" << this << " " << location.file() << ":"
                << location.line() << " ref " << prior << " -> " << prior + n
                << " " << reason;
    }
#else

    (void)location;
    (void)reason;
    value_.fetch_add(n, std::memory_order_relaxed);
#endif
  }

  void RefNonZero() {
#ifndef NDEBUG
    const Value prior = value_.fetch_add(1, std::memory_order_relaxed);
    if (trace_ != nullptr) {
      LOG(INFO) << trace_ << ":" << this << " ref " << prior << " -> "
                << prior + 1;
    }
    assert(prior > 0);
#else
    value_.fetch_add(1, std::memory_order_relaxed);
#endif
  }
  void RefNonZero(const DebugLocation& location, const char* reason) {
#ifndef NDEBUG
    const Value prior = value_.fetch_add(1, std::memory_order_relaxed);
    if (trace_ != nullptr) {
      LOG(INFO) << trace_ << ":" << this << " " << location.file() << ":"
                << location.line() << " ref " << prior << " -> " << prior + 1
                << " " << reason;
    }
    assert(prior > 0);
#else

    (void)location;
    (void)reason;
    RefNonZero();
#endif
  }

  bool RefIfNonZero() {
#ifndef NDEBUG
    if (trace_ != nullptr) {
      const Value prior = get();
      LOG(INFO) << trace_ << ":" << this << " ref_if_non_zero " << prior
                << " -> " << prior + 1;
    }
#endif
    return IncrementIfNonzero(&value_);
  }
  bool RefIfNonZero(const DebugLocation& location, const char* reason) {
#ifndef NDEBUG
    if (trace_ != nullptr) {
      const Value prior = get();
      LOG(INFO) << trace_ << ":" << this << " " << location.file() << ":"
                << location.line() << " ref_if_non_zero " << prior << " -> "
                << prior + 1 << " " << reason;
    }
#endif

    (void)location;
    (void)reason;
    return IncrementIfNonzero(&value_);
  }

  bool Unref() {
#ifndef NDEBUG

    auto* trace = trace_;
#endif
    const Value prior = value_.fetch_sub(1, std::memory_order_acq_rel);
#ifndef NDEBUG
    if (trace != nullptr) {
      LOG(INFO) << trace << ":" << this << " unref " << prior << " -> "
                << prior - 1;
    }
    DCHECK_GT(prior, 0);
#endif
    return prior == 1;
  }
  bool Unref(const DebugLocation& location, const char* reason) {
#ifndef NDEBUG

    auto* trace = trace_;
#endif
    const Value prior = value_.fetch_sub(1, std::memory_order_acq_rel);
#ifndef NDEBUG
    if (trace != nullptr) {
      LOG(INFO) << trace << ":" << this << " " << location.file() << ":"
                << location.line() << " unref " << prior << " -> " << prior - 1
                << " " << reason;
    }
    DCHECK_GT(prior, 0);
#else

    (void)location;
    (void)reason;
#endif
    return prior == 1;
  }

 private:
  Value get() const { return value_.load(std::memory_order_relaxed); }

#ifndef NDEBUG
  const char* trace_;
#endif
  std::atomic<Value> value_{0};
};

class PolymorphicRefCount {
 public:
  virtual ~PolymorphicRefCount() = default;
};

class NonPolymorphicRefCount {
 public:
  ~NonPolymorphicRefCount() = default;
};

struct UnrefDelete {
  template <typename T>
  void operator()(T* p) const {
    delete p;
  }
};

struct UnrefNoDelete {
  template <typename T>
  void operator()(T* ) const {}
};

struct UnrefCallDtor {
  template <typename T>
  void operator()(T* p) const {
    p->~T();
  }
};

struct UnrefCallDestroy {
  template <typename T>
  void operator()(T* p) const {
    p->Destroy();
  }
};

template <typename Child, typename Impl = PolymorphicRefCount,
          typename UnrefBehavior = UnrefDelete>
class RefCounted : public Impl {
 public:
  using RefCountedChildType = Child;
  using RefCountedUnrefBehaviorType = UnrefBehavior;

  RefCounted(const RefCounted&) = delete;
  RefCounted& operator=(const RefCounted&) = delete;

  // Note: Depending on the Impl used, this dtor can be implicitly virtual.
  ~RefCounted() = default;

  GRPC_MUST_USE_RESULT RefCountedPtr<Child> Ref() {
    IncrementRefCount();
    return RefCountedPtr<Child>(static_cast<Child*>(this));
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<Child> Ref(const DebugLocation& location,
                                                const char* reason) {
    IncrementRefCount(location, reason);
    return RefCountedPtr<Child>(static_cast<Child*>(this));
  }

  GRPC_MUST_USE_RESULT RefCountedPtr<const Child> Ref() const {
    IncrementRefCount();
    return RefCountedPtr<const Child>(static_cast<const Child*>(this));
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<const Child> Ref(
      const DebugLocation& location, const char* reason) const {
    IncrementRefCount(location, reason);
    return RefCountedPtr<const Child>(static_cast<const Child*>(this));
  }

  template <
      typename Subclass,
      std::enable_if_t<std::is_base_of<Child, Subclass>::value, bool> = true>
  RefCountedPtr<Subclass> RefAsSubclass() {
    IncrementRefCount();
    return RefCountedPtr<Subclass>(
        DownCast<Subclass*>(static_cast<Child*>(this)));
  }
  template <
      typename Subclass,
      std::enable_if_t<std::is_base_of<Child, Subclass>::value, bool> = true>
  RefCountedPtr<Subclass> RefAsSubclass(const DebugLocation& location,
                                        const char* reason) {
    IncrementRefCount(location, reason);
    return RefCountedPtr<Subclass>(
        DownCast<Subclass*>(static_cast<Child*>(this)));
  }

  GRPC_MUST_USE_RESULT RefCountedPtr<Child> RefIfNonZero() {
    return RefCountedPtr<Child>(refs_.RefIfNonZero() ? static_cast<Child*>(this)
                                                     : nullptr);
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<Child> RefIfNonZero(
      const DebugLocation& location, const char* reason) {
    return RefCountedPtr<Child>(refs_.RefIfNonZero(location, reason)
                                    ? static_cast<Child*>(this)
                                    : nullptr);
  }

  GRPC_MUST_USE_RESULT RefCountedPtr<const Child> RefIfNonZero() const {
    return RefCountedPtr<const Child>(
        refs_.RefIfNonZero() ? static_cast<const Child*>(this) : nullptr);
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<const Child> RefIfNonZero(
      const DebugLocation& location, const char* reason) const {
    return RefCountedPtr<const Child>(refs_.RefIfNonZero(location, reason)
                                          ? static_cast<const Child*>(this)
                                          : nullptr);
  }

  void Unref() const {
    if (GPR_UNLIKELY(refs_.Unref())) {
      unref_behavior_(static_cast<const Child*>(this));
    }
  }
  void Unref(const DebugLocation& location, const char* reason) const {
    if (GPR_UNLIKELY(refs_.Unref(location, reason))) {
      unref_behavior_(static_cast<const Child*>(this));
    }
  }

 protected:
  // Note: Tracing is a no-op on non-debug builds.
  explicit RefCounted(const char* trace = nullptr,
                      intptr_t initial_refcount = 1)
      : refs_(initial_refcount, trace) {}

  // Note: Tracing is a no-op on non-debug builds.
  explicit RefCounted(UnrefBehavior b, const char* trace = nullptr,
                      intptr_t initial_refcount = 1)
      : refs_(initial_refcount, trace), unref_behavior_(b) {}

 private:

  template <typename T>
  friend class RefCountedPtr;

  void IncrementRefCount() const { refs_.Ref(); }
  void IncrementRefCount(const DebugLocation& location,
                         const char* reason) const {
    refs_.Ref(location, reason);
  }

  mutable RefCount refs_;
  GPR_NO_UNIQUE_ADDRESS UnrefBehavior unref_behavior_;
};

}

#endif
