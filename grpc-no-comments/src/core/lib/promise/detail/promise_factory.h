// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_FACTORY_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_FACTORY_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "absl/meta/type_traits.h"
#include "src/core/lib/promise/detail/promise_like.h"

namespace grpc_core {
namespace promise_detail {

template <typename T, typename Ignored = void>
struct IsVoidCallable {
  static constexpr bool value = false;
};
template <typename F>
struct IsVoidCallable<F, absl::void_t<decltype(std::declval<F>()())>> {
  static constexpr bool value = true;
};

template <typename T, typename Ignored = void>
struct ResultOfT;

template <typename F, typename... Args>
struct ResultOfT<F(Args...),
                 absl::void_t<decltype(std::declval<RemoveCVRef<F>>()(
                     std::declval<Args>()...))>> {
  using T = decltype(std::declval<RemoveCVRef<F>>()(std::declval<Args>()...));
};

template <typename F, typename... Args>
struct ResultOfT<F(Args...)&,
                 absl::void_t<decltype(std::declval<RemoveCVRef<F>>()(
                     std::declval<Args>()...))>> {
  using T = decltype(std::declval<RemoveCVRef<F>>()(std::declval<Args>()...));
};

template <typename F, typename... Args>
struct ResultOfT<const F(Args...)&,
                 absl::void_t<decltype(std::declval<RemoveCVRef<F>>()(
                     std::declval<Args>()...))>> {
  using T = decltype(std::declval<RemoveCVRef<F>>()(std::declval<Args>()...));
};

template <typename T>
using ResultOf = typename ResultOfT<T>::T;

template <typename F, typename Arg>
class Curried {
 public:
  Curried(F&& f, Arg&& arg)
      : f_(std::forward<F>(f)), arg_(std::forward<Arg>(arg)) {}
  Curried(const F& f, Arg&& arg) : f_(f), arg_(std::forward<Arg>(arg)) {}
  using Result = decltype(std::declval<F>()(std::declval<Arg>()));
  Result operator()() { return f_(std::move(arg_)); }

 private:
  GPR_NO_UNIQUE_ADDRESS F f_;
  GPR_NO_UNIQUE_ADDRESS Arg arg_;
#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);
#endif
};

struct RepeatableToken {};
struct OnceToken {};

template <typename Token, typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
    absl::enable_if_t<!IsVoidCallable<ResultOf<F(A)>>::value,
                      PromiseLike<Curried<RemoveCVRef<F>, A>>>
    PromiseFactoryImpl(Token, F&& f, A&& arg) {
  return Curried<RemoveCVRef<F>, A>(std::forward<F>(f), std::forward<A>(arg));
}

template <typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    !IsVoidCallable<ResultOf<F()>>::value, PromiseLike<RemoveCVRef<F>>>
PromiseFactoryImpl(OnceToken, F f, A&&) {
  return PromiseLike<F>(std::move(f));
}

template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    !IsVoidCallable<ResultOf<F()>>::value &&
        PollTraits<ResultOf<F()>>::is_poll(),
    PromiseLike<RemoveCVRef<F>>>
PromiseFactoryImpl(OnceToken, F f) {
  return PromiseLike<F>(std::move(f));
}

template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto PromiseFactoryImpl(
    std::enable_if_t<!IsVoidCallable<ResultOf<F()>>::value &&
                         !PollTraits<ResultOf<F()>>::is_poll() &&
                         !std::is_same_v<ResultOf<F()>, void>,
                     OnceToken>,
    F f) {
  auto f2 = [x = f()]() mutable { return std::move(x); };
  return PromiseLike<decltype(f2)>(std::move(f2));
}
template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto PromiseFactoryImpl(
    std::enable_if_t<!IsVoidCallable<ResultOf<F()>>::value &&
                         !PollTraits<ResultOf<F()>>::is_poll() &&
                         std::is_same_v<ResultOf<F()>, void>,
                     OnceToken>,
    F f) {
  f();
  auto f2 = []() { return Empty{}; };
  return PromiseLike<decltype(f2)>(std::move(f2));
}

template <typename Token, typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    IsVoidCallable<ResultOf<F(A)>>::value,
    PromiseLike<decltype(std::declval<F>()(std::declval<A>()))>>
PromiseFactoryImpl(Token, F&& f, A&& arg) {
  return f(std::forward<A>(arg));
}

template <typename Token, typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    IsVoidCallable<ResultOf<F(A)>>::value,
    PromiseLike<decltype(std::declval<F>()(std::declval<A>()))>>
PromiseFactoryImpl(Token, F& f, A&& arg) {
  return f(std::forward<A>(arg));
}

template <typename Token, typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
    absl::enable_if_t<IsVoidCallable<ResultOf<F()>>::value,
                      PromiseLike<decltype(std::declval<F>()())>>
    PromiseFactoryImpl(Token, F&& f, A&&) {
  return f();
}

template <typename Token, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
    absl::enable_if_t<IsVoidCallable<ResultOf<F()>>::value,
                      PromiseLike<decltype(std::declval<F>()())>>
    PromiseFactoryImpl(Token, F&& f) {
  return f();
}

template <typename A, typename F>

class OncePromiseFactory {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;

 public:
  using Arg = A;
  using Promise = decltype(PromiseFactoryImpl(OnceToken{}, std::move(f_),
                                              std::declval<A>()));
  using UnderlyingFactory = F;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit OncePromiseFactory(F f)
      : f_(std::move(f)) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make(Arg&& a) {
    return PromiseFactoryImpl(OnceToken{}, std::move(f_), std::forward<Arg>(a));
  }
};

template <typename F>
class OncePromiseFactory<void, F> {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;

 public:
  using Arg = void;
  using Promise = decltype(PromiseFactoryImpl(OnceToken{}, std::move(f_)));
  using UnderlyingFactory = F;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit OncePromiseFactory(F f)
      : f_(std::move(f)) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make() {
    return PromiseFactoryImpl(OnceToken{}, std::move(f_));
  }
};

template <typename A, typename F>

class RepeatedPromiseFactory {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;

 public:
  using Arg = A;
  using Promise =
      decltype(PromiseFactoryImpl(RepeatableToken{}, f_, std::declval<A>()));

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit RepeatedPromiseFactory(F f)
      : f_(std::move(f)) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make(Arg&& a) const {
    return PromiseFactoryImpl(RepeatableToken{}, f_, std::forward<Arg>(a));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make(Arg&& a) {
    return PromiseFactoryImpl(RepeatableToken{}, f_, std::forward<Arg>(a));
  }
};

template <typename F>
class RepeatedPromiseFactory<void, F> {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;

 public:
  using Arg = void;
  using Promise = decltype(PromiseFactoryImpl(RepeatableToken{}, f_));

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit RepeatedPromiseFactory(F f)
      : f_(std::move(f)) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make() const {
    return PromiseFactoryImpl(RepeatableToken{}, f_);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make() {
    return PromiseFactoryImpl(RepeatableToken{}, f_);
  }
};

template <typename A, typename F, typename = void>
constexpr const bool kIsRepeatedPromiseFactory = false;

template <typename A, typename F>
constexpr const bool kIsRepeatedPromiseFactory<
    A, F,
    std::void_t<decltype(PromiseFactoryImpl(
        RepeatableToken{}, std::declval<F&&>(), std::declval<A>()))>> = true;

template <typename F>
constexpr const bool
    kIsRepeatedPromiseFactory<void, F,
                              std::void_t<decltype(PromiseFactoryImpl(
                                  RepeatableToken{}, std::declval<F&&>()))>> =
        true;

}
}

#endif
