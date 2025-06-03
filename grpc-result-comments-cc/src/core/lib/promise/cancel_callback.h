Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_CANCEL_CALLBACK_H
#define GRPC_SRC_CORE_LIB_PROMISE_CANCEL_CALLBACK_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/resource_quota/arena.h"

namespace grpc_core {

// Internal namespace for cancel callback implementation details
namespace cancel_callback_detail {

// Handler class manages the execution of a cancel callback function
// The callback is executed when the handler is destroyed unless Done() was called
template <typename Fn>
class Handler {
 public:
  // Construct handler with the given cancel function
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Handler(Fn fn)
      : fn_(std::move(fn)) {}
  
  // Delete copy constructor/assignment to ensure single ownership of the callback
  Handler(const Handler&) = delete;
  Handler& operator=(const Handler&) = delete;
  
  // Destructor - executes the cancel function if not marked as done
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Handler() {
    if (!done_) {
      promise_detail::Context<Arena> ctx(arena_.get());
      fn_();
    }
  }
  
  // Move constructor - transfers ownership of the callback
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Handler(Handler&& other) noexcept
      : fn_(std::move(other.fn_)), done_(other.done_) {
    other.done_ = true;  // Ensure callback won't execute in moved-from object
  }
  
  // Move assignment - transfers ownership of the callback
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Handler& operator=(
      Handler&& other) noexcept {
    fn_ = std::move(other.fn_);
    done_ = other.done_;
    other.done_ = true;  // Ensure callback won't execute in moved-from object
  }

  // Mark the handler as done, preventing cancel callback execution
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Done() { done_ = true; }

 private:
  Fn fn_;  // The cancel callback function to execute

  // Arena reference for memory management
  RefCountedPtr<Arena> arena_ =
      HasContext<Arena>() ? GetContext<Arena>()->Ref() : nullptr;
  bool done_ = false;  // Flag indicating whether callback should be skipped
};

}  // namespace cancel_callback_detail

// Creates a promise that will execute cancel_fn if the promise is destroyed before completion
// The cancel_fn will not be executed if the promise completes successfully
template <typename MainFn, typename CancelFn>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto OnCancel(MainFn main_fn,
                                                          CancelFn cancel_fn) {
  return [on_cancel =
              cancel_callback_detail::Handler<CancelFn>(std::move(cancel_fn)),
          main_fn = promise_detail::PromiseLike<MainFn>(
              std::move(main_fn))]() mutable {
    auto r = main_fn();
    if (r.ready()) {
      on_cancel.Done();  // Mark as done if promise completes
    }
    return r;
  };
}

// Creates a factory that will produce promises with cancel callbacks
// The cancel_fn will always be executed after the promise runs, regardless of completion
template <typename MainFn, typename CancelFn>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto OnCancelFactory(
    MainFn main_fn, CancelFn cancel_fn) {
  return [on_cancel =
              cancel_callback_detail::Handler<CancelFn>(std::move(cancel_fn)),
          main_fn = std::move(main_fn)]() mutable {
    auto r = main_fn();
    on_cancel.Done();  // Always mark as done after execution
    return r;
  };
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_CANCEL_CALLBACK_H
```

The comments explain:
1. The overall purpose of the file (cancel callback functionality)
2. The internal Handler class that manages cancel callback execution
3. The difference between OnCancel and OnCancelFactory
4. The move semantics and ownership transfer
5. The memory management with Arena
6. The control flow and conditions for callback execution

The comments are placed to help future developers understand:
- Why certain design decisions were made
- How the code should be used
- When and why callbacks will be executed
- The thread safety implications (through the use of Arena)
- The difference between the two main functions exposed by the API