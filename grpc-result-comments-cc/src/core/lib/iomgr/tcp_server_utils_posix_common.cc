Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Include necessary headers
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

// Only compile this code for POSIX systems with TCP support
#ifdef GRPC_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON

#include <errno.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <limits.h>
#include <stdio.h>
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
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/iomgr/vsock.h"
#include "src/core/util/crash.h"

// Minimum safe size for accept queue to prevent connection drops
#define MIN_SAFE_ACCEPT_QUEUE_SIZE 100

// Global variables for managing accept queue size
static gpr_once s_init_max_accept_queue_size = GPR_ONCE_INIT;
static int s_max_accept_queue_size;

// Initialize the maximum accept queue size by reading system configuration
static void init_max_accept_queue_size(void) {
  int n = SOMAXCONN;
  char buf[64];
  // Try to read the system-configured maximum queue size
  FILE* fp = fopen("/proc/sys/net/core/somaxconn", "r");
  if (fp == nullptr) {
    // Fall back to default if file can't be opened
    s_max_accept_queue_size = SOMAXCONN;
    return;
  }
  // Parse the value from the file
  if (fgets(buf, sizeof buf, fp)) {
    char* end;
    long i = strtol(buf, &end, 10);
    if (i > 0 && i <= INT_MAX && end && *end == '\n') {
      n = static_cast<int>(i);
    }
  }
  fclose(fp);
  s_max_accept_queue_size = n;

  // Warn if the queue size seems too small
  if (s_max_accept_queue_size < MIN_SAFE_ACCEPT_QUEUE_SIZE) {
    LOG(INFO) << "Suspiciously small accept queue (" << s_max_accept_queue_size
              << ") will probably lead to connection drops";
  }
}

// Get the maximum accept queue size, initializing it if necessary
static int get_max_accept_queue_size(void) {
  gpr_once_init(&s_init_max_accept_queue_size, init_max_accept_queue_size);
  return s_max_accept_queue_size;
}

// Callback for listener retry timer
static void listener_retry_timer_cb(void* arg, grpc_error_handle err) {
  // Only proceed if there was no error
  if (!err.ok()) return;
  grpc_tcp_listener* listener = static_cast<grpc_tcp_listener*>(arg);
  // Mark timer as no longer armed
  gpr_atm_no_barrier_store(&listener->retry_timer_armed, false);
  // If the file descriptor isn't shutdown, make it readable again
  if (!grpc_fd_is_shutdown(listener->emfd)) {
    grpc_fd_set_readable(listener->emfd);
  }
}

// Initialize retry timer for a TCP listener
void grpc_tcp_server_listener_initialize_retry_timer(
    grpc_tcp_listener* listener) {
  gpr_atm_no_barrier_store(&listener->retry_timer_armed, false);
  grpc_timer_init_unset(&listener->retry_timer);
  GRPC_CLOSURE_INIT(&listener->retry_closure, listener_retry_timer_cb, listener,
                    grpc_schedule_on_exec_ctx);
}

// Add a socket to the TCP server and initialize a listener for it
static grpc_error_handle add_socket_to_server(grpc_tcp_server* s, int fd,
                                              const grpc_resolved_address* addr,
                                              unsigned port_index,
                                              unsigned fd_index,
                                              grpc_tcp_listener** listener) {
  *listener = nullptr;
  int port = -1;

  // Prepare the socket (set options, bind, etc.)
  grpc_error_handle err =
      grpc_tcp_server_prepare_socket(s, fd, addr, s->so_reuseport, &port);
  if (!err.ok()) return err;
  CHECK_GT(port, 0);
  
  // Convert address to string for logging/identification
  absl::StatusOr<std::string> addr_str = grpc_sockaddr_to_string(addr, true);
  if (!addr_str.ok()) {
    return GRPC_ERROR_CREATE(addr_str.status().ToString());
  }
  std::string name = absl::StrCat("tcp-server-listener:", addr_str.value());
  
  // Add the new listener to the server's list
  gpr_mu_lock(&s->mu);
  s->nports++;
  grpc_tcp_listener* sp =
      static_cast<grpc_tcp_listener*>(gpr_malloc(sizeof(grpc_tcp_listener)));
  sp->next = nullptr;
  if (s->head == nullptr) {
    s->head = sp;
  } else {
    s->tail->next = sp;
  }
  s->tail = sp;
  
  // Initialize listener fields
  sp->server = s;
  sp->fd = fd;
  sp->emfd = grpc_fd_create(fd, name.c_str(), true);
  grpc_tcp_server_listener_initialize_retry_timer(sp);

  // Mark as pre-allocated if this is the pre-allocated FD
  if (grpc_tcp_server_pre_allocated_fd(s) == fd) {
    grpc_fd_set_pre_allocated(sp->emfd);
  }

  // Store address and port information
  memcpy(&sp->addr, addr, sizeof(grpc_resolved_address));
  sp->port = port;
  sp->port_index = port_index;
  sp->fd_index = fd_index;
  sp->is_sibling = 0;
  sp->sibling = nullptr;
  CHECK(sp->emfd);
  gpr_mu_unlock(&s->mu);

  *listener = sp;
  return err;
}

// Add a new address to the TCP server
grpc_error_handle grpc_tcp_server_add_addr(grpc_tcp_server* s,
                                           const grpc_resolved_address* addr,
                                           unsigned port_index,
                                           unsigned fd_index,
                                           grpc_dualstack_mode* dsmode,
                                           grpc_tcp_listener** listener) {
  int fd;
  // Check for pre-allocated FD first
  fd = grpc_tcp_server_pre_allocated_fd(s);

  if (fd > 0) {
    // Determine dualstack mode for IPv6 addresses
    int family = grpc_sockaddr_get_family(addr);
    if (family == AF_INET6) {
      const int off = 0;
      if (setsockopt(fd, 0, IPV6_V6ONLY, &off, sizeof(off)) == 0) {
        *dsmode = GRPC_DSMODE_DUALSTACK;
      } else if (!grpc_sockaddr_is_v4mapped(addr, nullptr)) {
        *dsmode = GRPC_DSMODE_IPV6;
      } else {
        *dsmode = GRPC_DSMODE_IPV4;
      }
    } else {
      *dsmode = family == AF_INET ? GRPC_DSMODE_IPV4 : GRPC_DSMODE_NONE;
    }

    // Handle v4-mapped addresses
    grpc_resolved_address addr4_copy;
    if (*dsmode == GRPC_DSMODE_IPV4 &&
        grpc_sockaddr_is_v4mapped(addr, &addr4_copy)) {
      addr = &addr4_copy;
    }

    return add_socket_to_server(s, fd, addr, port_index, fd_index, listener);
  }

  // Create new socket if no pre-allocated FD was available
  grpc_resolved_address addr4_copy;
  grpc_error_handle err =
      grpc_create_dualstack_socket(addr, SOCK_STREAM, 0, dsmode, &fd);
  if (!err.ok()) {
    return err;
  }
  // Handle v4-mapped addresses
  if (*dsmode == GRPC_DSMODE_IPV4 &&
      grpc_sockaddr_is_v4mapped(addr, &addr4_copy)) {
    addr = &addr4_copy;
  }
  return add_socket_to_server(s, fd, addr, port_index, fd_index, listener);
}

// Prepare a socket for use in the TCP server
grpc_error_handle grpc_tcp_server_prepare_socket(
    grpc_tcp_server* s, int fd, const grpc_resolved_address* addr,
    bool so_reuseport, int* port) {
  grpc_resolved_address sockname_temp;
  grpc_error_handle err;

  CHECK_GE(fd, 0);

  // Set socket options based on address type and server configuration
  if (so_reuseport && !grpc_is_unix_socket(addr) && !grpc_is_vsock(addr)) {
    err = grpc_set_socket_reuse_port(fd, 1);
    if (!err.ok()) goto error;
  }

#ifdef GRPC_LINUX_ERRQUEUE
  // Try to enable zero-copy if available (Linux only)
  err = grpc_set_socket_zerocopy(fd);
  if (!err.ok()) {
    // Not critical if zero-copy isn't supported
    VLOG(2) << "Node does not support SO_ZEROCOPY, continuing.";
  }
#endif
  // Set common socket options
  err = grpc_set_socket_nonblocking(fd, 1);
  if (!err.ok()) goto error;
  err = grpc_set_socket_cloexec(fd, 1);
  if (!err.ok()) goto error;
  
  // Additional options for non-Unix/non-vsock sockets
  if (!grpc_is_unix_socket(addr) && !grpc_is_vsock(addr)) {
    err = grpc_set_socket_low_latency(fd, 1);
    if (!err.ok()) goto error;
    err = grpc_set_socket_reuse_addr(fd, 1);
    if (!err.ok()) goto error;
    err = grpc_set_socket_dscp(fd, s->options.dscp);
    if (!err.ok()) goto error;
    err =
        grpc_set_socket_tcp_user_timeout(fd, s->options, false );
    if (!err.ok()) goto error;
  }
  err = grpc_set_socket_no_sigpipe_if_possible(fd);
  if (!err.ok()) goto error;

  // Apply any additional socket mutators from options
  err = grpc_apply_socket_mutator_in_args(fd, GRPC_FD_SERVER_LISTENER_USAGE,
                                          s->options);
  if (!err.ok()) goto error;

  // Bind and listen if this isn't the pre-allocated FD
  if (grpc_tcp_server_pre_allocated_fd(s) != fd) {
    if (bind(fd,
             reinterpret_cast<grpc_sockaddr*>(const_cast<char*>(addr->addr)),
             addr->len) < 0) {
      err = GRPC_OS_ERROR(errno, "bind");
      goto error;
    }

    if (listen(fd, get_max_accept_queue_size()) < 0) {
      err = GRPC_OS_ERROR(errno, "listen");
      goto error;
    }
  }

  // Get the actual bound port number
  sockname_temp.len = static_cast<socklen_t>(sizeof(struct sockaddr_storage));

  if (getsockname(fd, reinterpret_cast<grpc_sockaddr*>(sockname_temp.addr),
                  &sockname_temp.len) < 0) {
    err = GRPC_OS_ERROR(errno, "getsockname");
    goto error;
  }

  *port = grpc_sockaddr_get_port(&sockname_temp);
  return absl::OkStatus();

error:
  CHECK(!err.ok());
  if (fd >= 0) {
    close(fd);
  }
  return GRPC_ERROR_CREATE_REFERENCING("Unable to configure socket", &err, 1);
}

#endif
```