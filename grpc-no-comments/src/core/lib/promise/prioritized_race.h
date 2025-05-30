// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_PRIORITIZED_RACE_H
#define GRPC_SRC_CORE_LIB_PROMISE_PRIORITIZED_RACE_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/lib/promise/detail/promise_like.h"

namespace grpc_core {

template <typename A, typename B>
class TwoPartyPrioritizedRace {
 public:
  using Result = decltype(std::declval<A>()());

  explicit TwoPartyPrioritizedRace(A a, B b)
      : a_(std::move(a)), b_(std::move(b)) {}

  Result operator()() {

    auto p = a_();
    if (p.ready()) return p;

    auto q = b_();
    if (!q.ready()) return q;

    auto r = a_();
    if (r.ready()) {

      return r;
    }
    return q;
  }

 private:
  promise_detail::PromiseLike<A> a_;
  promise_detail::PromiseLike<B> b_;
};

template <typename... Promises>
class PrioritizedRace;

template <typename Promise, typename... Promises>
class PrioritizedRace<Promise, Promises...>
    : public TwoPartyPrioritizedRace<Promise, PrioritizedRace<Promises...>> {
 public:
  using Result = decltype(std::declval<Promise>()());
  explicit PrioritizedRace(Promise promise, Promises... promises)
      : TwoPartyPrioritizedRace<Promise, PrioritizedRace<Promises...>>(
            std::move(promise),
            PrioritizedRace<Promises...>(std::move(promises)...)) {}
};

template <typename Promise>
class PrioritizedRace<Promise> {
 public:
  using Result = decltype(std::declval<Promise>()());
  explicit PrioritizedRace(Promise promise) : promise_(std::move(promise)) {}
  Result operator()() { return promise_(); }

 private:
  Promise promise_;
};

template <typename... Promises>
PrioritizedRace(Promises...) -> PrioritizedRace<Promises...>;

}

#endif
