// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_ALL_OK_H
#define GRPC_SRC_CORE_LIB_PROMISE_ALL_OK_H

#include <grpc/support/port_platform.h>

#include <tuple>
#include <variant>

#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/promise/detail/join_state.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/status_flag.h"

namespace grpc_core {

namespace promise_detail {

template <typename Result>
struct AllOkTraits {
  template <typename T>
  using ResultType = Result;
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(const T& x) {
    return IsStatusOk(x);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Empty Unwrapped(StatusFlag) {
    return Empty{};
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Empty Unwrapped(absl::Status) {
    return Empty{};
  }
  template <typename R, typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R EarlyReturn(T&& x) {
    return StatusCast<R>(std::forward<T>(x));
  }
  template <typename... A>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Result FinalReturn(A&&...) {
    return Result{};
  }
};

template <typename Result, typename... Promises>
class AllOk {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit AllOk(Promises... promises)
      : state_(std::move(promises)...) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION auto operator()() {
    return state_.PollOnce();
  }

 private:
  JoinState<AllOkTraits<Result>, Promises...> state_;
};

}

template <typename Result, typename... Promises>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto AllOk(Promises... promises) {
  return promise_detail::AllOk<Result, Promises...>(std::move(promises)...);
}

template <typename Result, typename Iter, typename FactoryFn>
inline auto AllOkIter(Iter begin, Iter end, FactoryFn factory_fn) {
  using Factory =
      promise_detail::RepeatedPromiseFactory<decltype(*begin), FactoryFn>;
  Factory factory(std::move(factory_fn));
  using Promise = typename Factory::Promise;
  std::vector<Promise> promises;
  std::vector<bool> done;
  for (auto it = begin; it != end; ++it) {
    promises.emplace_back(factory.Make(*it));
    done.push_back(false);
  }
  return [promises = std::move(promises),
          done = std::move(done)]() mutable -> Poll<Result> {
    using Traits = promise_detail::AllOkTraits<Result>;
    bool still_working = false;
    for (size_t i = 0; i < promises.size(); ++i) {
      if (done[i]) continue;
      auto p = promises[i]();
      if (auto* r = p.value_if_ready()) {
        if (!Traits::IsOk(*r)) {
          return Traits::template EarlyReturn<Result>(std::move(*r));
        }
        done[i] = true;
      } else {
        still_working = true;
      }
    }
    if (still_working) return Pending{};
    return Traits::FinalReturn();
  };
}

}

#endif
