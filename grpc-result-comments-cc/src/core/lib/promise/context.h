Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_CONTEXT_H
#define GRPC_SRC_CORE_LIB_PROMISE_CONTEXT_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "src/core/util/down_cast.h"

namespace grpc_core {

// Forward declaration of ContextType template
template <typename T>
struct ContextType;

// Forward declaration of ContextSubclass template
template <typename Derived>
struct ContextSubclass;

namespace promise_detail {

// Primary template for Context (undefined)
template <typename T, typename = void>
class Context;

// ThreadLocalContext provides thread-local storage for context objects
// Inherits from ContextType<T> to enable type-specific context handling
template <typename T>
class ThreadLocalContext : public ContextType<T> {
 public:
  // Constructor saves current context and sets new one
  explicit ThreadLocalContext(T* p) : old_(current_) { current_ = p; }
  // Destructor restores previous context
  ~ThreadLocalContext() { current_ = old_; }
  // Disallow copying
  ThreadLocalContext(const ThreadLocalContext&) = delete;
  ThreadLocalContext& operator=(const ThreadLocalContext&) = delete;

  // Static method to get current thread's context
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T* get() { return current_; }

 private:
  T* const old_;  // Previous context to restore on destruction
  static thread_local T* current_;  // Thread-local storage for current context
};

// Definition of thread-local static member
template <typename T>
thread_local T* ThreadLocalContext<T>::current_;

// Specialization of Context for types with ContextType defined
template <typename T>
class Context<T, absl::void_t<decltype(ContextType<T>())>>
    : public ThreadLocalContext<T> {
  using ThreadLocalContext<T>::ThreadLocalContext;
};

// Specialization of Context for types derived from ContextSubclass
template <typename T>
class Context<T, absl::void_t<typename ContextSubclass<T>::Base>>
    : public Context<typename ContextSubclass<T>::Base> {
 public:
  using Context<typename ContextSubclass<T>::Base>::Context;
  // Gets context and downcasts to the derived type
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T* get() {
    return DownCast<T*>(Context<typename ContextSubclass<T>::Base>::get());
  }
};

// WithContext executes a function within a specific context
template <typename T, typename F>
class WithContext {
 public:
  // Constructor stores context and function to execute
  WithContext(F f, T* context) : context_(context), f_(std::move(f)) {}

  // Executes the stored function within the stored context
  decltype(std::declval<F>()()) operator()() {
    Context<T> ctx(context_);  // Sets the context
    return f_();  // Executes the function
  }

 private:
  T* context_;  // Context to set during execution
  F f_;         // Function to execute
};

}  // namespace promise_detail

// Checks if a context of type T exists in the current thread
template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool HasContext() {
  return promise_detail::Context<T>::get() != nullptr;
}

// Gets the current context of type T, asserts if not present
template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline T* GetContext() {
  auto* p = promise_detail::Context<T>::get();
  DCHECK_NE(p, nullptr);
  return p;
}

// Gets the current context of type T if present, returns nullptr otherwise
template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline T* MaybeGetContext() {
  return promise_detail::Context<T>::get();
}

// Sets the current context for type T
template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void SetContext(T* p) {
  promise_detail::Context<T>::set(p);
}

// Creates a WithContext object that will execute f within the specified context
template <typename T, typename F>
promise_detail::WithContext<T, F> WithContext(F f, T* context) {
  return promise_detail::WithContext<T, F>(std::move(f), context);
}

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_CONTEXT_H
```

The comments explain:
1. The overall purpose of the file (context management for promises)
2. The thread-local storage mechanism for contexts
3. The different template specializations and their purposes
4. The WithContext helper class for scoped context execution
5. The public API functions (HasContext, GetContext, MaybeGetContext, SetContext, WithContext)
6. Important implementation details like the use of thread_local and downcasting

The comments are designed to help future developers understand both the high-level concepts and implementation details of the context management system.