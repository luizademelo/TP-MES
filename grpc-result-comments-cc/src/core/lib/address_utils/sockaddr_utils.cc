Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Includes necessary headers for socket address utilities
#include "src/core/lib/address_utils/sockaddr_utils.h"

#include <errno.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include "absl/log/check.h"
#ifdef GRPC_HAVE_VSOCK
#include <linux/vm_sockets.h>  // For VSOCK support
#endif
#include <string.h>

#include <string>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "src/core/util/uri.h"

// Unix socket support includes
#ifdef GRPC_HAVE_UNIX_SOCKET
#ifdef GPR_WINDOWS
#include <ws2def.h>
#include <afunix.h>
#else
#include <sys/un.h>
#endif
#endif

// Converts Unix socket address to URI if possible
#ifdef GRPC_HAVE_UNIX_SOCKET
static absl::StatusOr<std::string> grpc_sockaddr_to_uri_unix_if_possible(
    const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  if (addr->sa_family != AF_UNIX) {
    return absl::InvalidArgumentError(
        absl::StrCat("Socket family is not AF_UNIX: ", addr->sa_family));
  }
  const auto* unix_addr = reinterpret_cast<const struct sockaddr_un*>(addr);
  std::string scheme, path;
  // Handle abstract Unix sockets (sun_path begins with \0)
  if (unix_addr->sun_path[0] == '\0' && unix_addr->sun_path[1] != '\0') {
    scheme = "unix-abstract";
    path = std::string(unix_addr->sun_path + 1,
                       resolved_addr->len - sizeof(unix_addr->sun_family) - 1);
  } else {
    scheme = "unix";
    path = unix_addr->sun_path;
  }
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Create(
      std::move(scheme), "", "", std::move(path),
      {}, "");
  if (!uri.ok()) return uri.status();
  return uri->ToString();
}
#else
static absl::StatusOr<std::string> grpc_sockaddr_to_uri_unix_if_possible(
    const grpc_resolved_address* ) {
  return absl::InvalidArgumentError("Unix socket is not supported.");
}
#endif

// Converts VSOCK address to URI if possible
#ifdef GRPC_HAVE_VSOCK
static absl::StatusOr<std::string> grpc_sockaddr_to_uri_vsock_if_possible(
    const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  if (addr->sa_family != AF_VSOCK) {
    return absl::InvalidArgumentError(
        absl::StrCat("Socket family is not AF_VSOCK: ", addr->sa_family));
  }
  const auto* vsock_addr = reinterpret_cast<const struct sockaddr_vm*>(addr);
  return absl::StrCat("vsock:", vsock_addr->svm_cid, ":", vsock_addr->svm_port);
}
#else
static absl::StatusOr<std::string> grpc_sockaddr_to_uri_vsock_if_possible(
    const grpc_resolved_address* ) {
  return absl::InvalidArgumentError("VSOCK is not supported.");
}
#endif

// Prefix for IPv4-mapped IPv6 addresses (::ffff:0:0/96)
static const uint8_t kV4MappedPrefix[] = {0, 0, 0, 0, 0,    0,
                                          0, 0, 0, 0, 0xff, 0xff};

// Checks if an IPv6 address is IPv4-mapped (::ffff:0:0/96)
// If yes and resolved_addr4_out is not null, outputs the IPv4 equivalent
int grpc_sockaddr_is_v4mapped(const grpc_resolved_address* resolved_addr,
                              grpc_resolved_address* resolved_addr4_out) {
  CHECK(resolved_addr != resolved_addr4_out);
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  grpc_sockaddr_in* addr4_out =
      resolved_addr4_out == nullptr
          ? nullptr
          : reinterpret_cast<grpc_sockaddr_in*>(resolved_addr4_out->addr);
  if (addr->sa_family == GRPC_AF_INET6) {
    const grpc_sockaddr_in6* addr6 =
        reinterpret_cast<const grpc_sockaddr_in6*>(addr);
    if (memcmp(addr6->sin6_addr.s6_addr, kV4MappedPrefix,
               sizeof(kV4MappedPrefix)) == 0) {
      if (resolved_addr4_out != nullptr) {
        // Convert to IPv4 address
        memset(resolved_addr4_out, 0, sizeof(*resolved_addr4_out));
        memcpy(&addr4_out->sin_addr, &addr6->sin6_addr.s6_addr[12], 4);
        addr4_out->sin_family = GRPC_AF_INET;
        addr4_out->sin_port = addr6->sin6_port;
        resolved_addr4_out->len =
            static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
      }
      return 1;
    }
  }
  return 0;
}

// Converts an IPv4 address to IPv4-mapped IPv6 address (::ffff:a.b.c.d)
int grpc_sockaddr_to_v4mapped(const grpc_resolved_address* resolved_addr,
                              grpc_resolved_address* resolved_addr6_out) {
  CHECK(resolved_addr != resolved_addr6_out);
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  grpc_sockaddr_in6* addr6_out =
      reinterpret_cast<grpc_sockaddr_in6*>(resolved_addr6_out->addr);
  if (addr->sa_family == GRPC_AF_INET) {
    const grpc_sockaddr_in* addr4 =
        reinterpret_cast<const grpc_sockaddr_in*>(addr);
    memset(resolved_addr6_out, 0, sizeof(*resolved_addr6_out));
    addr6_out->sin6_family = GRPC_AF_INET6;
    memcpy(&addr6_out->sin6_addr.s6_addr[0], kV4MappedPrefix, 12);
    memcpy(&addr6_out->sin6_addr.s6_addr[12], &addr4->sin_addr, 4);
    addr6_out->sin6_port = addr4->sin_port;
    resolved_addr6_out->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
    return 1;
  }
  return 0;
}

// Checks if address is wildcard (0.0.0.0 or ::) and returns port if it is
int grpc_sockaddr_is_wildcard(const grpc_resolved_address* resolved_addr,
                              int* port_out) {
  const grpc_sockaddr* addr;
  grpc_resolved_address addr4_normalized;
  if (grpc_sockaddr_is_v4mapped(resolved_addr, &addr4_normalized)) {
    resolved_addr = &addr4_normalized;
  }
  addr = reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  if (addr->sa_family == GRPC_AF_INET) {
    // Check IPv4 wildcard (0.0.0.0)
    const grpc_sockaddr_in* addr4 =
        reinterpret_cast<const grpc_sockaddr_in*>(addr);
    if (addr4->sin_addr.s_addr != 0) {
      return 0;
    }
    *port_out = grpc_ntohs(addr4->sin_port);
    return 1;
  } else if (addr->sa_family == GRPC_AF_INET6) {
    // Check IPv6 wildcard (::)
    const grpc_sockaddr_in6* addr6 =
        reinterpret_cast<const grpc_sockaddr_in6*>(addr);
    int i;
    for (i = 0; i < 16; i++) {
      if (addr6->sin6_addr.s6_addr[i] != 0) {
        return 0;
      }
    }
    *port_out = grpc_ntohs(addr6->sin6_port);
    return 1;
  } else {
    return 0;
  }
}

// Creates wildcard addresses for both IPv4 and IPv6
void grpc_sockaddr_make_wildcards(int port, grpc_resolved_address* wild4_out,
                                  grpc_resolved_address* wild6_out) {
  grpc_sockaddr_make_wildcard4(port, wild4_out);
  grpc_sockaddr_make_wildcard6(port, wild6_out);
}

// Creates IPv4 wildcard address (0.0.0.0:port)
void grpc_sockaddr_make_wildcard4(int port,
                                  grpc_resolved_address* resolved_wild_out) {
  grpc_sockaddr_in* wild_out =
      reinterpret_cast<grpc_sockaddr_in*>(resolved_wild_out->addr);
  CHECK(port >= 0);
  CHECK(port < 65536);
  memset(resolved_wild_out, 0, sizeof(*resolved_wild_out));
  wild_out->sin_family = GRPC_AF_INET;
  wild_out->sin_port = grpc_htons(static_cast<uint16_t>(port));
  resolved_wild_out->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
}

// Creates IPv6 wildcard address (:::port)
void grpc_sockaddr_make_wildcard6(int port,
                                  grpc_resolved_address* resolved_wild_out) {
  grpc_sockaddr_in6* wild_out =
      reinterpret_cast<grpc_sockaddr_in6*>(resolved_wild_out->addr);
  CHECK(port >= 0);
  CHECK(port < 65536);
  memset(resolved_wild_out, 0, sizeof(*resolved_wild_out));
  wild_out->sin6_family = GRPC_AF_INET6;
  wild_out->sin6_port = grpc_htons(static_cast<uint16_t>(port));
  resolved_wild_out->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
}

// Converts socket address to string representation
absl::StatusOr<std::string> grpc_sockaddr_to_string(
    const grpc_resolved_address* resolved_addr, bool normalize) {
  const int save_errno = errno;
  grpc_resolved_address addr_normalized;
  if (normalize && grpc_sockaddr_is_v4mapped(resolved_addr, &addr_normalized)) {
    resolved_addr = &addr_normalized;
  }
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  std::string out;
#ifdef GRPC_HAVE_UNIX_SOCKET
  if (addr->sa_family == GRPC_AF_UNIX) {
    const sockaddr_un* addr_un = reinterpret_cast<const sockaddr_un*>(addr);
    bool abstract = addr_un->sun_path[0] == '\0';
    if (abstract) {
      int len = resolved_addr->len - sizeof(addr->sa_family);
      if (len <= 0) {
        return absl::InvalidArgumentError("empty UDS abstract path");
      }
      out = std::string(addr_un->sun_path, len);
    } else {
      size_t maxlen = sizeof(addr_un->sun_path);
      if (strnlen(addr_un->sun_path, maxlen) == maxlen) {
        return absl::InvalidArgumentError("UDS path is not null-terminated");
      }
      out = std::string(addr_un->sun_path);
    }
    return out;
  }
#endif

#ifdef GRPC_HAVE_VSOCK
  if (addr->sa_family == GRPC_AF_VSOCK) {
    const sockaddr_vm* addr_vm = reinterpret_cast<const sockaddr_vm*>(addr);
    out = absl::StrCat(addr_vm->svm_cid, ":", addr_vm->svm_port);
    return out;
  }
#endif

  const void* ip = nullptr;
  int port = 0;
  uint32_t sin6_scope_id = 0;
  if (addr->sa_family == GRPC_AF_INET) {
    const grpc_sockaddr_in* addr4 =
        reinterpret_cast<const grpc_sockaddr_in*>(addr);
    ip = &addr4->sin_addr;
    port = grpc_ntohs(addr4->sin_port);
  } else if (addr->sa_family == GRPC_AF_INET6) {
    const grpc_sockaddr_in6* addr6 =
        reinterpret_cast<const grpc_sockaddr_in6*>(addr);
    ip = &addr6->sin6_addr;
    port = grpc_ntohs(addr6->sin6_port);
    sin6_scope_id = addr6->sin6_scope_id;
  }
  char ntop_buf[GRPC_INET6_ADDRSTRLEN];
  if (ip != nullptr && grpc_inet_ntop(addr->sa_family, ip, ntop_buf,
                                      sizeof(ntop_buf)) != nullptr) {
    if (sin6_scope_id != 0) {
      // Handle IPv6 scoped addresses (with %zone)
      std::string host_with_scope =
          absl::StrFormat("%s%%%" PRIu32, ntop_buf, sin6_scope_id);
      out = grpc_core::JoinHostPort(host_with_scope, port);
    } else {
      out = grpc_core::JoinHostPort(ntop_buf, port);
    }
  } else {
    return absl::InvalidArgumentError(
        absl::StrCat("Unknown sockaddr family: ", addr->sa_family));
  }

  errno = save_errno;
  return out;
}

// Converts socket address to URI
absl::StatusOr<std::string> grpc_sockaddr_to_uri(
    const grpc_resolved_address* resolved_addr) {
  if (resolved_addr->len == 0) {
    return absl::InvalidArgumentError("Empty address");
  }
  grpc_resolved_address addr_normalized;
  if (grpc_sockaddr_is_v4mapped(resolved_addr, &addr_normalized)) {
    resolved_addr = &addr_normalized;
  }
  const char* scheme = grpc_sockaddr_get_uri_scheme(resolved_addr);
  if (scheme == nullptr) {
    return absl::InvalidArgumentError("Unknown address type");
  }
  if (strcmp("unix", scheme) == 0) {
    return grpc_sockaddr_to_uri_unix_if_possible(resolved_addr);
  }
  if (strcmp("vsock", scheme) == 0) {
    return grpc_sockaddr_to_uri_vsock_if_possible(resolved_addr);
  }

  auto path = grpc_sockaddr_to_string(resolved_addr, false );
  if (!path.ok()) return path;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Create(
      scheme, "", "", std::move(path.value()),
      {}, "");
  if (!uri.ok()) return uri.status();
  return uri->ToString();
}

// Gets URI scheme for the given socket address
const char* grpc_sockaddr_get_uri_scheme(
    const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  switch (addr->sa_family) {
    case GRPC_AF_INET:
      return "ipv4";
    case GRPC_AF_INET6:
      return "ipv6";
    case GRPC_AF_UNIX:
      return "unix";
#ifdef GRPC_HAVE_VSOCK
    case GRPC_AF_VSOCK:
      return "vsock";
#endif
  }
  return nullptr;
}

// Gets address family for the given socket address
int grpc_sockaddr_get_family(const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  return addr->sa_family;
}

// Gets port number from socket address
int grpc_sockaddr_get_port(const grpc_resolved_address* resolved_addr) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  switch (addr->sa_family) {
    case GRPC_AF_INET:
      return grpc_ntohs(
          (reinterpret_cast<const grpc_sockaddr_in*>(addr))->sin_port);
    case GRPC_AF_INET6:
      return grpc_ntohs(
          (reinterpret_cast<const grpc_sockaddr_in6*>(addr))->sin6_port);
#ifdef GRPC_HAVE_UNIX_SOCKET
    case AF_UNIX:
      return 1;
#endif
#ifdef GRPC_HAVE_VSOCK
    case AF_VSOCK:
      return 1;
#endif
    default:
      LOG(ERROR) << "Unknown socket family " << addr->sa_family
                 << " in grpc_sockaddr_get_port";
      return 0;
  }
}