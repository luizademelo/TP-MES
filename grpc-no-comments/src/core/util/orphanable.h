
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_ORPHANABLE_H
#define GRPC_SRC_CORE_UTIL_ORPHANABLE_H

#include <grpc/support/port_platform.h>

#include <cinttypes>
#include <memory>
#include <utility>

#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class Orphanable {
 public:

  virtual void Orphan() = 0;

  Orphanable(const Orphanable&) = delete;
  Orphanable& operator=(const Orphanable&) = delete;

 protected:
  Orphanable() {}
  virtual ~Orphanable() {}
};

class OrphanableDelete {
 public:
  template <typename T>
  void operator()(T* p) {
    p->Orphan();
  }
};

template <typename T, typename Deleter = OrphanableDelete>
using OrphanablePtr = std::unique_ptr<T, Deleter>;

template <typename T, typename... Args>
inline OrphanablePtr<T> MakeOrphanable(Args&&... args) {
  return OrphanablePtr<T>(new T(std::forward<Args>(args)...));
}

template <typename Child, typename UnrefBehavior = UnrefDelete>
class InternallyRefCounted : public Orphanable {
 public:

  InternallyRefCounted(const InternallyRefCounted&) = delete;
  InternallyRefCounted& operator=(const InternallyRefCounted&) = delete;

 protected:

  template <typename T>
  friend class RefCountedPtr;

  // Note: Tracing is a no-op on non-debug builds.
  explicit InternallyRefCounted(const char* trace = nullptr,
                                intptr_t initial_refcount = 1)
      : refs_(initial_refcount, trace) {}
  ~InternallyRefCounted() override = default;

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

  void Unref() {
    if (GPR_UNLIKELY(refs_.Unref())) {
      unref_behavior_(static_cast<Child*>(this));
    }
  }
  void Unref(const DebugLocation& location, const char* reason) {
    if (GPR_UNLIKELY(refs_.Unref(location, reason))) {
      unref_behavior_(static_cast<Child*>(this));
    }
  }

 private:
  void IncrementRefCount() { refs_.Ref(); }
  void IncrementRefCount(const DebugLocation& location, const char* reason) {
    refs_.Ref(location, reason);
  }

  RefCount refs_;
  GPR_NO_UNIQUE_ADDRESS UnrefBehavior unref_behavior_;
};

}

#endif
