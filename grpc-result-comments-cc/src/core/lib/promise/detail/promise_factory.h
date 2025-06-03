Here's the commented version of the code:

```c++
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

// Type trait to check if a callable F can be invoked with no arguments
// and returns void
template <typename T, typename Ignored = void>
struct IsVoidCallable {
  static constexpr bool value = false;
};
template <typename F>
struct IsVoidCallable<F, absl::void_t<decltype(std::declval<F>()())>> {
  static constexpr bool value = true;
};

// Helper to determine the return type of a callable F when invoked with Args...
template <typename T, typename Ignored = void>
struct ResultOfT;

// Specializations for different callable types (value, lvalue reference, const lvalue reference)
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

// Convenience alias for ResultOfT
template <typename T>
using ResultOf = typename ResultOfT<T>::T;

// Helper class to curry a function with one argument
template <typename F, typename Arg>
class Curried {
 public:
  // Constructors that forward the function and argument
  Curried(F&& f, Arg&& arg)
      : f_(std::forward<F>(f)), arg_(std::forward<Arg>(arg)) {}
  Curried(const F& f, Arg&& arg) : f_(f), arg_(std::forward<Arg>(arg)) {}

  // Determine and store the result type of F(Arg)
  using Result = decltype(std::declval<F>()(std::declval<Arg>()));
  
  // Invoke the curried function
  Result operator()() { return f_(std::move(arg_)); }

 private:
  GPR_NO_UNIQUE_ADDRESS F f_;  // Function to be called
  GPR_NO_UNIQUE_ADDRESS Arg arg_;  // Argument to pass to function
#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);  // Debug helper
#endif
};

// Tags to indicate promise execution semantics
struct RepeatableToken {};  // Promise can be executed multiple times
struct OnceToken {};        // Promise can only be executed once

// Implementation of promise factory for non-void callables with arguments
template <typename Token, typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION
    absl::enable_if_t<!IsVoidCallable<ResultOf<F(A)>>::value,
                      PromiseLike<Curried<RemoveCVRef<F>, A>>>
    PromiseFactoryImpl(Token, F&& f, A&& arg) {
  return Curried<RemoveCVRef<F>, A>(std::forward<F>(f), std::forward<A>(arg));
}

// Implementation for non-void callables with no arguments (once)
template <typename A, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    !IsVoidCallable<ResultOf<F()>>::value, PromiseLike<RemoveCVRef<F>>>
PromiseFactoryImpl(OnceToken, F f, A&&) {
  return PromiseLike<F>(std::move(f));
}

// Implementation for pollable non-void callables with no arguments (once)
template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::enable_if_t<
    !IsVoidCallable<ResultOf<F()>>::value &&
        PollTraits<ResultOf<F()>>::is_poll(),
    PromiseLike<RemoveCVRef<F>>>
PromiseFactoryImpl(OnceToken, F f) {
  return PromiseLike<F>(std::move(f));
}

// Implementation for non-pollable non-void callables with no arguments (once)
template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto PromiseFactoryImpl(
    std::enable_if_t<!IsVoidCallable<ResultOf<F()>>::value &&
                         !PollTraits<ResultOf<F()>>::is_poll() &&
                         !std::is_same_v<ResultOf<F()>, void>,
                     OnceToken>,
    F f) {
  // Capture the result immediately and return it when called
  auto f2 = [x = f()]() mutable { return std::move(x); };
  return PromiseLike<decltype(f2)>(std::move(f2));
}

// Implementation for void-returning non-pollable callables with no arguments (once)
template <typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto PromiseFactoryImpl(
    std::enable_if_t<!IsVoidCallable<ResultOf<F()>>::value &&
                         !PollTraits<ResultOf<F()>>::is_poll() &&
                         std::is_same_v<ResultOf<F()>, void>,
                     OnceToken>,
    F f) {
  // Execute immediately and return an empty result
  f();
  auto f2 = []() { return Empty{}; };
  return PromiseLike<decltype(f2)>(std::move(f2));
}

// Implementations for void callables (various forms)
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

// Factory for promises that can only be executed once (with arguments)
template <typename A, typename F>
class OncePromiseFactory {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;  // The callable to execute

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

// Specialization for void-argument once promises
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

// Factory for promises that can be executed multiple times (with arguments)
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

  // Const and non-const versions to support both const and non-const contexts
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make(Arg&& a) const {
    return PromiseFactoryImpl(RepeatableToken{}, f_, std::forward<Arg>(a));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make(Arg&& a) {
    return PromiseFactoryImpl(RepeatableToken{}, f_, std::forward<Arg>(a));
  }
};

// Specialization for void-argument repeatable promises
template <typename F>
class RepeatedPromiseFactory<void, F> {
 private:
  GPR_NO_UNIQUE_ADDRESS F f_;

 public:
  using Arg = void;
  using Promise = decltype(PromiseFactoryImpl(RepeatableToken{}, f_));

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit RepeatedPromiseFactory(F f)
      : f_(std::move(f)) {}

  // Const and non-const versions
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make() const {
    return PromiseFactoryImpl(RepeatableToken{}, f_);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Promise Make() {
    return PromiseFactoryImpl(RepeatableToken{}, f_);
  }
};

// Type trait to detect if a type is a repeated promise factory
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
```

The comments explain:
1. The purpose of each template and class
2. The different specializations and their use cases
3. The promise execution semantics (once vs repeatable)
4. The handling of different callable types (void vs non-void, pollable vs non-pollable)
5. The purpose of helper traits and type aliases
6. The difference between const and non-const contexts for repeated promises
7. Debugging aids like the ASAN canary

The comments are designed to help future developers understand the complex template metaprogramming involved in this promise factory implementation.