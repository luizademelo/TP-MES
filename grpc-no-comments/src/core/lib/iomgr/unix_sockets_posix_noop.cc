
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/unix_sockets_posix.h"

#ifndef GRPC_HAVE_UNIX_SOCKET

#include <string>

#include "absl/log/check.h"

void grpc_create_socketpair_if_unix(int [2]) {
  // TODO: Either implement this for the non-Unix socket case or make

  CHECK(0);
}

absl::StatusOr<std::vector<grpc_resolved_address>>
grpc_resolve_unix_domain_address(absl::string_view ) {
  return absl::UnknownError("Unix domain sockets are not supported on Windows");
}

absl::StatusOr<std::vector<grpc_resolved_address>>
grpc_resolve_unix_abstract_domain_address(absl::string_view ) {
  return absl::UnknownError("Unix domain sockets are not supported on Windows");
}

int grpc_is_unix_socket(const grpc_resolved_address* ) {
  return false;
}

void grpc_unlink_if_unix_domain_socket(
    const grpc_resolved_address* ) {}

#endif
