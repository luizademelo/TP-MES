Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_HAVE_IFADDRS  // Only compile this code if ifaddrs is available

#include <errno.h>
#include <grpc/support/alloc.h>
#include <ifaddrs.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/tcp_server_utils_posix.h"
#include "src/core/util/crash.h"

// Finds a listener in the TCP server that matches the given address
// Parameters:
//   s - Pointer to the TCP server structure
//   addr - Pointer to the resolved address to search for
// Returns:
//   Pointer to the matching listener, or nullptr if not found
static grpc_tcp_listener* find_listener_with_addr(grpc_tcp_server* s,
                                                  grpc_resolved_address* addr) {
  grpc_tcp_listener* l;
  gpr_mu_lock(&s->mu);  // Lock server mutex for thread safety
  // Iterate through all listeners in the server
  for (l = s->head; l != nullptr; l = l->next) {
    if (l->addr.len != addr->len) {
      continue;  // Skip if address lengths don't match
    }
    if (memcmp(l->addr.addr, addr->addr, addr->len) == 0) {
      break;  // Found matching address
    }
  }
  gpr_mu_unlock(&s->mu);  // Unlock server mutex
  return l;
}

// Finds and returns an unused port number
// Parameters:
//   port - Output parameter for the unused port number
// Returns:
//   OK status if successful, error status otherwise
static grpc_error_handle get_unused_port(int* port) {
  grpc_resolved_address wild;
  // Create a wildcard IPv6 address
  grpc_sockaddr_make_wildcard6(0, &wild);
  grpc_dualstack_mode dsmode;
  int fd;
  // Create a dual-stack socket
  grpc_error_handle err =
      grpc_create_dualstack_socket(&wild, SOCK_STREAM, 0, &dsmode, &fd);
  if (!err.ok()) {
    return err;
  }
  // If we got an IPv4 socket, create a wildcard IPv4 address instead
  if (dsmode == GRPC_DSMODE_IPV4) {
    grpc_sockaddr_make_wildcard4(0, &wild);
  }
  // Bind to the wildcard address
  if (bind(fd, reinterpret_cast<const grpc_sockaddr*>(wild.addr), wild.len) !=
      0) {
    err = GRPC_OS_ERROR(errno, "bind");
    close(fd);
    return err;
  }
  // Get the socket name (which will include the assigned port)
  if (getsockname(fd, reinterpret_cast<grpc_sockaddr*>(wild.addr), &wild.len) !=
      0) {
    err = GRPC_OS_ERROR(errno, "getsockname");
    close(fd);
    return err;
  }
  close(fd);
  *port = grpc_sockaddr_get_port(&wild);
  return *port <= 0 ? GRPC_ERROR_CREATE("Bad port") : absl::OkStatus();
}

// Checks if IPv4 is available on the system
// Returns:
//   true if IPv4 is available, false otherwise
static bool grpc_is_ipv4_available() {
  const int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd >= 0) close(fd);
  return fd >= 0;
}

// Adds all local addresses to the TCP server
// Parameters:
//   s - Pointer to the TCP server
//   port_index - Index of the port to use
//   requested_port - Port number to use (0 means pick any available port)
//   out_port - Output parameter for the actual port used
// Returns:
//   OK status if successful, error status otherwise
grpc_error_handle grpc_tcp_server_add_all_local_addrs(grpc_tcp_server* s,
                                                      unsigned port_index,
                                                      int requested_port,
                                                      int* out_port) {
  struct ifaddrs* ifa = nullptr;
  struct ifaddrs* ifa_it;
  unsigned fd_index = 0;
  grpc_tcp_listener* sp = nullptr;
  grpc_error_handle err;
  
  // If no specific port requested, find an unused one
  if (requested_port == 0) {
    // Note: There could be a race where some local addrs can listen on the
    // selected port while others cannot
    if ((err = get_unused_port(&requested_port)) != absl::OkStatus()) {
      return err;
    } else if (requested_port <= 0) {
      return GRPC_ERROR_CREATE("Bad get_unused_port()");
    }
    VLOG(2) << "Picked unused port " << requested_port;
  }

  // Cache IPv4 availability check
  static bool v4_available = grpc_is_ipv4_available();

  // Get all network interfaces
  if (getifaddrs(&ifa) != 0 || ifa == nullptr) {
    return GRPC_OS_ERROR(errno, "getifaddrs");
  }
  
  // Iterate through all network interfaces
  for (ifa_it = ifa; ifa_it != nullptr; ifa_it = ifa_it->ifa_next) {
    grpc_resolved_address addr;
    grpc_dualstack_mode dsmode;
    grpc_tcp_listener* new_sp = nullptr;
    const char* ifa_name = (ifa_it->ifa_name ? ifa_it->ifa_name : "<unknown>");
    
    if (ifa_it->ifa_addr == nullptr) {
      continue;  // Skip interfaces without addresses
    } else if (ifa_it->ifa_addr->sa_family == AF_INET) {
      if (!v4_available) {
        continue;  // Skip IPv4 if not available
      }
      addr.len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
    } else if (ifa_it->ifa_addr->sa_family == AF_INET6) {
      addr.len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
    } else {
      continue;  // Skip non-IP addresses
    }
    
    // Copy the address and set the requested port
    memcpy(addr.addr, ifa_it->ifa_addr, addr.len);
    if (!grpc_sockaddr_set_port(&addr, requested_port)) {
      err = GRPC_ERROR_CREATE("Failed to set port");
      break;
    }
    
    // Convert address to string for logging
    auto addr_str = grpc_sockaddr_to_string(&addr, false);
    if (!addr_str.ok()) {
      return GRPC_ERROR_CREATE(addr_str.status().ToString());
    }
    VLOG(2) << absl::StrFormat(
        "Adding local addr from interface %s flags 0x%x to server: %s",
        ifa_name, ifa_it->ifa_flags, addr_str->c_str());

    // Skip duplicate addresses
    if (find_listener_with_addr(s, &addr) != nullptr) {
      VLOG(2) << "Skipping duplicate addr " << *addr_str << " on interface "
              << ifa_name;
      continue;
    }
    
    // Add the address as a new listener
    if ((err = grpc_tcp_server_add_addr(s, &addr, port_index, fd_index, &dsmode,
                                        &new_sp)) != absl::OkStatus()) {
      grpc_error_handle root_err = GRPC_ERROR_CREATE(
          absl::StrCat("Failed to add listener: ", addr_str.value()));
      err = grpc_error_add_child(root_err, err);
      break;
    } else {
      CHECK(requested_port == new_sp->port);
      ++fd_index;
      // Link siblings (multiple listeners on same port)
      if (sp != nullptr) {
        new_sp->is_sibling = 1;
        sp->sibling = new_sp;
      }
      sp = new_sp;
    }
  }
  
  freeifaddrs(ifa);  // Free interface list
  
  if (!err.ok()) {
    return err;  // Return any error that occurred
  } else if (sp == nullptr) {
    return GRPC_ERROR_CREATE("No local addresses");  // No addresses found
  } else {
    *out_port = sp->port;  // Return the port used
    return absl::OkStatus();
  }
}

// Indicates whether ifaddrs functionality is available
// Returns:
//   true (since this file is only compiled when ifaddrs is available)
bool grpc_tcp_server_have_ifaddrs(void) { return true; }

#endif  // GRPC_HAVE_IFADDRS
```