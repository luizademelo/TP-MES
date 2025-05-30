
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_VSOCK_H
#define GRPC_SRC_CORE_LIB_IOMGR_VSOCK_H

#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolve_address.h"

absl::StatusOr<std::vector<grpc_resolved_address>> grpc_resolve_vsock_address(
    absl::string_view name);

int grpc_is_vsock(const grpc_resolved_address* resolved_addr);

#endif
