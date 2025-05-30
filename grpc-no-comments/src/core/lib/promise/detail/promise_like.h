// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_LIKE_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_LIKE_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/meta/type_traits.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/function_signature.h"
#include "src/core/util/json/json.h"

namespace grpc_core {

namespace promise_detail {
template <typename Promise, typename = void>
constexpr bool kHasToJsonMethod = false;

template <typename Promise>
constexpr bool kHasToJsonMethod<
    Promise, std::void_t<decltype(std::declval<Promise>().ToJson())>> = true;
}

template <typename Promise>
Json PromiseAsJson(const Promise& promise) {
  if constexpr (promise_detail::kHasToJsonMethod<Promise>) {
    return promise.ToJson();
  } else {
    return Json::FromString(std::string(TypeName<Promise>()));
  }
}

namespace promise_detail {

template <typename T>
struct PollWrapper {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Wrap(T&& x) {
    return Poll<T>(std::forward<T>(x));
  }
};

template <typename T>
struct PollWrapper<Poll<T>> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Wrap(Poll<T>&& x) {
    return std::forward<Poll<T>>(x);
  }
};

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto WrapInPoll(T&& x)
    -> decltype(PollWrapper<T>::Wrap(std::forward<T>(x))) {
  return PollWrapper<T>::Wrap(std::forward<T>(x));
}

template <typename T>
using RemoveCVRef = absl::remove_cv_t<absl::remove_reference_t<T>>;

template <typename F, typename SfinaeVoid = void>
class PromiseLike;

template <>
class PromiseLike<void>;

template <typename F>
class PromiseLike<
    F, absl::enable_if_t<!std::is_void<std::invoke_result_t<F>>::value>> {
 private:
  GPR_NO_UNIQUE_ADDRESS RemoveCVRef<F> f_;
  using OriginalResult = decltype(f_());
  using WrappedResult = decltype(WrapInPoll(std::declval<OriginalResult>()));

 public:

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION PromiseLike(F&& f)
      : f_(std::forward<F>(f)) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION WrappedResult operator()() {
    return WrapInPoll(f_());
  }
  Json ToJson() const { return PromiseAsJson(f_); }
  PromiseLike(const PromiseLike&) = default;
  PromiseLike& operator=(const PromiseLike&) = default;
  PromiseLike(PromiseLike&&) = default;
  PromiseLike& operator=(PromiseLike&&) = default;
  using Result = typename PollTraits<WrappedResult>::Type;
};

template <typename F>
class PromiseLike<
    F, absl::enable_if_t<std::is_void<std::invoke_result_t<F>>::value>> {
 private:
  GPR_NO_UNIQUE_ADDRESS RemoveCVRef<F> f_;

 public:

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION PromiseLike(F&& f)
      : f_(std::forward<F>(f)) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Empty> operator()() {
    f_();
    return Empty{};
  }
  Json ToJson() const { return PromiseAsJson(f_); }
  PromiseLike(const PromiseLike&) = default;
  PromiseLike& operator=(const PromiseLike&) = default;
  PromiseLike(PromiseLike&&) = default;
  PromiseLike& operator=(PromiseLike&&) = default;
  using Result = Empty;
};

}

}

#endif
