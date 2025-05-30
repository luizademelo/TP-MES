
// Copyright 2015 gRPC authors.

#include "src/core/resolver/resolver.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

Resolver::Resolver()
    : InternallyRefCounted(
          GRPC_TRACE_FLAG_ENABLED(resolver_refcount) ? "Resolver" : nullptr) {}

}
