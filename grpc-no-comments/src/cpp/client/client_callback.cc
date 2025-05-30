
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/status.h>

#include "src/core/lib/surface/call.h"

namespace grpc {
namespace internal {

bool ClientReactor::InternalTrailersOnly(const grpc_call* call) const {
  return grpc_call_is_trailers_only(call);
}

}
}
