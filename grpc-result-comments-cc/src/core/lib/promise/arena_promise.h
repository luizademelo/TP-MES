Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_ARENA_PROMISE_H
#define GRPC_SRC_CORE_LIB_PROMISE_ARENA_PROMISE_H

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "absl/meta/type_traits.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/util/construct_destruct.h"

namespace grpc_core {

// Internal implementation details for ArenaPromise
namespace arena_promise_detail {

// Storage for arguments passed to promise operations
// Aligned to maximum alignment to ensure proper alignment for any type
struct ArgType {
  alignas(std::max_align_t) char buffer[sizeof(void*)];
};

// Helper function to interpret ArgType as a pointer to T
template <typename T>
T*& ArgAsPtr(ArgType* arg) {
  static_assert(sizeof(ArgType) >= sizeof(T**),
                "Must have ArgType of at least one pointer size");
  return *reinterpret_cast<T**>(arg);
}

// Virtual function table for promise operations
template <typename T>
struct Vtable {
  // Function pointer for polling the promise once
  Poll<T> (*poll_once)(ArgType* arg);
  // Function pointer for destroying the promise
  void (*destroy)(ArgType* arg);
};

// Combined storage for vtable and argument
template <typename T>
struct VtableAndArg {
  const Vtable<T>* vtable;  // Pointer to the virtual function table
  ArgType arg;              // Storage for the promise argument
};

// Null implementation of Vtable for empty promises
template <typename T>
struct Null {
  static const Vtable<T> vtable;

  // Invalid poll operation for null promise (should never be called)
  static Poll<T> PollOnce(ArgType*) {
    abort();
    GPR_UNREACHABLE_CODE(return Pending{});
  }

  // No-op destroy operation for null promise
  static void Destroy(ArgType*) {}
};

// Initialize the null vtable
template <typename T>
const Vtable<T> Null<T>::vtable = {PollOnce, Destroy};

// Implementation for callables allocated on the arena
template <typename T, typename Callable>
struct AllocatedCallable {
  static const Vtable<T> vtable;

  // Poll the callable by dereferencing the pointer stored in arg
  static Poll<T> PollOnce(ArgType* arg) {
    return poll_cast<T>((*ArgAsPtr<Callable>(arg))());
  }

  // Destroy the callable by calling destructor on the pointer in arg
  static void Destroy(ArgType* arg) { Destruct(ArgAsPtr<Callable>(arg)); }
};

// Initialize the allocated callable vtable
template <typename T, typename Callable>
const Vtable<T> AllocatedCallable<T, Callable>::vtable = {PollOnce, Destroy};

// Implementation for callables small enough to be stored inline
template <typename T, typename Callable>
struct Inlined {
  static const Vtable<T> vtable;

  // Poll the callable by interpreting arg as the callable directly
  static Poll<T> PollOnce(ArgType* arg) {
    return poll_cast<T>((*reinterpret_cast<Callable*>(arg))());
  }

  // Destroy the callable by calling destructor on the inlined storage
  static void Destroy(ArgType* arg) {
    Destruct(reinterpret_cast<Callable*>(arg));
  }
};

// Initialize the inlined callable vtable
template <typename T, typename Callable>
const Vtable<T> Inlined<T, Callable>::vtable = {PollOnce, Destroy};

// Implementation for empty callables (no storage needed)
template <typename T, typename Callable>
struct SharedCallable {
  static const Vtable<T> vtable;

  // Poll the empty callable by interpreting arg as the callable directly
  static Poll<T> PollOnce(ArgType* arg) {
    return (*reinterpret_cast<Callable*>(arg))();
  }
};

// Initialize the shared callable vtable (uses Null's destroy as no destruction needed)
template <typename T, typename Callable>
const Vtable<T> SharedCallable<T, Callable>::vtable = {PollOnce,
                                                       Null<T>::Destroy};

// Metafunction to choose the appropriate implementation based on callable properties
template <typename T, typename Callable, typename Ignored = void>
struct ChooseImplForCallable;

// Specialization for large, non-empty callables (uses arena allocation)
template <typename T, typename Callable>
struct ChooseImplForCallable<
    T, Callable,
    absl::enable_if_t<!std::is_empty<Callable>::value &&
                      (sizeof(Callable) > sizeof(ArgType))>> {
  static void Make(Callable&& callable, VtableAndArg<T>* out) {
    out->vtable = &AllocatedCallable<T, Callable>::vtable;
    ArgAsPtr<Callable>(&out->arg) = GetContext<Arena>()->template New<Callable>(
        std::forward<Callable>(callable));
  }
};

// Specialization for small, non-empty callables (uses inlined storage)
template <typename T, typename Callable>
struct ChooseImplForCallable<
    T, Callable,
    absl::enable_if_t<!std::is_empty<Callable>::value &&
                      (sizeof(Callable) <= sizeof(ArgType))>> {
  static void Make(Callable&& callable, VtableAndArg<T>* out) {
    out->vtable = &Inlined<T, Callable>::vtable;
    Construct(reinterpret_cast<Callable*>(&out->arg),
              std::forward<Callable>(callable));
  }
};

// Specialization for empty callables (no storage needed)
template <typename T, typename Callable>
struct ChooseImplForCallable<
    T, Callable, absl::enable_if_t<std::is_empty<Callable>::value>> {
  static void Make(Callable&&, VtableAndArg<T>* out) {
    out->vtable = &SharedCallable<T, Callable>::vtable;
  }
};

// Helper function to create the appropriate implementation for a callable
template <typename T, typename Callable>
void MakeImplForCallable(Callable&& callable, VtableAndArg<T>* out) {
  ChooseImplForCallable<T, Callable>::Make(std::forward<Callable>(callable),
                                           out);
}

}  // namespace arena_promise_detail

// A promise implementation that uses arena allocation for storage
template <typename T>
class ArenaPromise {
 public:
  // Default constructor creates a null promise
  ArenaPromise() = default;

  // Constructor from any callable type (excluding ArenaPromise itself)
  template <typename Callable,
            typename Ignored =
                absl::enable_if_t<!std::is_same<Callable, ArenaPromise>::value>>
  ArenaPromise(Callable&& callable) {
    arena_promise_detail::MakeImplForCallable(std::forward<Callable>(callable),
                                              &vtable_and_arg_);
  }

  // Copy operations are deleted - promises are move-only
  ArenaPromise(const ArenaPromise&) = delete;
  ArenaPromise& operator=(const ArenaPromise&) = delete;

  // Move constructor - transfers ownership and nulls out the source
  ArenaPromise(ArenaPromise&& other) noexcept
      : vtable_and_arg_(other.vtable_and_arg_) {
    other.vtable_and_arg_.vtable = &arena_promise_detail::Null<T>::vtable;
  }

  // Move assignment - destroys current promise and transfers ownership
  ArenaPromise& operator=(ArenaPromise&& other) noexcept {
    vtable_and_arg_.vtable->destroy(&vtable_and_arg_.arg);
    vtable_and_arg_ = other.vtable_and_arg_;
    other.vtable_and_arg_.vtable = &arena_promise_detail::Null<T>::vtable;
    return *this;
  }

  // Destructor - destroys the contained promise
  ~ArenaPromise() { vtable_and_arg_.vtable->destroy(&vtable_and_arg_.arg); }

  // Poll the promise once
  Poll<T> operator()() {
    return vtable_and_arg_.vtable->poll_once(&vtable_and_arg_.arg);
  }

  // Check if the promise contains a value (is not null)
  bool has_value() const {
    return vtable_and_arg_.vtable != &arena_promise_detail::Null<T>::vtable;
  }

 private:
  // Storage for the promise implementation and its argument
  arena_promise_detail::VtableAndArg<T> vtable_and_arg_ = {
      &arena_promise_detail::Null<T>::vtable, {}};
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_ARENA_PROMISE_H
```