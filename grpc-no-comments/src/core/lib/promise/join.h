// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_JOIN_H
#define GRPC_SRC_CORE_LIB_PROMISE_JOIN_H

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <tuple>

#include "absl/meta/type_traits.h"
#include "src/core/lib/promise/detail/join_state.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/map.h"

namespace grpc_core {
namespace promise_detail {

struct JoinTraits {
  template <typename T>
  using ResultType = absl::remove_reference_t<T>;
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(const T&) {
    return true;
  }
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T Unwrapped(T x) {
    return x;
  }
  template <typename R, typename T>
  static R EarlyReturn(T) {
    abort();
  }
  template <typename... A>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static std::tuple<A...> FinalReturn(
      A... a) {
    return std::tuple(std::move(a)...);
  }
};

template <typename... Promises>
class Join {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Join(Promises... promises)
      : state_(std::move(promises)...) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION auto operator()() {
    return state_.PollOnce();
  }

 private:
  JoinState<JoinTraits, Promises...> state_;
};

struct WrapInTuple {
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION std::tuple<T> operator()(T x) {
    return std::tuple(std::move(x));
  }
};

}

template <typename... Promise>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline promise_detail::Join<Promise...>
Join(Promise... promises) {
  return promise_detail::Join<Promise...>(std::move(promises)...);
}

template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto Join(F promise) {
  return Map(std::move(promise), promise_detail::WrapInTuple{});
}

template <typename Iter, typename FactoryFn>
inline auto JoinIter(Iter begin, Iter end, FactoryFn factory_fn) {
  using Factory =
      promise_detail::RepeatedPromiseFactory<decltype(*begin), FactoryFn>;
  Factory factory(std::move(factory_fn));
  using Promise = typename Factory::Promise;
  using Result = typename Promise::Result;
  using State = std::variant<Promise, Result>;
  std::vector<State> state;
  for (Iter it = begin; it != end; ++it) {
    state.emplace_back(factory.Make(*it));
  }
  return [state = std::move(state)]() mutable -> Poll<std::vector<Result>> {
    bool still_working = false;
    for (auto& s : state) {
      if (auto* promise = std::get_if<Promise>(&s)) {
        auto p = (*promise)();
        if (auto* r = p.value_if_ready()) {
          s.template emplace<Result>(std::move(*r));
        } else {
          still_working = true;
        }
      }
    }
    if (!still_working) {
      std::vector<Result> output;
      for (auto& s : state) {
        output.emplace_back(std::move(std::get<Result>(s)));
      }
      return output;
    }
    return Pending{};
  };
}

}

#endif
