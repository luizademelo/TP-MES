// Copyright 2024 gRPC authors.

#include <grpcpp/support/global_callback_hook.h>

#include <memory>

#include "absl/base/no_destructor.h"
#include "absl/log/check.h"

namespace grpc {

static absl::NoDestructor<std::shared_ptr<GlobalCallbackHook>> g_callback_hook(
    std::make_shared<DefaultGlobalCallbackHook>());

std::shared_ptr<GlobalCallbackHook> GetGlobalCallbackHook() {
  return *g_callback_hook;
}

void SetGlobalCallbackHook(GlobalCallbackHook* hook) {
  CHECK(hook != nullptr);
  CHECK(hook != (*g_callback_hook).get());
  *g_callback_hook = std::shared_ptr<GlobalCallbackHook>(hook);
}
}
