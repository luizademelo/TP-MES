Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON

#ifdef HAVE_LIBSYSTEMD
#include <systemd/sd-daemon.h>
#endif

#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/systemd_utils.h"

#ifdef HAVE_LIBSYSTEMD
// Checks if any of the file descriptors from fd_start to fd_start+n-1 matches
// the given UNIX domain socket address. If found, sets it as pre-allocated fd.
// Returns true if a matching fd was found, false otherwise.
bool set_matching_sd_unix_fd(grpc_tcp_server* s,
                             const grpc_resolved_address* addr,
                             const int fd_start, const int n) {
  // Convert socket address to string representation
  absl::StatusOr<std::string> addr_name = grpc_sockaddr_to_string(addr, true);
  // Check each file descriptor in the range
  for (int i = fd_start; i < fd_start + n; i++) {
    // Check if the fd is a UNIX socket matching our address
    if (sd_is_socket_unix(i, SOCK_STREAM, 1, addr_name.value().c_str(), 0)) {
      // Found matching fd, set it as pre-allocated
      grpc_tcp_server_set_pre_allocated_fd(s, i);
      return true;
    }
  }
  return false;
}

// Checks if any of the file descriptors from fd_start to fd_start+n-1 matches
// the given INET socket address (both family and port). If found, sets it as
// pre-allocated fd. Returns true if a matching fd was found, false otherwise.
bool set_matching_sd_inet_fd(grpc_tcp_server* s,
                             const grpc_resolved_address* addr,
                             const int family, const int port,
                             const int fd_start, const int n) {
  for (int i = fd_start; i < fd_start + n; i++) {
    // Check if fd is an INET socket of the correct family and port
    int r_inet = sd_is_socket_inet(i, family, SOCK_STREAM, 1, (uint16_t)port);
    // Check if fd matches the specific socket address
    int r_addr = sd_is_socket_sockaddr(
        i, SOCK_STREAM,
        reinterpret_cast<grpc_sockaddr*>(const_cast<char*>(addr->addr)),
        addr->len, 1);

    // If both checks pass, use this fd
    if (r_inet > 0 && r_addr > 0) {
      grpc_tcp_server_set_pre_allocated_fd(s, i);
      return true;
    }
  }
  return false;
}

// Attempts to find and set file descriptors from systemd that match the given
// address. Handles both UNIX and INET sockets, including wildcard addresses.
void set_matching_sd_fds(grpc_tcp_server* s, const grpc_resolved_address* addr,
                         int requested_port) {
  // Get number of file descriptors passed by systemd
  int n = sd_listen_fds(0);
  if (n <= 0) {
    return;  // No file descriptors available
  }

  // Systemd starts passing file descriptors from this value
  int fd_start = SD_LISTEN_FDS_START;
  grpc_resolved_address addr6_v4mapped;

  // Convert IPv4 address to IPv4-mapped IPv6 address if needed
  if (grpc_sockaddr_to_v4mapped(addr, &addr6_v4mapped)) {
    addr = &addr6_v4mapped;
  }

  int family = grpc_sockaddr_get_family(addr);
  int port = grpc_sockaddr_get_port(addr);

  if (family == AF_UNIX) {
    // Handle UNIX domain sockets
    set_matching_sd_unix_fd(s, addr, fd_start, n);
  } else {
    // Handle INET sockets
    if (grpc_sockaddr_is_wildcard(addr, &requested_port)) {
      // Special handling for wildcard addresses (INADDR_ANY/IN6ADDR_ANY)
      grpc_resolved_address wild4;
      grpc_resolved_address wild6;
      grpc_resolved_address wildcard_addrs[2];

      // Create both IPv4 and IPv6 wildcard addresses
      grpc_sockaddr_make_wildcards(requested_port, &wild4, &wild6);
      wildcard_addrs[0] = wild4;
      wildcard_addrs[1] = wild6;

      // Check for matching fds for both wildcard addresses
      for (grpc_resolved_address addr_w : wildcard_addrs) {
        int family_w = grpc_sockaddr_get_family(&addr_w);
        int port_w = grpc_sockaddr_get_port(&addr_w);
        if (set_matching_sd_inet_fd(s, &addr_w, family_w, port_w, fd_start,
                                    n)) {
          return;  // Found a match, we're done
        }
      }
      return;
    }

    // Non-wildcard case - just check for exact match
    set_matching_sd_inet_fd(s, addr, family, port, fd_start, n);
  }
}
#else
// Dummy implementation when systemd support is not available
void set_matching_sd_fds(GRPC_UNUSED grpc_tcp_server* s,
                         GRPC_UNUSED const grpc_resolved_address* addr,
                         GRPC_UNUSED int requested_port) {}
#endif

#endif
```

The comments explain:
1. The overall purpose of each function
2. Key steps in the logic flow
3. Special cases (like wildcard addresses)
4. Systemd-specific functionality
5. The fallback implementation when systemd isn't available

The comments are designed to help maintainers understand:
- What the code does at a high level
- Why certain operations are performed
- How the systemd integration works
- The flow of control through the functions