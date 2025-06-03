Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header file for address parsing utilities
#include "src/core/lib/address_utils/parse_address.h"

// Platform-specific portability header
#include <grpc/support/port_platform.h>

// I/O manager port definitions
#include "src/core/lib/iomgr/port.h"

// Include VM sockets support if available
#ifdef GRPC_HAVE_VSOCK
#include <linux/vm_sockets.h>
#endif

// Standard C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Unix socket support includes (platform-specific)
#ifdef GRPC_HAVE_UNIX_SOCKET
#ifdef GPR_WINDOWS
// Windows-specific unix socket headers
#include <ws2def.h>
#include <afunix.h>
#else
// Unix-like system unix socket header
#include <sys/un.h>
#endif
#endif

#include <string>

// Abseil libraries for logging and string manipulation
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/strip.h"

// gRPC core headers
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/util/grpc_if_nametoindex.h"
#include "src/core/util/host_port.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/string.h"

// Unix socket parsing implementation (if supported)
#ifdef GRPC_HAVE_UNIX_SOCKET

// Parses a unix URI into a resolved address structure
// Returns true on success, false on failure
bool grpc_parse_unix(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr) {
  // Validate scheme is "unix"
  if (uri.scheme() != "unix") {
    LOG(ERROR) << "Expected 'unix' scheme, got '" << uri.scheme() << "'";
    return false;
  }
  // Populate the sockaddr structure
  grpc_error_handle error =
      grpc_core::UnixSockaddrPopulate(uri.path(), resolved_addr);
  if (!error.ok()) {
    LOG(ERROR) << "" << grpc_core::StatusToString(error);
    return false;
  }
  return true;
}

// Parses a unix-abstract URI into a resolved address structure
// Returns true on success, false on failure
bool grpc_parse_unix_abstract(const grpc_core::URI& uri,
                              grpc_resolved_address* resolved_addr) {
  // Validate scheme is "unix-abstract"
  if (uri.scheme() != "unix-abstract") {
    LOG(ERROR) << "Expected 'unix-abstract' scheme, got '" << uri.scheme()
               << "'";
    return false;
  }
  // Populate the abstract sockaddr structure
  grpc_error_handle error =
      grpc_core::UnixAbstractSockaddrPopulate(uri.path(), resolved_addr);
  if (!error.ok()) {
    LOG(ERROR) << "" << grpc_core::StatusToString(error);
    return false;
  }
  return true;
}

namespace grpc_core {

// Populates a sockaddr_un structure for regular Unix domain sockets
grpc_error_handle UnixSockaddrPopulate(absl::string_view path,
                                       grpc_resolved_address* resolved_addr) {
  memset(resolved_addr, 0, sizeof(*resolved_addr));
  struct sockaddr_un* un =
      reinterpret_cast<struct sockaddr_un*>(resolved_addr->addr);
  const size_t maxlen = sizeof(un->sun_path) - 1;
  // Validate path length
  if (path.size() > maxlen) {
    return GRPC_ERROR_CREATE(absl::StrCat(
        "Path name should not have more than ", maxlen, " characters"));
  }
  un->sun_family = AF_UNIX;
  path.copy(un->sun_path, path.size());
  un->sun_path[path.size()] = '\0';
  resolved_addr->len = static_cast<socklen_t>(sizeof(*un));
  return absl::OkStatus();
}

// Populates a sockaddr_un structure for abstract Unix domain sockets
grpc_error_handle UnixAbstractSockaddrPopulate(
    absl::string_view path, grpc_resolved_address* resolved_addr) {
  memset(resolved_addr, 0, sizeof(*resolved_addr));
  struct sockaddr_un* un =
      reinterpret_cast<struct sockaddr_un*>(resolved_addr->addr);
  const size_t maxlen = sizeof(un->sun_path) - 1;
  // Validate path length
  if (path.size() > maxlen) {
    return GRPC_ERROR_CREATE(absl::StrCat(
        "Path name should not have more than ", maxlen, " characters"));
  }
  un->sun_family = AF_UNIX;
  un->sun_path[0] = '\0';  // Abstract socket starts with null byte
  path.copy(un->sun_path + 1, path.size());
  resolved_addr->len =
      static_cast<socklen_t>(sizeof(un->sun_family) + path.size() + 1);
  return absl::OkStatus();
}

}

#else  // GRPC_HAVE_UNIX_SOCKET not defined

// Stub implementations when Unix sockets are not supported
bool grpc_parse_unix(const grpc_core::URI& ,
                     grpc_resolved_address* ) {
  abort();
}

bool grpc_parse_unix_abstract(const grpc_core::URI& ,
                              grpc_resolved_address* ) {
  abort();
}

namespace grpc_core {

grpc_error_handle UnixSockaddrPopulate(
    absl::string_view , grpc_resolved_address* ) {
  abort();
}

grpc_error_handle UnixAbstractSockaddrPopulate(
    absl::string_view , grpc_resolved_address* ) {
  abort();
}

}
#endif  // GRPC_HAVE_UNIX_SOCKET

#ifdef GRPC_HAVE_VSOCK

// Parses a vsock URI into a resolved address structure
// Returns true on success, false on failure
bool grpc_parse_vsock(const grpc_core::URI& uri,
                      grpc_resolved_address* resolved_addr) {
  // Validate scheme is "vsock"
  if (uri.scheme() != "vsock") {
    LOG(ERROR) << "Expected 'vsock' scheme, got '" << uri.scheme() << "'";
    return false;
  }
  // Populate the vsock address structure
  grpc_error_handle error =
      grpc_core::VSockaddrPopulate(uri.path(), resolved_addr);
  if (!error.ok()) {
    LOG(ERROR) << "" << grpc_core::StatusToString(error);
    return false;
  }
  return true;
}

namespace grpc_core {

// Populates a sockaddr_vm structure for VM sockets
grpc_error_handle VSockaddrPopulate(absl::string_view path,
                                    grpc_resolved_address* resolved_addr) {
  memset(resolved_addr, 0, sizeof(*resolved_addr));
  struct sockaddr_vm* vm =
      reinterpret_cast<struct sockaddr_vm*>(resolved_addr->addr);
  vm->svm_family = AF_VSOCK;
  std::string s = std::string(path);
  // Parse CID and port from path (format: "CID:port")
  if (sscanf(s.c_str(), "%u:%u", &vm->svm_cid, &vm->svm_port) != 2) {
    return GRPC_ERROR_CREATE(
        absl::StrCat("Failed to parse vsock cid/port: ", s));
  }
  resolved_addr->len = static_cast<socklen_t>(sizeof(*vm));
  return absl::OkStatus();
}

}

#else  // GRPC_HAVE_VSOCK not defined

// Stub implementations when vsock is not supported
bool grpc_parse_vsock(const grpc_core::URI& ,
                      grpc_resolved_address* ) {
  GPR_UNREACHABLE_CODE(return false);
}

namespace grpc_core {

grpc_error_handle VSockaddrPopulate(
    absl::string_view , grpc_resolved_address* ) {
  GPR_UNREACHABLE_CODE(return absl::InvalidArgumentError("vsock unsupported."));
}

}
#endif  // GRPC_HAVE_VSOCK

// Parses an IPv4 host:port string into a resolved address structure
// If log_errors is true, will log parsing failures
// Returns true on success, false on failure
bool grpc_parse_ipv4_hostport(absl::string_view hostport,
                              grpc_resolved_address* addr, bool log_errors) {
  bool success = false;

  std::string host;
  std::string port;
  // Split host:port string into components
  if (!grpc_core::SplitHostPort(hostport, &host, &port)) {
    if (log_errors) {
      LOG(ERROR) << "Failed gpr_split_host_port(" << hostport << ", ...)";
    }
    return false;
  }

  // Initialize and set up IPv4 sockaddr structure
  memset(addr, 0, sizeof(*addr));
  addr->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
  grpc_sockaddr_in* in = reinterpret_cast<grpc_sockaddr_in*>(addr->addr);
  in->sin_family = GRPC_AF_INET;
  
  // Convert textual IPv4 address to binary form
  if (grpc_inet_pton(GRPC_AF_INET, host.c_str(), &in->sin_addr) == 0) {
    if (log_errors) {
      LOG(ERROR) << "invalid ipv4 address: '" << host << "'";
    }
    goto done;
  }

  // Validate and parse port number
  if (port.empty()) {
    if (log_errors) LOG(ERROR) << "no port given for ipv4 scheme";
    goto done;
  }
  int port_num;
  if (sscanf(port.c_str(), "%d", &port_num) != 1 || port_num < 0 ||
      port_num > 65535) {
    if (log_errors) LOG(ERROR) << "invalid ipv4 port: '" << port << "'";
    goto done;
  }
  in->sin_port = grpc_htons(static_cast<uint16_t>(port_num));
  success = true;
done:
  return success;
}

// Parses an IPv4 URI into a resolved address structure
// Returns true on success, false on failure
bool grpc_parse_ipv4(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr) {
  // Validate scheme is "ipv4"
  if (uri.scheme() != "ipv4") {
    LOG(ERROR) << "Expected 'ipv4' scheme, got '" << uri.scheme() << "'";
    return false;
  }
  // Parse the host:port portion of the URI (stripping leading '/')
  return grpc_parse_ipv4_hostport(absl::StripPrefix(uri.path(), "/"),
                                  resolved_addr, true );
}

// Parses an IPv6 host:port string into a resolved address structure
// If log_errors is true, will log parsing failures
// Returns true on success, false on failure
bool grpc_parse_ipv6_hostport(absl::string_view hostport,
                              grpc_resolved_address* addr, bool log_errors) {
  bool success = false;

  std::string host;
  std::string port;
  // Split host:port string into components
  if (!grpc_core::SplitHostPort(hostport, &host, &port)) {
    if (log_errors) {
      LOG(ERROR) << "Failed gpr_split_host_port(" << hostport << ", ...)";
    }
    return false;
  }

  // Initialize and set up IPv6 sockaddr structure
  memset(addr, 0, sizeof(*addr));
  addr->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
  grpc_sockaddr_in6* in6 = reinterpret_cast<grpc_sockaddr_in6*>(addr->addr);
  in6->sin6_family = GRPC_AF_INET6;

  // Handle IPv6 scoped addresses (with %)
  char* host_end =
      static_cast<char*>(gpr_memrchr(host.c_str(), '%', host.size()));
  if (host_end != nullptr) {
    CHECK(host_end >= host.c_str());
    char host_without_scope[GRPC_INET6_ADDRSTRLEN + 1];
    size_t host_without_scope_len =
        static_cast<size_t>(host_end - host.c_str());
    uint32_t sin6_scope_id = 0;
    
    // Validate length of address portion
    if (host_without_scope_len > GRPC_INET6_ADDRSTRLEN) {
      if (log_errors) {
        LOG(ERROR) << "invalid ipv6 address length " << host_without_scope_len
                   << ". Length cannot be greater than "
                   << "GRPC_INET6_ADDRSTRLEN i.e " << GRPC_INET6_ADDRSTRLEN;
      }
      goto done;
    }
    
    // Copy address portion (without scope)
    strncpy(host_without_scope, host.c_str(), host_without_scope_len);
    host_without_scope[host_without_scope_len] = '\0';
    
    // Convert textual IPv6 address to binary form
    if (grpc_inet_pton(GRPC_AF_INET6, host_without_scope, &in6->sin6_addr) ==
        0) {
      if (log_errors) {
        LOG(ERROR) << "invalid ipv6 address: '" << host_without_scope << "'";
      }
      goto done;
    }
    
    // Parse scope ID (either numeric or interface name)
    if (gpr_parse_bytes_to_uint32(host_end + 1,
                                  host.size() - host_without_scope_len - 1,
                                  &sin6_scope_id) == 0) {
      if ((sin6_scope_id = grpc_if_nametoindex(host_end + 1)) == 0) {
        LOG(ERROR) << "Invalid interface name: '" << host_end + 1
                   << "'. Non-numeric and failed if_nametoindex.";
        goto done;
      }
    }

    in6->sin6_scope_id = sin6_scope_id;
  } else {
    // Handle non-scoped IPv6 address
    if (grpc_inet_pton(GRPC_AF_INET6, host.c_str(), &in6->sin6_addr) == 0) {
      if (log_errors) {
        LOG(ERROR) << "invalid ipv6 address: '" << host << "'";
      }
      goto done;
    }
  }

  // Validate and parse port number
  if (port.empty()) {
    if (log_errors) LOG(ERROR) << "no port given for ipv6 scheme";
    goto done;
  }
  int port_num;
  if (sscanf(port.c_str(), "%d", &port_num) != 1 || port_num < 0 ||
      port_num > 65535) {
    if (log_errors) LOG(ERROR) << "invalid ipv6 port: '" << port << "'";
    goto done;
  }
  in6->sin6_port = grpc_htons(static_cast<uint16_t>(port_num));
  success = true;
done:
  return success;
}

// Parses an IPv6 URI into a resolved address structure
// Returns true on success, false on failure
bool grpc_parse_ipv6(const grpc_core::URI& uri,
                     grpc_resolved_address* resolved_addr) {
  // Validate scheme is "ipv6"
  if (uri.scheme() != "ipv6") {
    LOG(ERROR) << "Expected 'ipv6' scheme, got '" << uri.scheme() << "'";
    return false;
  }
  // Parse the host:port portion of the URI (stripping leading '/')
  return grpc_parse_ipv6_hostport(absl::StripPrefix(uri.path(), "/"),
                                  resolved_addr, true );
}

// General URI parsing function that delegates to specific protocol parsers
// Returns true on success, false on failure
bool grpc_parse_uri(const grpc_core::URI& uri,
                    grpc_resolved_address* resolved_addr) {
  // Dispatch to appropriate parser based on URI scheme
  if (uri.scheme() == "unix") {
    return grpc_parse_unix(uri, resolved_addr);
  }
  if (uri.scheme() == "unix-abstract") {
    return grpc_parse_unix_abstract(uri, resolved_addr);
  }
  if (uri.scheme() == "vsock") {
    return grpc_parse_vsock(uri, resolved_addr);
  }
  if (uri.scheme() == "ipv4") {
    return grpc_parse_ipv4(uri, resolved_addr);
  }
  if (uri.scheme() == "ipv6") {
    return grpc_parse_ipv6(uri, resolved_addr);
  }
  LOG(ERROR) << "Can't parse scheme '" << uri.scheme() << "'";
  return false;
}

// Converts well-known port names to numbers, or parses numeric ports
uint16_t grpc_strhtons(const char* port) {
  if (strcmp(port, "http") == 0) {
    return htons(80);
  } else if (strcmp(port, "https") == 0) {
    return htons(443);
  }
  return htons(static_cast<unsigned short>(atoi(port)));
}

namespace grpc_core {

// Converts a string in host:port format to a sockaddr structure
// Supports both IPv4 and IPv6 addresses
absl::StatusOr<grpc_resolved_address> StringToSockaddr(
    absl::string_view address_and_port) {
  grpc_resolved_address