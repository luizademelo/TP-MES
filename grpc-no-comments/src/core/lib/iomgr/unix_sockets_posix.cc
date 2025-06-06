
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_HAVE_UNIX_SOCKET

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef GPR_WINDOWS

#include <ws2def.h>
#include <afunix.h>

#else
#include <sys/un.h>
#endif

#include <grpc/support/alloc.h>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

void grpc_create_socketpair_if_unix(int sv[2]) {
#ifdef GPR_WINDOWS
  grpc_core::Crash("AF_UNIX socket pairs are not supported on Windows");
#else
  CHECK_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, sv), 0);
#endif
}

absl::StatusOr<std::vector<grpc_resolved_address>>
grpc_resolve_unix_domain_address(absl::string_view name) {
  grpc_resolved_address addr;
  grpc_error_handle error = grpc_core::UnixSockaddrPopulate(name, &addr);
  if (error.ok()) {
    return std::vector<grpc_resolved_address>({addr});
  }
  auto result = grpc_error_to_absl_status(error);
  return result;
}

absl::StatusOr<std::vector<grpc_resolved_address>>
grpc_resolve_unix_abstract_domain_address(const absl::string_view name) {
  grpc_resolved_address addr;
  grpc_error_handle error =
      grpc_core::UnixAbstractSockaddrPopulate(name, &addr);
  if (error.ok()) {
    return std::vector<grpc_resolved_address>({addr});
  }
  auto result = grpc_error_to_absl_status(error);
  return result;
}

int grpc_is_unix_socket(const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  return addr->sa_family == AF_UNIX;
}

void grpc_unlink_if_unix_domain_socket(
    const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  if (addr->sa_family != AF_UNIX) {
    return;
  }
  struct sockaddr_un* un = reinterpret_cast<struct sockaddr_un*>(
      const_cast<char*>(resolved_addr->addr));

  if (un->sun_path[0] == '\0' && un->sun_path[1] != '\0') {
    return;
  }

#ifndef GPR_WINDOWS
  struct stat st;
  if (stat(un->sun_path, &st) == 0 && (st.st_mode & S_IFMT) == S_IFSOCK) {
    unlink(un->sun_path);
  }
#endif
}

#endif
