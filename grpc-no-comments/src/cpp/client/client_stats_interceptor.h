
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_CLIENT_CLIENT_STATS_INTERCEPTOR_H
#define GRPC_SRC_CPP_CLIENT_CLIENT_STATS_INTERCEPTOR_H

#include <grpcpp/support/client_interceptor.h>

namespace grpc {
namespace internal {

void RegisterGlobalClientStatsInterceptorFactory(
    grpc::experimental::ClientInterceptorFactoryInterface* factory);

}
}

#endif
