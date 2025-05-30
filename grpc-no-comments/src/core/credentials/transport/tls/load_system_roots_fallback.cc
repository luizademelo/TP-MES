
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#if !defined(GPR_LINUX) && !defined(GPR_ANDROID) && !defined(GPR_FREEBSD) && \
    !defined(GPR_APPLE) && !defined(GPR_WINDOWS)

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>

#include "src/core/credentials/transport/tls/load_system_roots.h"

namespace grpc_core {

grpc_slice LoadSystemRootCerts() { return grpc_empty_slice(); }

}

#endif
