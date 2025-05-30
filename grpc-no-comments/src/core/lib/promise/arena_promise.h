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

namespace arena_promise_detail {

struct ArgType {
  alignas(std::max_align_t) char buffer[sizeof(void*)];
};

template <typename T>
T*& ArgAsPtr(ArgType* arg) {
  static_assert(sizeof(ArgType) >= sizeof(T**),
                "Must have ArgType of at least one pointer size");
  return *reinterpret_cast<T**>(arg);
}

template <typename T>
struct Vtable {

  Poll<T> (*poll_once)(ArgType* arg);

  void (*destroy)(ArgType* arg);
};

template <typename T>
struct VtableAndArg {
  const Vtable<T>* vtable;
  ArgType arg;
};

template <typename T>
struct Null {
  static const Vtable<T> vtable;

  static Poll<T> PollOnce(ArgType*) {
    abort();
    GPR_UNREACHABLE_CODE(return Pending{});
  }

  static void Destroy(ArgType*) {}
};

template <typename T>
const Vtable<T> Null<T>::vtable = {PollOnce, Destroy};

template <typename T, typename Callable>
struct AllocatedCallable {
  static const Vtable<T> vtable;

  static Poll<T> PollOnce(ArgType* arg) {
    return poll_cast<T>((*ArgAsPtr<Callable>(arg))());
  }

  static void Destroy(ArgType* arg) { Destruct(ArgAsPtr<Callable>(arg)); }
};

template <typename T, typename Callable>
const Vtable<T> AllocatedCallable<T, Callable>::vtable = {PollOnce, Destroy};

template <typename T, typename Callable>
struct Inlined {
  static const Vtable<T> vtable;

  static Poll<T> PollOnce(ArgType* arg) {
    return poll_cast<T>((*reinterpret_cast<Callable*>(arg))());
  }

  static void Destroy(ArgType* arg) {
    Destruct(reinterpret_cast<Callable*>(arg));
  }
};

template <typename T, typename Callable>
const Vtable<T> Inlined<T, Callable>::vtable = {PollOnce, Destroy};

template <typename T, typename Callable>
struct SharedCallable {
  static const Vtable<T> vtable;

  static Poll<T> PollOnce(ArgType* arg) {
    return (*reinterpret_cast<Callable*>(arg))();
  }
};

template <typename T, typename Callable>
const Vtable<T> SharedCallable<T, Callable>::vtable = {PollOnce,
                                                       Null<T>::Destroy};

template <typename T, typename Callable, typename Ignored = void>
struct ChooseImplForCallable;

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

template <typename T, typename Callable>
struct ChooseImplForCallable<
    T, Callable, absl::enable_if_t<std::is_empty<Callable>::value>> {
  static void Make(Callable&&, VtableAndArg<T>* out) {
    out->vtable = &SharedCallable<T, Callable>::vtable;
  }
};

template <typename T, typename Callable>
void MakeImplForCallable(Callable&& callable, VtableAndArg<T>* out) {
  ChooseImplForCallable<T, Callable>::Make(std::forward<Callable>(callable),
                                           out);
}

}

template <typename T>
class ArenaPromise {
 public:

  ArenaPromise() = default;

  template <typename Callable,
            typename Ignored =
                absl::enable_if_t<!std::is_same<Callable, ArenaPromise>::value>>

  ArenaPromise(Callable&& callable) {
    arena_promise_detail::MakeImplForCallable(std::forward<Callable>(callable),
                                              &vtable_and_arg_);
  }

  ArenaPromise(const ArenaPromise&) = delete;
  ArenaPromise& operator=(const ArenaPromise&) = delete;

  ArenaPromise(ArenaPromise&& other) noexcept
      : vtable_and_arg_(other.vtable_and_arg_) {
    other.vtable_and_arg_.vtable = &arena_promise_detail::Null<T>::vtable;
  }
  ArenaPromise& operator=(ArenaPromise&& other) noexcept {
    vtable_and_arg_.vtable->destroy(&vtable_and_arg_.arg);
    vtable_and_arg_ = other.vtable_and_arg_;
    other.vtable_and_arg_.vtable = &arena_promise_detail::Null<T>::vtable;
    return *this;
  }

  ~ArenaPromise() { vtable_and_arg_.vtable->destroy(&vtable_and_arg_.arg); }

  Poll<T> operator()() {
    return vtable_and_arg_.vtable->poll_once(&vtable_and_arg_.arg);
  }

  bool has_value() const {
    return vtable_and_arg_.vtable != &arena_promise_detail::Null<T>::vtable;
  }

 private:

  arena_promise_detail::VtableAndArg<T> vtable_and_arg_ = {
      &arena_promise_detail::Null<T>::vtable, {}};
};

}

#endif
