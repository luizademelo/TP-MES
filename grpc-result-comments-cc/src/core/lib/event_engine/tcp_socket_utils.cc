Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Header file for TCP socket utility functions
#include "src/core/lib/event_engine/tcp_socket_utils.h"

// gRPC event engine and platform support headers
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

// Core gRPC utility headers
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/iomgr/port.h"

// Platform-specific socket headers
#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON
#include <arpa/inet.h>

// Linux-specific TCP headers
#ifdef GRPC_LINUX_TCP_H
#include <linux/tcp.h>
#else
#include <netinet/in.h>
#endif
#include <sys/socket.h>
#endif

// Unix socket support
#ifdef GRPC_HAVE_UNIX_SOCKET
#ifdef GPR_WINDOWS
// Windows unix socket headers
#include <ws2def.h>
#include <afunix.h>
#else
// Unix socket headers for non-Windows platforms
#include <sys/stat.h>
#include <sys/un.h>
#endif
#endif

// VSOCK support
#ifdef GRPC_HAVE_VSOCK
#include <linux/vm_sockets.h>
#endif

// Standard C headers
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// C++ utility headers
#include <utility>

// Abseil headers
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"

// gRPC core utility headers
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/host_port.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/uri.h"

namespace grpc_event_engine::experimental {

namespace {
// IPv4-mapped IPv6 prefix (::ffff:0:0/96)
constexpr uint8_t kV4MappedPrefix[] = {0, 0, 0, 0, 0,    0,
                                       0, 0, 0, 0, 0xff, 0xff};

// Returns the scheme (protocol family) of the given resolved address
absl::StatusOr<std::string> GetScheme(
    const EventEngine::ResolvedAddress& resolved_address) {
  switch (resolved_address.address()->sa_family) {
    case AF_INET:
      return "ipv4";
    case AF_INET6:
      return "ipv6";
    case AF_UNIX:
      return "unix";
#ifdef GRPC_HAVE_VSOCK
    case AF_VSOCK:
      return "vsock";
#endif
    default:
      return absl::InvalidArgumentError(
          absl::StrFormat("Unknown sockaddr family: %d",
                          resolved_address.address()->sa_family));
  }
}

#ifdef GRPC_HAVE_UNIX_SOCKET
// Converts a resolved unix socket address to its filesystem path
absl::StatusOr<std::string> ResolvedAddrToUnixPathIfPossible(
    const EventEngine::ResolvedAddress* resolved_addr) {
  const sockaddr* addr = resolved_addr->address();
  if (addr->sa_family != AF_UNIX) {
    return absl::InvalidArgumentError(
        absl::StrCat("Socket family is not AF_UNIX: ", addr->sa_family));
  }
  const sockaddr_un* unix_addr = reinterpret_cast<const sockaddr_un*>(addr);
#ifdef GPR_APPLE
  // On Apple platforms, account for additional length field in sockaddr_un
  int len = resolved_addr->size() - sizeof(unix_addr->sun_family) -
            sizeof(unix_addr->sun_len) - 1;
#else
  int len = resolved_addr->size() - sizeof(unix_addr->sun_family) - 1;
#endif
  if (len <= 0) return "";
  std::string path;
  if (unix_addr->sun_path[0] == '\0') {
    // Handle abstract namespace sockets (path starts with null byte)
    path = std::string(unix_addr->sun_path + 1, len);
    path = absl::StrCat(std::string(1, '\0'), path);
  } else {
    // Handle regular filesystem path sockets
    size_t maxlen = sizeof(unix_addr->sun_path);
    if (strnlen(unix_addr->sun_path, maxlen) == maxlen) {
      return absl::InvalidArgumentError("UDS path is not null-terminated");
    }
    path = unix_addr->sun_path;
  }
  return path;
}

// Converts a resolved unix socket address to a URI string
absl::StatusOr<std::string> ResolvedAddrToUriUnixIfPossible(
    const EventEngine::ResolvedAddress* resolved_addr) {
  auto path = ResolvedAddrToUnixPathIfPossible(resolved_addr);
  GRPC_RETURN_IF_ERROR(path.status());
  std::string scheme;
  std::string path_string;
  if (!path->empty() && path->at(0) == '\0' && path->length() > 1) {
    // Abstract namespace socket
    scheme = "unix-abstract";
    path_string = path->substr(1, std::string::npos);
  } else {
    // Regular filesystem path socket
    scheme = "unix";
    path_string = std::move(*path);
  }

  // Create URI from scheme and path
  absl::StatusOr<grpc_core::URI> uri =
      grpc_core::URI::Create(std::move(scheme), "",
                             "", std::move(path_string),
                             {}, "");
  if (!uri.ok()) return uri.status();
  return uri->ToString();
}
#else
// Stub implementation when Unix sockets are not supported
absl::StatusOr<std::string> ResolvedAddrToUriUnixIfPossible(
    const EventEngine::ResolvedAddress* ) {
  return absl::InvalidArgumentError("Unix socket is not supported.");
}
#endif

#ifdef GRPC_HAVE_VSOCK
// Converts a resolved VSOCK address to a string representation (CID:PORT)
absl::StatusOr<std::string> ResolvedAddrToVsockPathIfPossible(
    const EventEngine::ResolvedAddress* resolved_addr) {
  const sockaddr* addr = resolved_addr->address();
  if (addr->sa_family != AF_VSOCK) {
    return absl::InvalidArgumentError(
        absl::StrCat("Socket family is not AF_VSOCK: ", addr->sa_family));
  }
  const sockaddr_vm* vm_addr = reinterpret_cast<const sockaddr_vm*>(addr);
  return absl::StrCat(vm_addr->svm_cid, ":", vm_addr->svm_port);
}

// Converts a resolved VSOCK address to a URI string
absl::StatusOr<std::string> ResolvedAddrToUriVsockIfPossible(
    const EventEngine::ResolvedAddress* resolved_addr) {
  auto path = ResolvedAddrToVsockPathIfPossible(resolved_addr);
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Create(
      "vsock", "", "", std::move(*path),
      {}, "");
  if (!uri.ok()) return uri.status();
  return uri->ToString();
}
#else
// Stub implementation when VSOCK is not supported
absl::StatusOr<std::string> ResolvedAddrToVsockPathIfPossible(
    const EventEngine::ResolvedAddress* ) {
  return absl::InvalidArgumentError("VSOCK is not supported.");
}

absl::StatusOr<std::string> ResolvedAddrToUriVsockIfPossible(
    const EventEngine::ResolvedAddress* ) {
  return absl::InvalidArgumentError("VSOCK is not supported.");
}
#endif

}  // namespace

// Checks if an IPv6 address is actually an IPv4-mapped IPv6 address
// and optionally converts it to an IPv4 address
bool ResolvedAddressIsV4Mapped(
    const EventEngine::ResolvedAddress& resolved_addr,
    EventEngine::ResolvedAddress* resolved_addr4_out) {
  const sockaddr* addr = resolved_addr.address();
  if (addr->sa_family == AF_INET6) {
    const sockaddr_in6* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
    sockaddr_in* addr4_out =
        resolved_addr4_out == nullptr
            ? nullptr
            : reinterpret_cast<sockaddr_in*>(
                  const_cast<sockaddr*>(resolved_addr4_out->address()));

    // Check if the address starts with the IPv4-mapped prefix
    if (memcmp(addr6->sin6_addr.s6_addr, kV4MappedPrefix,
               sizeof(kV4MappedPrefix)) == 0) {
      if (resolved_addr4_out != nullptr) {
        // Convert to IPv4 address
        memset(addr4_out, 0, EventEngine::ResolvedAddress::MAX_SIZE_BYTES);
        addr4_out->sin_family = AF_INET;

        // Copy the embedded IPv4 address (last 4 bytes)
        memcpy(&addr4_out->sin_addr, &addr6->sin6_addr.s6_addr[12], 4);
        addr4_out->sin_port = addr6->sin6_port;
        *resolved_addr4_out = EventEngine::ResolvedAddress(
            reinterpret_cast<sockaddr*>(addr4_out),
            static_cast<socklen_t>(sizeof(sockaddr_in)));
      }
      return true;
    }
  }
  return false;
}

// Converts an IPv4 address to an IPv4-mapped IPv6 address
bool ResolvedAddressToV4Mapped(
    const EventEngine::ResolvedAddress& resolved_addr,
    EventEngine::ResolvedAddress* resolved_addr6_out) {
  CHECK(&resolved_addr != resolved_addr6_out);
  const sockaddr* addr = resolved_addr.address();
  sockaddr_in6* addr6_out = const_cast<sockaddr_in6*>(
      reinterpret_cast<const sockaddr_in6*>(resolved_addr6_out->address()));
  if (addr->sa_family == AF_INET) {
    const sockaddr_in* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
    memset(resolved_addr6_out, 0, sizeof(*resolved_addr6_out));
    addr6_out->sin6_family = AF_INET6;
    // Set the IPv4-mapped prefix
    memcpy(&addr6_out->sin6_addr.s6_addr[0], kV4MappedPrefix, 12);
    // Embed the IPv4 address in the last 4 bytes
    memcpy(&addr6_out->sin6_addr.s6_addr[12], &addr4->sin_addr, 4);
    addr6_out->sin6_port = addr4->sin_port;
    *resolved_addr6_out = EventEngine::ResolvedAddress(
        reinterpret_cast<sockaddr*>(addr6_out), sizeof(sockaddr_in6));
    return true;
  }
  return false;
}

// Creates a wildcard IPv6 address (::) with the specified port
EventEngine::ResolvedAddress ResolvedAddressMakeWild6(int port) {
  EventEngine::ResolvedAddress resolved_wild_out;
  sockaddr_in6* wild_out = reinterpret_cast<sockaddr_in6*>(
      const_cast<sockaddr*>(resolved_wild_out.address()));
  CHECK_GE(port, 0);
  CHECK_LT(port, 65536);
  memset(wild_out, 0, sizeof(sockaddr_in6));
  wild_out->sin6_family = AF_INET6;
  wild_out->sin6_port = htons(static_cast<uint16_t>(port));
  return EventEngine::ResolvedAddress(
      reinterpret_cast<sockaddr*>(wild_out),
      static_cast<socklen_t>(sizeof(sockaddr_in6)));
}

// Creates a wildcard IPv4 address (0.0.0.0) with the specified port
EventEngine::ResolvedAddress ResolvedAddressMakeWild4(int port) {
  EventEngine::ResolvedAddress resolved_wild_out;
  sockaddr_in* wild_out = reinterpret_cast<sockaddr_in*>(
      const_cast<sockaddr*>(resolved_wild_out.address()));
  CHECK_GE(port, 0);
  CHECK_LT(port, 65536);
  memset(wild_out, 0, sizeof(sockaddr_in));
  wild_out->sin_family = AF_INET;
  wild_out->sin_port = htons(static_cast<uint16_t>(port));
  return EventEngine::ResolvedAddress(
      reinterpret_cast<sockaddr*>(wild_out),
      static_cast<socklen_t>(sizeof(sockaddr_in)));
}

// Gets the port number from a resolved address
int ResolvedAddressGetPort(const EventEngine::ResolvedAddress& resolved_addr) {
  const sockaddr* addr = resolved_addr.address();
  switch (addr->sa_family) {
    case AF_INET:
      return ntohs((reinterpret_cast<const sockaddr_in*>(addr))->sin_port);
    case AF_INET6:
      return ntohs((reinterpret_cast<const sockaddr_in6*>(addr))->sin6_port);
#ifdef GRPC_HAVE_UNIX_SOCKET
    case AF_UNIX:
      return 1;  // Unix sockets don't have ports, return dummy value
#endif
#ifdef GRPC_HAVE_VSOCK
    case AF_VSOCK:
      return 1;  // VSOCK doesn't have ports in the same way, return dummy value
#endif
    default:
      LOG(ERROR) << "Unknown socket family " << addr->sa_family
                 << " in ResolvedAddressGetPort";
      abort();
  }
}

// Sets the port number in a resolved address
void ResolvedAddressSetPort(EventEngine::ResolvedAddress& resolved_addr,
                            int port) {
  sockaddr* addr = const_cast<sockaddr*>(resolved_addr.address());
  switch (addr->sa_family) {
    case AF_INET:
      CHECK_GE(port, 0);
      CHECK_LT(port, 65536);
      (reinterpret_cast<sockaddr_in*>(addr))->sin_port =
          htons(static_cast<uint16_t>(port));
      return;
    case AF_INET6:
      CHECK_GE(port, 0);
      CHECK_LT(port, 65536);
      (reinterpret_cast<sockaddr_in6*>(addr))->sin6_port =
          htons(static_cast<uint16_t>(port));
      return;
    default:
      LOG(ERROR) << "Unknown socket family " << addr->sa_family
                 << " in grpc_sockaddr_set_port";
      abort();
  }
}

// Checks if the address is a wildcard address and returns its port if it is
std::optional<int> MaybeGetWildcardPortFromAddress(
    const EventEngine::ResolvedAddress& addr) {
  const EventEngine::ResolvedAddress* resolved_addr = &addr;
  EventEngine::ResolvedAddress addr4_normalized;
  if (ResolvedAddressIsV4Mapped(addr, &addr4_normalized)) {
    resolved_addr = &addr4_normalized;
  }
  if (resolved_addr->address()->sa_family == AF_INET) {
    // Check for IPv4 wildcard (0.0.0.0)
    const sockaddr_in* addr4 =
        reinterpret_cast<const sockaddr_in*>(resolved_addr->address());
    if (addr4->sin_addr.s_addr != 0) {
      return std::nullopt;
    }
    return static_cast<int>(ntohs(addr4->sin_port));
  } else if (resolved_addr->address()->sa_family == AF_INET6) {
    // Check for IPv6 wildcard (::)
    const sockaddr_in6* addr6 =
        reinterpret_cast<const sockaddr_in6*>(resolved_addr->address());
    int i;
    for (i = 0; i < 16; i++) {
      if (addr6->sin6_addr.s6_addr[i] != 0) {
        return std::nullopt;
      }
    }
    return static_cast<int>(ntohs(addr6->sin6_port));
  } else {
    return std::nullopt;
  }
}

// Checks if the address is a VSOCK address
bool ResolvedAddressIsVSock(const EventEngine::ResolvedAddress& resolved_addr) {
#ifdef GRPC_HAVE_VSOCK
  return resolved_addr.address()->sa_family == AF_VSOCK;
#else
  (void)resolved_addr;
  return false;
#endif
}

// Converts a resolved address to a normalized string representation
// (converts IPv4-mapped IPv6 addresses to IPv4 first)
absl::StatusOr<std::string> ResolvedAddressToNormalizedString(
    const EventEngine::ResolvedAddress& resolved_addr) {
  EventEngine::ResolvedAddress addr_normalized;
  if (!ResolvedAddressIsV4Mapped(resolved_addr, &addr_normalized)) {
    addr_normalized = resolved_addr;
  }
  return ResolvedAddressToString(addr_normalized);
}

// Converts a resolved address to a string representation (host:port for IP)
absl::StatusOr<std::string> ResolvedAddressToString(
    const EventEngine::ResolvedAddress& resolved_addr) {
  const int save_errno = errno;
  const sockaddr* addr = resolved_addr.address();
  std::string out;
#ifdef GRPC_HAVE_UNIX_SOCKET
  if (addr->sa_family == AF_UNIX) {
    return ResolvedAddrToUnixPathIfPossible(&resolved_addr);
  }
#endif

  if (ResolvedAddressIsVSock(resolved_addr)) {
    return ResolvedAddrToVsockPathIfPossible(&resolved_addr);
  }

  const void* ip = nullptr;
  int port = 0;
  uint32_t sin6_scope_id = 0;
  if (addr->sa_family == AF_INET) {
    const sockaddr_in* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
    ip = &addr4->sin_addr;
    port = ntohs(addr4->sin_port);
  } else if (addr->sa_family == AF_INET6) {
    const sockaddr_in6* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
    ip = &addr6->sin6_addr;
    port = ntohs