Here's the commented version of the code:

```c++
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

// A Promise is an invocable object that returns a Poll<T>.
// It represents an asynchronous computation that may complete immediately or later.
template <typename T>
using Promise = absl::AnyInvocable<Poll<T>()>;

// Executes a promise synchronously and returns its result if immediately available.
// If the promise isn't ready, returns an empty optional.
template <typename Promise>
auto NowOrNever(Promise promise)
    -> std::optional<typename promise_detail::PromiseLike<Promise>::Result> {
  auto r = promise_detail::PromiseLike<Promise>(std::move(promise))();
  if (auto* p = r.value_if_ready()) {
    return std::move(*p);
  }
  return {};
}

// A promise that never completes (always returns Pending).
template <typename T>
struct Never {
  Poll<T> operator()() { return Pending(); }
};

namespace promise_detail {

// A promise that completes immediately with a pre-determined value.
template <typename T>
class Immediate {
 public:
  // Constructs an Immediate promise with the given value.
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Immediate(T value)
      : value_(std::move(value)) {}

  // Returns the stored value immediately when polled.
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<T> operator()() {
    return std::move(value_);
  }

 private:
  T value_;
};
}  // namespace promise_detail

// Creates an Immediate promise that completes with the given value.
template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline promise_detail::Immediate<T>
Immediate(T value) {
  return promise_detail::Immediate<T>(std::move(value));
}

// A promise that immediately completes with an OkStatus.
struct ImmediateOkStatus {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<absl::Status> operator()() {
    return absl::OkStatus();
  }
};

// NOTE: there are tests in promise_test.cc that are commented out because they
// are not currently passing or are under development.

// Compile-time assertion that a function returns Poll<T>.
// If the assertion passes, returns the function unchanged.
template <typename T, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto AssertResultType(F f) ->
    typename std::enable_if<std::is_same<decltype(f()), Poll<T>>::value,
                            F>::type {
  return f;
}

// Extracts the result type from a promise.
template <typename Promise>
using PromiseResult = typename PollTraits<
    typename promise_detail::PromiseLike<Promise>::Result>::Type;

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_PROMISE_H
```

Key improvements in the comments:
1. Added clear descriptions of each template and class purpose
2. Explained the behavior of important functions like NowOrNever and Immediate
3. Documented the return types and behaviors
4. Added namespace closing comments
5. Explained the purpose of the AssertResultType template
6. Added a comment for the header guard closing
7. Clarified the NOTE about tests

The comments now provide a comprehensive understanding of the promise implementation while maintaining readability.