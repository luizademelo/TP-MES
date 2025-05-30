
// Copyright 2023 gRPC authors.

#include <grpcpp/support/client_interceptor.h>

#include "src/core/util/crash.h"

namespace grpc {
namespace internal {

experimental::ClientInterceptorFactoryInterface*
    g_global_client_stats_interceptor_factory = nullptr;

void RegisterGlobalClientStatsInterceptorFactory(
    grpc::experimental::ClientInterceptorFactoryInterface* factory) {
  if (internal::g_global_client_stats_interceptor_factory != nullptr) {
    grpc_core::Crash(
        "It is illegal to call RegisterGlobalClientStatsInterceptorFactory "
        "multiple times.");
  }
  internal::g_global_client_interceptor_factory = factory;
}

}
}
