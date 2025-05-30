// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_CONTEXT_H
#define GRPC_SRC_CORE_LIB_PROMISE_CONTEXT_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "src/core/util/down_cast.h"

namespace grpc_core {

template <typename T>
struct ContextType;

template <typename Derived>
struct ContextSubclass;

namespace promise_detail {

template <typename T, typename = void>
class Context;

template <typename T>
class ThreadLocalContext : public ContextType<T> {
 public:
  explicit ThreadLocalContext(T* p) : old_(current_) { current_ = p; }
  ~ThreadLocalContext() { current_ = old_; }
  ThreadLocalContext(const ThreadLocalContext&) = delete;
  ThreadLocalContext& operator=(const ThreadLocalContext&) = delete;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T* get() { return current_; }

 private:
  T* const old_;
  static thread_local T* current_;
};

template <typename T>
thread_local T* ThreadLocalContext<T>::current_;

template <typename T>
class Context<T, absl::void_t<decltype(ContextType<T>())>>
    : public ThreadLocalContext<T> {
  using ThreadLocalContext<T>::ThreadLocalContext;
};

template <typename T>
class Context<T, absl::void_t<typename ContextSubclass<T>::Base>>
    : public Context<typename ContextSubclass<T>::Base> {
 public:
  using Context<typename ContextSubclass<T>::Base>::Context;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T* get() {
    return DownCast<T*>(Context<typename ContextSubclass<T>::Base>::get());
  }
};

template <typename T, typename F>
class WithContext {
 public:
  WithContext(F f, T* context) : context_(context), f_(std::move(f)) {}

  decltype(std::declval<F>()()) operator()() {
    Context<T> ctx(context_);
    return f_();
  }

 private:
  T* context_;
  F f_;
};

}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool HasContext() {
  return promise_detail::Context<T>::get() != nullptr;
}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline T* GetContext() {
  auto* p = promise_detail::Context<T>::get();
  DCHECK_NE(p, nullptr);
  return p;
}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline T* MaybeGetContext() {
  return promise_detail::Context<T>::get();
}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void SetContext(T* p) {
  promise_detail::Context<T>::set(p);
}

template <typename T, typename F>
promise_detail::WithContext<T, F> WithContext(F f, T* context) {
  return promise_detail::WithContext<T, F>(std::move(f), context);
}

}

#endif
