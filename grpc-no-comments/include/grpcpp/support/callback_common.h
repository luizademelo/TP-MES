
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_SUPPORT_CALLBACK_COMMON_H
#define GRPCPP_SUPPORT_CALLBACK_COMMON_H

#include <grpc/grpc.h>
#include <grpc/impl/grpc_types.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/global_callback_hook.h>
#include <grpcpp/support/status.h>

#include <functional>

#include "absl/log/absl_check.h"

namespace grpc {
namespace internal {

template <class Func, class... Args>
void CatchingCallback(Func&& func, Args&&... args) {
#if GRPC_ALLOW_EXCEPTIONS
  try {
    func(std::forward<Args>(args)...);
  } catch (...) {

  }
#else
  func(std::forward<Args>(args)...);
#endif
}

template <class Reactor, class Func, class... Args>
Reactor* CatchingReactorGetter(Func&& func, Args&&... args) {
#if GRPC_ALLOW_EXCEPTIONS
  try {
    return func(std::forward<Args>(args)...);
  } catch (...) {

    return nullptr;
  }
#else
  return func(std::forward<Args>(args)...);
#endif
}

class CallbackWithStatusTag : public grpc_completion_queue_functor {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(CallbackWithStatusTag));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  CallbackWithStatusTag(grpc_call* call, std::function<void(Status)> f,
                        CompletionQueueTag* ops)
      : call_(call), func_(std::move(f)), ops_(ops) {
    grpc_call_ref(call);
    functor_run = &CallbackWithStatusTag::StaticRun;

    inlineable = false;
  }
  ~CallbackWithStatusTag() {}
  Status* status_ptr() { return &status_; }

  void force_run(Status s) {
    status_ = std::move(s);
    Run(true);
  }

 private:
  grpc_call* call_;
  std::function<void(Status)> func_;
  CompletionQueueTag* ops_;
  Status status_;

  static void StaticRun(grpc_completion_queue_functor* cb, int ok) {
    static_cast<CallbackWithStatusTag*>(cb)->Run(static_cast<bool>(ok));
  }
  void Run(bool ok) {
    void* ignored = ops_;

    if (!ops_->FinalizeResult(&ignored, &ok)) {

      return;
    }
    ABSL_CHECK(ignored == ops_);

    auto func = std::move(func_);
    auto status = std::move(status_);
    func_ = nullptr;
    status_ = Status();
    GetGlobalCallbackHook()->RunCallback(
        call_, [func = std::move(func), status = std::move(status)]() {
#if GRPC_ALLOW_EXCEPTIONS
          try {
            func(status);
          } catch (...) {

          }
#else
  func(status);
#endif
        });
    grpc_call_unref(call_);
  }
};

class CallbackWithSuccessTag : public grpc_completion_queue_functor {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(CallbackWithSuccessTag));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  CallbackWithSuccessTag() : call_(nullptr) {}

  CallbackWithSuccessTag(const CallbackWithSuccessTag&) = delete;
  CallbackWithSuccessTag& operator=(const CallbackWithSuccessTag&) = delete;

  ~CallbackWithSuccessTag() { Clear(); }

  void Set(grpc_call* call, std::function<void(bool)> f,
           CompletionQueueTag* ops, bool can_inline) {
    ABSL_CHECK_EQ(call_, nullptr);
    grpc_call_ref(call);
    call_ = call;
    func_ = std::move(f);
    ops_ = ops;
    functor_run = &CallbackWithSuccessTag::StaticRun;
    inlineable = can_inline;
  }

  void Clear() {
    if (call_ != nullptr) {
      grpc_call* call = call_;
      call_ = nullptr;
      func_ = nullptr;
      grpc_call_unref(call);
    }
  }

  CompletionQueueTag* ops() { return ops_; }

  void force_run(bool ok) { Run(ok); }

  operator bool() const { return call_ != nullptr; }

 private:
  grpc_call* call_;
  std::function<void(bool)> func_;
  CompletionQueueTag* ops_;

  static void StaticRun(grpc_completion_queue_functor* cb, int ok) {
    static_cast<CallbackWithSuccessTag*>(cb)->Run(static_cast<bool>(ok));
  }
  void Run(bool ok) {
    void* ignored = ops_;

#ifndef NDEBUG
    auto* ops = ops_;
#endif
    bool do_callback = ops_->FinalizeResult(&ignored, &ok);
#ifndef NDEBUG
    ABSL_DCHECK(ignored == ops);
#endif

    if (do_callback) {
      GetGlobalCallbackHook()->RunCallback(call_, [this, ok]() {
#if GRPC_ALLOW_EXCEPTIONS
        try {
          func_(ok);
        } catch (...) {

        }
#else
  func_(ok);
#endif
      });
    }
  }
};

}
}

#endif
