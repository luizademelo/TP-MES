
// Copyright 2023 gRPC authors.

#include "src/core/lib/iomgr/vsock.h"

#include <grpc/support/port_platform.h>

#ifdef GRPC_HAVE_VSOCK

#include <grpc/support/alloc.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

absl::StatusOr<std::vector<grpc_resolved_address>> grpc_resolve_vsock_address(
    absl::string_view name) {
  grpc_resolved_address addr;
  grpc_error_handle error = grpc_core::VSockaddrPopulate(name, &addr);
  GRPC_RETURN_IF_ERROR(error);
  return std::vector<grpc_resolved_address>({addr});
}

int grpc_is_vsock(const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  return addr->sa_family == AF_VSOCK;
}
#else
absl::StatusOr<std::vector<grpc_resolved_address>> grpc_resolve_vsock_address(
    absl::string_view ) {
  return absl::InvalidArgumentError("VSOCK is not supported.");
}

int grpc_is_vsock(const grpc_resolved_address* ) { return 0; }
#endif
