// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_PROMISE_H
#define GRPC_SRC_CORE_LIB_PROMISE_PROMISE_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <type_traits>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/function_signature.h"
#include "src/core/util/json/json.h"

namespace grpc_core {

template <typename T>
using Promise = absl::AnyInvocable<Poll<T>()>;

template <typename Promise>
auto NowOrNever(Promise promise)
    -> std::optional<typename promise_detail::PromiseLike<Promise>::Result> {
  auto r = promise_detail::PromiseLike<Promise>(std::move(promise))();
  if (auto* p = r.value_if_ready()) {
    return std::move(*p);
  }
  return {};
}

template <typename T>
struct Never {
  Poll<T> operator()() { return Pending(); }
};

namespace promise_detail {

template <typename T>
class Immediate {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Immediate(T value)
      : value_(std::move(value)) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<T> operator()() {
    return std::move(value_);
  }

 private:
  T value_;
};
}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline promise_detail::Immediate<T>
Immediate(T value) {
  return promise_detail::Immediate<T>(std::move(value));
}

struct ImmediateOkStatus {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<absl::Status> operator()() {
    return absl::OkStatus();
  }
};

// NOTE: there are tests in promise_test.cc that are commented out because they

template <typename T, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto AssertResultType(F f) ->
    typename std::enable_if<std::is_same<decltype(f()), Poll<T>>::value,
                            F>::type {
  return f;
}

template <typename Promise>
using PromiseResult = typename PollTraits<
    typename promise_detail::PromiseLike<Promise>::Result>::Type;

}

#endif
