Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific includes and configuration
#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// POSIX socket utilities implementation
#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

// System headers for socket operations
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>

// gRPC internal headers
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"

// Platform-specific TCP header inclusion
#ifdef GRPC_LINUX_TCP_H
#include <linux/tcp.h>
#else
#include <netinet/tcp.h>
#endif

// Additional headers
#include <grpc/event_engine/endpoint_config.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

// Utility headers
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_factory_posix.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"
#include "src/core/util/string.h"

/// Enables zero-copy operations on a socket if supported by the platform
/// @param fd The socket file descriptor
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_zerocopy(int fd) {
#ifdef GRPC_LINUX_ERRQUEUE
  const int enable = 1;
  auto err = setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY, &enable, sizeof(enable));
  if (err != 0) {
    return GRPC_OS_ERROR(errno, "setsockopt(SO_ZEROCOPY)");
  }
  return absl::OkStatus();
#else
  (void)fd;
  return GRPC_OS_ERROR(ENOSYS, "setsockopt(SO_ZEROCOPY)");
#endif
}

/// Sets a socket to blocking or non-blocking mode
/// @param fd The socket file descriptor
/// @param non_blocking 1 for non-blocking, 0 for blocking
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_nonblocking(int fd, int non_blocking) {
  int oldflags = fcntl(fd, F_GETFL, 0);
  if (oldflags < 0) {
    return GRPC_OS_ERROR(errno, "fcntl");
  }

  if (non_blocking) {
    oldflags |= O_NONBLOCK;
  } else {
    oldflags &= ~O_NONBLOCK;
  }

  if (fcntl(fd, F_SETFL, oldflags) != 0) {
    return GRPC_OS_ERROR(errno, "fcntl");
  }

  return absl::OkStatus();
}

/// Disables SIGPIPE signals for the given socket if supported by platform
/// @param fd The socket file descriptor
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_no_sigpipe_if_possible(int fd) {
#ifdef GRPC_HAVE_SO_NOSIGPIPE
  int val = 1;
  int newval;
  socklen_t intlen = sizeof(newval);
  if (0 != setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof(val))) {
    return GRPC_OS_ERROR(errno, "setsockopt(SO_NOSIGPIPE)");
  }
  if (0 != getsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &newval, &intlen)) {
    return GRPC_OS_ERROR(errno, "getsockopt(SO_NOSIGPIPE)");
  }
  if ((newval != 0) != (val != 0)) {
    return GRPC_ERROR_CREATE("Failed to set SO_NOSIGPIPE");
  }
#else
  (void)fd;
#endif
  return absl::OkStatus();
}

/// Enables IP packet information retrieval for IPv4 sockets if supported
/// @param fd The socket file descriptor
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_ip_pktinfo_if_possible(int fd) {
  (void)fd;
#ifdef GRPC_HAVE_IP_PKTINFO
  int get_local_ip = 1;
  if (0 != setsockopt(fd, IPPROTO_IP, IP_PKTINFO, &get_local_ip,
                      sizeof(get_local_ip))) {
    return GRPC_OS_ERROR(errno, "setsockopt(IP_PKTINFO)");
  }
#endif
  return absl::OkStatus();
}

/// Enables packet information retrieval for IPv6 sockets if supported
/// @param fd The socket file descriptor
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_ipv6_recvpktinfo_if_possible(int fd) {
  (void)fd;
#ifdef GRPC_HAVE_IPV6_RECVPKTINFO
  int get_local_ip = 1;
  if (0 != setsockopt(fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, &get_local_ip,
                      sizeof(get_local_ip))) {
    return GRPC_OS_ERROR(errno, "setsockopt(IPV6_RECVPKTINFO)");
  }
#endif
  return absl::OkStatus();
}

/// Sets the send buffer size for a socket
/// @param fd The socket file descriptor
/// @param buffer_size_bytes Desired buffer size in bytes
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_sndbuf(int fd, int buffer_size_bytes) {
  return 0 == setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffer_size_bytes,
                         sizeof(buffer_size_bytes))
             ? absl::OkStatus()
             : GRPC_OS_ERROR(errno, "setsockopt(SO_SNDBUF)");
}

/// Sets the receive buffer size for a socket
/// @param fd The socket file descriptor
/// @param buffer_size_bytes Desired buffer size in bytes
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_rcvbuf(int fd, int buffer_size_bytes) {
  return 0 == setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buffer_size_bytes,
                         sizeof(buffer_size_bytes))
             ? absl::OkStatus()
             : GRPC_OS_ERROR(errno, "setsockopt(SO_RCVBUF)");
}

/// Sets the close-on-exec flag for a socket
/// @param fd The socket file descriptor
/// @param close_on_exec 1 to enable close-on-exec, 0 to disable
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_cloexec(int fd, int close_on_exec) {
  int oldflags = fcntl(fd, F_GETFD, 0);
  if (oldflags < 0) {
    return GRPC_OS_ERROR(errno, "fcntl");
  }

  if (close_on_exec) {
    oldflags |= FD_CLOEXEC;
  } else {
    oldflags &= ~FD_CLOEXEC;
  }

  if (fcntl(fd, F_SETFD, oldflags) != 0) {
    return GRPC_OS_ERROR(errno, "fcntl");
  }

  return absl::OkStatus();
}

/// Enables or disables SO_REUSEADDR socket option
/// @param fd The socket file descriptor
/// @param reuse 1 to enable, 0 to disable
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_reuse_addr(int fd, int reuse) {
  int val = (reuse != 0);
  int newval;
  socklen_t intlen = sizeof(newval);
  if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
    return GRPC_OS_ERROR(errno, "setsockopt(SO_REUSEADDR)");
  }
  if (0 != getsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &newval, &intlen)) {
    return GRPC_OS_ERROR(errno, "getsockopt(SO_REUSEADDR)");
  }
  if ((newval != 0) != val) {
    return GRPC_ERROR_CREATE("Failed to set SO_REUSEADDR");
  }

  return absl::OkStatus();
}

/// Enables or disables SO_REUSEPORT socket option if supported
/// @param fd The socket file descriptor
/// @param reuse 1 to enable, 0 to disable
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_reuse_port(int fd, int reuse) {
#ifndef SO_REUSEPORT
  return GRPC_ERROR_CREATE("SO_REUSEPORT unavailable on compiling system");
#else
  int val = (reuse != 0);
  int newval;
  socklen_t intlen = sizeof(newval);
  if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val))) {
    return GRPC_OS_ERROR(errno, "setsockopt(SO_REUSEPORT)");
  }
  if (0 != getsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &newval, &intlen)) {
    return GRPC_OS_ERROR(errno, "getsockopt(SO_REUSEPORT)");
  }
  if ((newval != 0) != val) {
    return GRPC_ERROR_CREATE("Failed to set SO_REUSEPORT");
  }

  return absl::OkStatus();
#endif
}

// Static variables for SO_REUSEPORT support detection
static gpr_once g_probe_so_reuesport_once = GPR_ONCE_INIT;
static int g_support_so_reuseport = false;

/// Probes system for SO_REUSEPORT support (run once)
void probe_so_reuseport_once(void) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    // Try IPv6 if IPv4 fails
    s = socket(AF_INET6, SOCK_STREAM, 0);
  }
  if (s >= 0) {
    g_support_so_reuseport = GRPC_LOG_IF_ERROR(
        "check for SO_REUSEPORT", grpc_set_socket_reuse_port(s, 1));
    close(s);
  }
}

/// Checks if SO_REUSEPORT is supported on this system
/// @return true if supported, false otherwise
bool grpc_is_socket_reuse_port_supported() {
  gpr_once_init(&g_probe_so_reuesport_once, probe_so_reuseport_once);
  return g_support_so_reuseport;
}

/// Enables or disables TCP_NODELAY (Nagle's algorithm)
/// @param fd The socket file descriptor
/// @param low_latency 1 to disable Nagle's algorithm (low latency), 0 to enable
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_low_latency(int fd, int low_latency) {
  int val = (low_latency != 0);
  int newval;
  socklen_t intlen = sizeof(newval);
  if (0 != setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val))) {
    return GRPC_OS_ERROR(errno, "setsockopt(TCP_NODELAY)");
  }
  if (0 != getsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &newval, &intlen)) {
    return GRPC_OS_ERROR(errno, "getsockopt(TCP_NODELAY)");
  }
  if ((newval != 0) != val) {
    return GRPC_ERROR_CREATE("Failed to set TCP_NODELAY");
  }
  return absl::OkStatus();
}

/// Sets DSCP (Differentiated Services Code Point) on socket
/// @param fd The socket file descriptor
/// @param dscp DSCP value to set
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_dscp(int fd, int dscp) {
  if (dscp == grpc_core::PosixTcpOptions::kDscpNotSet) {
    return absl::OkStatus();
  }

  int value = dscp << 2;  // DSCP occupies upper 6 bits of TOS field

  int optval;
  socklen_t optlen = sizeof(optval);

  // For IPv4
  if (0 == getsockopt(fd, IPPROTO_IP, IP_TOS, &optval, &optlen)) {
    value |= (optval & 0x3);  // Preserve lower 2 bits
    if (0 != setsockopt(fd, IPPROTO_IP, IP_TOS, &value, sizeof(value))) {
      return GRPC_OS_ERROR(errno, "setsockopt(IP_TOS)");
    }
  }

  // For IPv6
  if (0 == getsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &optval, &optlen)) {
    value |= (optval & 0x3);  // Preserve lower 2 bits
    if (0 != setsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &value, sizeof(value))) {
      return GRPC_OS_ERROR(errno, "setsockopt(IPV6_TCLASS)");
    }
  }
  return absl::OkStatus();
}

// Default TCP user timeout values (20 seconds)
#define DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS 20000
#define DEFAULT_SERVER_TCP_USER_TIMEOUT_MS 20000

// Global default timeout settings
static int g_default_client_tcp_user_timeout_ms =
    DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS;
static int g_default_server_tcp_user_timeout_ms =
    DEFAULT_SERVER_TCP_USER_TIMEOUT_MS;
static bool g_default_client_tcp_user_timeout_enabled = false;
static bool g_default_server_tcp_user_timeout_enabled = true;

// Platform-specific TCP_USER_TIMEOUT handling
#if GPR_LINUX == 1
  #ifndef TCP_USER_TIMEOUT
  #define TCP_USER_TIMEOUT 18
  #endif
  #define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT 0
#else
  #ifdef TCP_USER_TIMEOUT
  #define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT 0
  #else
  #define TCP_USER_TIMEOUT 0
  #define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT -1
  #endif
#endif

// Atomic variable to track TCP_USER_TIMEOUT support
static std::atomic<int> g_socket_supports_tcp_user_timeout(
    SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT);

/// Configures default TCP user timeout settings
/// @param enable Whether to enable TCP user timeout
/// @param timeout Timeout value in milliseconds
/// @param is_client Whether configuring for client or server
void config_default_tcp_user_timeout(bool enable, int timeout, bool is_client) {
  if (is_client) {
    g_default_client_tcp_user_timeout_enabled = enable;
    if (timeout > 0) {
      g_default_client_tcp_user_timeout_ms = timeout;
    }
  } else {
    g_default_server_tcp_user_timeout_enabled = enable;
    if (timeout > 0) {
      g_default_server_tcp_user_timeout_ms = timeout;
    }
  }
}

/// Sets TCP user timeout on a socket
/// @param fd The socket file descriptor
/// @param options TCP options structure
/// @param is_client Whether this is a client socket
/// @return OK status on success or error with details
grpc_error_handle grpc_set_socket_tcp_user_timeout(
    int fd, const grpc_core::PosixTcpOptions& options, bool is_client) {
  (void)fd;
  (void)is_client;
  if (g_socket_supports_tcp_user_timeout.load() >= 0) {
    bool enable;
    int timeout;
    if (is_client) {
      enable = g_default_client_tcp_user_timeout_enabled;
      timeout = g_default_client_tcp_user_timeout_ms;
    } else {
      enable = g_default_server_tcp_user_timeout_enabled;
      timeout = g_default_server_tcp_user_timeout_ms;
    }
    
    // Override with options if specified
    int value = options.keep_alive_time_ms;
    if (value > 0) {
      enable = value != INT_MAX;
    }
    value = options.keep_alive_timeout_ms;
    if (value > 0) {
      timeout = value;
    }

    if (enable) {
      int newval;
      socklen_t len = sizeof(newval);

      // Probe for TCP_USER_TIMEOUT support if not already known
      if (g_socket_supports_tcp_user_timeout.load() == 0) {
        if (0 != getsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &newval, &len)) {
          GRPC_TRACE_LOG(tcp, INFO)
              << "TCP_USER_TIMEOUT is not available. TCP_USER_TIMEOUT won't be "
                 "used thereafter";
          g_socket_supports_tcp_user_timeout.store(-