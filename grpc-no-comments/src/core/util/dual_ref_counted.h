
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_DUAL_REF_COUNTED_H
#define GRPC_SRC_CORE_UTIL_DUAL_REF_COUNTED_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

template <typename Child, typename Impl = PolymorphicRefCount,
          typename UnrefBehavior = UnrefDelete>
class DualRefCounted : public Impl {
 public:

  DualRefCounted(const DualRefCounted&) = delete;
  DualRefCounted& operator=(const DualRefCounted&) = delete;

  GRPC_MUST_USE_RESULT RefCountedPtr<Child> Ref() {
    IncrementRefCount();
    return RefCountedPtr<Child>(static_cast<Child*>(this));
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<Child> Ref(const DebugLocation& location,
                                                const char* reason) {
    IncrementRefCount(location, reason);
    return RefCountedPtr<Child>(static_cast<Child*>(this));
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

  void Unref() {

    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(-1, 1), std::memory_order_acq_rel);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
#ifndef NDEBUG
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " unref " << strong_refs << " -> "
              << strong_refs - 1 << ", weak_ref " << weak_refs << " -> "
              << weak_refs + 1;
    }
    CHECK_GT(strong_refs, 0u);
#endif
    if (GPR_UNLIKELY(strong_refs == 1)) {
      Orphaned();
    }

    WeakUnref();
  }
  void Unref(const DebugLocation& location, const char* reason) {
    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(-1, 1), std::memory_order_acq_rel);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
#ifndef NDEBUG
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " " << location.file() << ":"
              << location.line() << " unref " << strong_refs << " -> "
              << strong_refs - 1 << ", weak_ref " << weak_refs << " -> "
              << weak_refs + 1 << ") " << reason;
    }
    CHECK_GT(strong_refs, 0u);
#else

    (void)location;
    (void)reason;
#endif
    if (GPR_UNLIKELY(strong_refs == 1)) {
      Orphaned();
    }

    WeakUnref(location, reason);
  }

  GRPC_MUST_USE_RESULT RefCountedPtr<Child> RefIfNonZero() {
    uint64_t prev_ref_pair = refs_.load(std::memory_order_acquire);
    do {
      const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
#ifndef NDEBUG
      const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
      if (trace_ != nullptr) {
        VLOG(2) << trace_ << ":" << this << " ref_if_non_zero " << strong_refs
                << " -> " << strong_refs + 1 << " (weak_refs=" << weak_refs
                << ")";
      }
#endif
      if (strong_refs == 0) return nullptr;
    } while (!refs_.compare_exchange_weak(
        prev_ref_pair, prev_ref_pair + MakeRefPair(1, 0),
        std::memory_order_acq_rel, std::memory_order_acquire));
    return RefCountedPtr<Child>(static_cast<Child*>(this));
  }
  GRPC_MUST_USE_RESULT RefCountedPtr<Child> RefIfNonZero(
      const DebugLocation& location, const char* reason) {
    uint64_t prev_ref_pair = refs_.load(std::memory_order_acquire);
    do {
      const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
#ifndef NDEBUG
      const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
      if (trace_ != nullptr) {
        VLOG(2) << trace_ << ":" << this << " " << location.file() << ":"
                << location.line() << " ref_if_non_zero " << strong_refs
                << " -> " << strong_refs + 1 << " (weak_refs=" << weak_refs
                << ") " << reason;
      }
#else

      (void)location;
      (void)reason;
#endif
      if (strong_refs == 0) return nullptr;
    } while (!refs_.compare_exchange_weak(
        prev_ref_pair, prev_ref_pair + MakeRefPair(1, 0),
        std::memory_order_acq_rel, std::memory_order_acquire));
    return RefCountedPtr<Child>(static_cast<Child*>(this));
  }

  GRPC_MUST_USE_RESULT WeakRefCountedPtr<Child> WeakRef() {
    IncrementWeakRefCount();
    return WeakRefCountedPtr<Child>(static_cast<Child*>(this));
  }
  GRPC_MUST_USE_RESULT WeakRefCountedPtr<Child> WeakRef(
      const DebugLocation& location, const char* reason) {
    IncrementWeakRefCount(location, reason);
    return WeakRefCountedPtr<Child>(static_cast<Child*>(this));
  }

  template <
      typename Subclass,
      std::enable_if_t<std::is_base_of<Child, Subclass>::value, bool> = true>
  WeakRefCountedPtr<Subclass> WeakRefAsSubclass() {
    IncrementWeakRefCount();
    return WeakRefCountedPtr<Subclass>(
        DownCast<Subclass*>(static_cast<Child*>(this)));
  }
  template <
      typename Subclass,
      std::enable_if_t<std::is_base_of<Child, Subclass>::value, bool> = true>
  WeakRefCountedPtr<Subclass> WeakRefAsSubclass(const DebugLocation& location,
                                                const char* reason) {
    IncrementWeakRefCount(location, reason);
    return WeakRefCountedPtr<Subclass>(
        DownCast<Subclass*>(static_cast<Child*>(this)));
  }

  void WeakUnref() {
#ifndef NDEBUG

    const char* trace = trace_;
#endif
    const uint64_t prev_ref_pair =
        refs_.fetch_sub(MakeRefPair(0, 1), std::memory_order_acq_rel);
#ifndef NDEBUG
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    if (trace != nullptr) {
      VLOG(2) << trace << ":" << this << " weak_unref " << weak_refs << " -> "
              << weak_refs - 1 << " (refs=" << strong_refs << ")";
    }
    CHECK_GT(weak_refs, 0u);
#endif
    if (GPR_UNLIKELY(prev_ref_pair == MakeRefPair(0, 1))) {
      unref_behavior_(static_cast<Child*>(this));
    }
  }
  void WeakUnref(const DebugLocation& location, const char* reason) {
#ifndef NDEBUG

    const char* trace = trace_;
#endif
    const uint64_t prev_ref_pair =
        refs_.fetch_sub(MakeRefPair(0, 1), std::memory_order_acq_rel);
#ifndef NDEBUG
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    if (trace != nullptr) {
      VLOG(2) << trace << ":" << this << " " << location.file() << ":"
              << location.line() << " weak_unref " << weak_refs << " -> "
              << weak_refs - 1 << " (refs=" << strong_refs << ") " << reason;
    }
    CHECK_GT(weak_refs, 0u);
#else

    (void)location;
    (void)reason;
#endif
    if (GPR_UNLIKELY(prev_ref_pair == MakeRefPair(0, 1))) {
      unref_behavior_(static_cast<const Child*>(this));
    }
  }

  GRPC_MUST_USE_RESULT WeakRefCountedPtr<Child> WeakRefIfNonZero() {
    uint64_t prev_ref_pair = refs_.load(std::memory_order_acquire);
    do {
      const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
      const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
#ifndef NDEBUG
      if (trace_ != nullptr) {
        VLOG(2) << trace_ << ":" << this << " ref_if_non_zero " << strong_refs
                << " -> " << strong_refs + 1 << " (weak_refs=" << weak_refs
                << ")";
      }
#endif
      if (strong_refs == 0 && weak_refs == 0) return nullptr;
    } while (!refs_.compare_exchange_weak(
        prev_ref_pair, prev_ref_pair + MakeRefPair(0, 1),
        std::memory_order_acq_rel, std::memory_order_acquire));
    return WeakRefCountedPtr<Child>(static_cast<Child*>(this));
  }
  GRPC_MUST_USE_RESULT WeakRefCountedPtr<Child> WeakRefIfNonZero(
      const DebugLocation& location, const char* reason) {
    uint64_t prev_ref_pair = refs_.load(std::memory_order_acquire);
    do {
      const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
      const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
#ifndef NDEBUG
      if (trace_ != nullptr) {
        VLOG(2) << trace_ << ":" << this << " " << location.file() << ":"
                << location.line() << " ref_if_non_zero " << strong_refs
                << " -> " << strong_refs + 1 << " (weak_refs=" << weak_refs
                << ") " << reason;
      }
#else

      (void)location;
      (void)reason;
#endif
      if (strong_refs == 0 && weak_refs == 0) return nullptr;
    } while (!refs_.compare_exchange_weak(
        prev_ref_pair, prev_ref_pair + MakeRefPair(0, 1),
        std::memory_order_acq_rel, std::memory_order_acquire));
    return WeakRefCountedPtr<Child>(static_cast<Child*>(this));
  }

 protected:
  // Note: Tracing is a no-op in non-debug builds.
  explicit DualRefCounted(
      const char*
#ifndef NDEBUG

          trace
#endif
      = nullptr,
      int32_t initial_refcount = 1)
      :
#ifndef NDEBUG
        trace_(trace),
#endif
        refs_(MakeRefPair(initial_refcount, 0)) {
  }

  virtual void Orphaned() = 0;

  // Note: Depending on the Impl used, this dtor can be implicitly virtual.
  ~DualRefCounted() = default;

  void AssertStronglyOwned() const {
    DCHECK_NE(GetStrongRefs(refs_.load(std::memory_order_relaxed)), 0u);
  }

 private:

  template <typename T>
  friend class RefCountedPtr;

  template <typename T>
  friend class WeakRefCountedPtr;

  static uint64_t MakeRefPair(uint32_t strong, uint32_t weak) {
    return (static_cast<uint64_t>(strong) << 32) + static_cast<int64_t>(weak);
  }
  static uint32_t GetStrongRefs(uint64_t ref_pair) {
    return static_cast<uint32_t>(ref_pair >> 32);
  }
  static uint32_t GetWeakRefs(uint64_t ref_pair) {
    return static_cast<uint32_t>(ref_pair & 0xffffffffu);
  }

  void IncrementRefCount() {
#ifndef NDEBUG
    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(1, 0), std::memory_order_relaxed);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    CHECK_NE(strong_refs, 0u);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " ref " << strong_refs << " -> "
              << strong_refs + 1 << "; (weak_refs=" << weak_refs << ")";
    }
#else
    refs_.fetch_add(MakeRefPair(1, 0), std::memory_order_relaxed);
#endif
  }
  void IncrementRefCount(const DebugLocation& location, const char* reason) {
#ifndef NDEBUG
    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(1, 0), std::memory_order_relaxed);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    CHECK_NE(strong_refs, 0u);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " " << location.file() << ":"
              << location.line() << " ref " << strong_refs << " -> "
              << strong_refs + 1 << " (weak_refs=" << weak_refs << ") "
              << reason;
    }
#else

    (void)location;
    (void)reason;
    refs_.fetch_add(MakeRefPair(1, 0), std::memory_order_relaxed);
#endif
  }

  void IncrementWeakRefCount() {
#ifndef NDEBUG
    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(0, 1), std::memory_order_relaxed);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " weak_ref " << weak_refs << " -> "
              << weak_refs + 1 << "; (refs=" << strong_refs << ")";
    }
    if (strong_refs == 0) CHECK_NE(weak_refs, 0u);
#else
    refs_.fetch_add(MakeRefPair(0, 1), std::memory_order_relaxed);
#endif
  }
  void IncrementWeakRefCount(const DebugLocation& location,
                             const char* reason) {
#ifndef NDEBUG
    const uint64_t prev_ref_pair =
        refs_.fetch_add(MakeRefPair(0, 1), std::memory_order_relaxed);
    const uint32_t strong_refs = GetStrongRefs(prev_ref_pair);
    const uint32_t weak_refs = GetWeakRefs(prev_ref_pair);
    if (trace_ != nullptr) {
      VLOG(2) << trace_ << ":" << this << " " << location.file() << ":"
              << location.line() << " weak_ref " << weak_refs << " -> "
              << weak_refs + 1 << " (refs=" << strong_refs << ") " << reason;
    }
    if (strong_refs == 0) CHECK_NE(weak_refs, 0u);
#else

    (void)location;
    (void)reason;
    refs_.fetch_add(MakeRefPair(0, 1), std::memory_order_relaxed);
#endif
  }

#ifndef NDEBUG
  const char* trace_;
#endif
  std::atomic<uint64_t> refs_{0};
  GPR_NO_UNIQUE_ADDRESS UnrefBehavior unref_behavior_;
};

}

#endif
