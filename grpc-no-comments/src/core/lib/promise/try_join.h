// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_TRY_JOIN_H
#define GRPC_SRC_CORE_LIB_PROMISE_TRY_JOIN_H

#include <grpc/support/port_platform.h>

#include <tuple>
#include <variant>

#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/promise/detail/join_state.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/status_flag.h"

namespace grpc_core {

namespace promise_detail {

template <typename T>
T IntoResult(absl::StatusOr<T>* status) {
  return std::move(**status);
}

inline Empty IntoResult(absl::Status*) { return Empty{}; }

template <template <typename> class Result>
struct TryJoinTraits {
  template <typename T>
  using ResultType = Result<absl::remove_reference_t<T>>;
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(
      const absl::StatusOr<T>& x) {
    return x.ok();
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(const absl::Status& x) {
    return x.ok();
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(StatusFlag x) {
    return x.ok();
  }
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static bool IsOk(
      const ValueOrFailure<T>& x) {
    return x.ok();
  }
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T Unwrapped(absl::StatusOr<T> x) {
    return std::move(*x);
  }
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T Unwrapped(ValueOrFailure<T> x) {
    return std::move(*x);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Empty Unwrapped(absl::Status) {
    return Empty{};
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Empty Unwrapped(StatusFlag) {
    return Empty{};
  }
  template <typename R, typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R EarlyReturn(
      absl::StatusOr<T> x) {
    return x.status();
  }
  template <typename R>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R EarlyReturn(absl::Status x) {
    return FailureStatusCast<R>(std::move(x));
  }
  template <typename R>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R EarlyReturn(StatusFlag x) {
    return FailureStatusCast<R>(x);
  }
  template <typename R, typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static R EarlyReturn(
      const ValueOrFailure<T>& x) {
    CHECK(!x.ok());
    return FailureStatusCast<R>(Failure{});
  }
  template <typename... A>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static auto FinalReturn(A&&... a) {
    return Result<std::tuple<A...>>(std::tuple(std::forward<A>(a)...));
  }
};

template <template <typename> class R, typename... Promises>
class TryJoin {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit TryJoin(Promises... promises)
      : state_(std::move(promises)...) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION auto operator()() {
    return state_.PollOnce();
  }

 private:
  JoinState<TryJoinTraits<R>, Promises...> state_;
};

template <template <typename> class R>
struct WrapInStatusOrTuple {
  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION R<std::tuple<T>> operator()(R<T> x) {
    if (!x.ok()) return x.status();
    return std::tuple(std::move(*x));
  }
};

}

template <template <typename> class R, typename... Promises>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline promise_detail::TryJoin<R,
                                                                    Promises...>
TryJoin(Promises... promises) {
  return promise_detail::TryJoin<R, Promises...>(std::move(promises)...);
}

template <template <typename> class R, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto TryJoin(F promise) {
  return Map(promise, promise_detail::WrapInStatusOrTuple<R>{});
}

}

#endif
