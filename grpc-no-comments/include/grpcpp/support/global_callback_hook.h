// Copyright 2024 gRPC authors.

#ifndef GRPCPP_SUPPORT_GLOBAL_CALLBACK_HOOK_H
#define GRPCPP_SUPPORT_GLOBAL_CALLBACK_HOOK_H

#include "absl/functional/function_ref.h"

struct grpc_call;

namespace grpc {

class GlobalCallbackHook {
 public:
  virtual ~GlobalCallbackHook() = default;
  virtual void RunCallback(grpc_call* call,
                           absl::FunctionRef<void()> callback) = 0;

 protected:

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
};

class DefaultGlobalCallbackHook final : public GlobalCallbackHook {
 public:
  void RunCallback(grpc_call* call,
                   absl::FunctionRef<void()> callback) override {
    CatchingCallback(callback);
  }
};

std::shared_ptr<GlobalCallbackHook> GetGlobalCallbackHook();
void SetGlobalCallbackHook(GlobalCallbackHook* hook);
}

#endif
