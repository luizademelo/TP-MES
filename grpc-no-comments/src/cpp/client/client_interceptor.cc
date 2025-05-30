
// Copyright 2018 gRPC authors.

#include <grpcpp/support/client_interceptor.h>

#include "src/core/util/crash.h"

namespace grpc {

namespace internal {
experimental::ClientInterceptorFactoryInterface*
    g_global_client_interceptor_factory = nullptr;

}

namespace experimental {
void RegisterGlobalClientInterceptorFactory(
    ClientInterceptorFactoryInterface* factory) {
  if (internal::g_global_client_interceptor_factory != nullptr) {
    grpc_core::Crash(
        "It is illegal to call RegisterGlobalClientInterceptorFactory "
        "multiple times.");
  }
  internal::g_global_client_interceptor_factory = factory;
}

void TestOnlyResetGlobalClientInterceptorFactory() {
  internal::g_global_client_interceptor_factory = nullptr;
}
}
}
