// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_CANCEL_CALLBACK_H
#define GRPC_SRC_CORE_LIB_PROMISE_CANCEL_CALLBACK_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/resource_quota/arena.h"

namespace grpc_core {

namespace cancel_callback_detail {

template <typename Fn>
class Handler {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Handler(Fn fn)
      : fn_(std::move(fn)) {}
  Handler(const Handler&) = delete;
  Handler& operator=(const Handler&) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Handler() {
    if (!done_) {
      promise_detail::Context<Arena> ctx(arena_.get());
      fn_();
    }
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Handler(Handler&& other) noexcept
      : fn_(std::move(other.fn_)), done_(other.done_) {
    other.done_ = true;
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Handler& operator=(
      Handler&& other) noexcept {
    fn_ = std::move(other.fn_);
    done_ = other.done_;
    other.done_ = true;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Done() { done_ = true; }

 private:
  Fn fn_;

  RefCountedPtr<Arena> arena_ =
      HasContext<Arena>() ? GetContext<Arena>()->Ref() : nullptr;
  bool done_ = false;
};

}

template <typename MainFn, typename CancelFn>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto OnCancel(MainFn main_fn,
                                                          CancelFn cancel_fn) {
  return [on_cancel =
              cancel_callback_detail::Handler<CancelFn>(std::move(cancel_fn)),
          main_fn = promise_detail::PromiseLike<MainFn>(
              std::move(main_fn))]() mutable {
    auto r = main_fn();
    if (r.ready()) {
      on_cancel.Done();
    }
    return r;
  };
}

template <typename MainFn, typename CancelFn>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline auto OnCancelFactory(
    MainFn main_fn, CancelFn cancel_fn) {
  return [on_cancel =
              cancel_callback_detail::Handler<CancelFn>(std::move(cancel_fn)),
          main_fn = std::move(main_fn)]() mutable {
    auto r = main_fn();
    on_cancel.Done();
    return r;
  };
};

}

#endif
