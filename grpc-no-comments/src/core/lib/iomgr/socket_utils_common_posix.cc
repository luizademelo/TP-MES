
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>

#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#ifdef GRPC_LINUX_TCP_H
#include <linux/tcp.h>
#else
#include <netinet/tcp.h>
#endif
#include <grpc/event_engine/endpoint_config.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_factory_posix.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"
#include "src/core/util/string.h"

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

grpc_error_handle grpc_set_socket_sndbuf(int fd, int buffer_size_bytes) {
  return 0 == setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffer_size_bytes,
                         sizeof(buffer_size_bytes))
             ? absl::OkStatus()
             : GRPC_OS_ERROR(errno, "setsockopt(SO_SNDBUF)");
}

grpc_error_handle grpc_set_socket_rcvbuf(int fd, int buffer_size_bytes) {
  return 0 == setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buffer_size_bytes,
                         sizeof(buffer_size_bytes))
             ? absl::OkStatus()
             : GRPC_OS_ERROR(errno, "setsockopt(SO_RCVBUF)");
}

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

static gpr_once g_probe_so_reuesport_once = GPR_ONCE_INIT;
static int g_support_so_reuseport = false;

void probe_so_reuseport_once(void) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {

    s = socket(AF_INET6, SOCK_STREAM, 0);
  }
  if (s >= 0) {
    g_support_so_reuseport = GRPC_LOG_IF_ERROR(
        "check for SO_REUSEPORT", grpc_set_socket_reuse_port(s, 1));
    close(s);
  }
}

bool grpc_is_socket_reuse_port_supported() {
  gpr_once_init(&g_probe_so_reuesport_once, probe_so_reuseport_once);
  return g_support_so_reuseport;
}

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

grpc_error_handle grpc_set_socket_dscp(int fd, int dscp) {
  if (dscp == grpc_core::PosixTcpOptions::kDscpNotSet) {
    return absl::OkStatus();
  }

  int value = dscp << 2;

  int optval;
  socklen_t optlen = sizeof(optval);

  if (0 == getsockopt(fd, IPPROTO_IP, IP_TOS, &optval, &optlen)) {
    value |= (optval & 0x3);
    if (0 != setsockopt(fd, IPPROTO_IP, IP_TOS, &value, sizeof(value))) {
      return GRPC_OS_ERROR(errno, "setsockopt(IP_TOS)");
    }
  }

  if (0 == getsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &optval, &optlen)) {
    value |= (optval & 0x3);
    if (0 != setsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &value, sizeof(value))) {
      return GRPC_OS_ERROR(errno, "setsockopt(IPV6_TCLASS)");
    }
  }
  return absl::OkStatus();
}

#define DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS 20000
#define DEFAULT_SERVER_TCP_USER_TIMEOUT_MS 20000

static int g_default_client_tcp_user_timeout_ms =
    DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS;
static int g_default_server_tcp_user_timeout_ms =
    DEFAULT_SERVER_TCP_USER_TIMEOUT_MS;
static bool g_default_client_tcp_user_timeout_enabled = false;
static bool g_default_server_tcp_user_timeout_enabled = true;

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

static std::atomic<int> g_socket_supports_tcp_user_timeout(
    SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT);

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

      if (g_socket_supports_tcp_user_timeout.load() == 0) {
        if (0 != getsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &newval, &len)) {
          GRPC_TRACE_LOG(tcp, INFO)
              << "TCP_USER_TIMEOUT is not available. TCP_USER_TIMEOUT won't be "
                 "used thereafter";
          g_socket_supports_tcp_user_timeout.store(-1);
        } else {
          GRPC_TRACE_LOG(tcp, INFO)
              << "TCP_USER_TIMEOUT is available. TCP_USER_TIMEOUT will be used "
                 "thereafter";
          g_socket_supports_tcp_user_timeout.store(1);
        }
      }
      if (g_socket_supports_tcp_user_timeout.load() > 0) {
        GRPC_TRACE_LOG(tcp, INFO)
            << "Enabling TCP_USER_TIMEOUT with a timeout of " << timeout
            << " ms";
        if (0 != setsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &timeout,
                            sizeof(timeout))) {
          LOG(ERROR) << "setsockopt(TCP_USER_TIMEOUT) "
                     << grpc_core::StrError(errno);
          return absl::OkStatus();
        }
        if (0 != getsockopt(fd, IPPROTO_TCP, TCP_USER_TIMEOUT, &newval, &len)) {
          LOG(ERROR) << "getsockopt(TCP_USER_TIMEOUT) "
                     << grpc_core::StrError(errno);
          return absl::OkStatus();
        }
        if (newval != timeout) {
          GRPC_TRACE_LOG(tcp, INFO)
              << "Setting TCP_USER_TIMEOUT to value " << timeout
              << " ms. Actual TCP_USER_TIMEOUT value is " << newval << " ms";
          return absl::OkStatus();
        }
      }
    }
  } else {
    GRPC_TRACE_LOG(tcp, INFO)
        << "TCP_USER_TIMEOUT not supported for this platform";
  }
  return absl::OkStatus();
}

grpc_error_handle grpc_set_socket_with_mutator(int fd, grpc_fd_usage usage,
                                               grpc_socket_mutator* mutator) {
  CHECK(mutator);
  if (!grpc_socket_mutator_mutate_fd(mutator, fd, usage)) {
    return GRPC_ERROR_CREATE("grpc_socket_mutator failed.");
  }
  return absl::OkStatus();
}

grpc_error_handle grpc_apply_socket_mutator_in_args(
    int fd, grpc_fd_usage usage, const grpc_core::PosixTcpOptions& options) {
  if (options.socket_mutator == nullptr) {
    return absl::OkStatus();
  }
  return grpc_set_socket_with_mutator(fd, usage, options.socket_mutator);
}

static gpr_once g_probe_ipv6_once = GPR_ONCE_INIT;
static int g_ipv6_loopback_available;

static void probe_ipv6_once(void) {
  int fd = socket(AF_INET6, SOCK_STREAM, 0);
  g_ipv6_loopback_available = 0;
  if (fd < 0) {
    GRPC_TRACE_LOG(tcp, INFO)
        << "Disabling AF_INET6 sockets because socket() failed.";
  } else {
    grpc_sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_addr.s6_addr[15] = 1;
    if (bind(fd, reinterpret_cast<grpc_sockaddr*>(&addr), sizeof(addr)) == 0) {
      g_ipv6_loopback_available = 1;
    } else {
      GRPC_TRACE_LOG(tcp, INFO)
          << "Disabling AF_INET6 sockets because ::1 is not available.";
    }
    close(fd);
  }
}

int grpc_ipv6_loopback_available(void) {
  gpr_once_init(&g_probe_ipv6_once, probe_ipv6_once);
  return g_ipv6_loopback_available;
}

static grpc_error_handle error_for_fd(int fd) {
  if (fd >= 0) return absl::OkStatus();
  return GRPC_OS_ERROR(errno, "socket");
}

grpc_error_handle grpc_create_dualstack_socket(
    const grpc_resolved_address* resolved_addr, int type, int protocol,
    grpc_dualstack_mode* dsmode, int* newfd) {
  return grpc_create_dualstack_socket_using_factory(
      nullptr, resolved_addr, type, protocol, dsmode, newfd);
}

static int create_socket(grpc_socket_factory* factory, int domain, int type,
                         int protocol) {
  int res = (factory != nullptr)
                ? grpc_socket_factory_socket(factory, domain, type, protocol)
                : socket(domain, type, protocol);
  if (res < 0 && errno == EMFILE) {
    int saved_errno = errno;
    LOG_EVERY_N_SEC(ERROR, 10)
        << "socket(" << domain << ", " << type << ", " << protocol
        << ") returned " << res << " with error: |"
        << grpc_core::StrError(errno)
        << "|. This process might not have a sufficient file descriptor limit "
           "for the number of connections grpc wants to open (which is "
           "generally a function of the number of grpc channels, the lb policy "
           "of each channel, and the number of backends each channel is load "
           "balancing across).";
    errno = saved_errno;
  }
  return res;
}

grpc_error_handle grpc_create_dualstack_socket_using_factory(
    grpc_socket_factory* factory, const grpc_resolved_address* resolved_addr,
    int type, int protocol, grpc_dualstack_mode* dsmode, int* newfd) {
  const grpc_sockaddr* addr =
      reinterpret_cast<const grpc_sockaddr*>(resolved_addr->addr);
  int family = addr->sa_family;
  if (family == AF_INET6) {
    if (grpc_ipv6_loopback_available()) {
      *newfd = create_socket(factory, family, type, protocol);
    } else {
      *newfd = -1;
      errno = EAFNOSUPPORT;
    }

    if (*newfd >= 0 && grpc_set_socket_dualstack(*newfd)) {
      *dsmode = GRPC_DSMODE_DUALSTACK;
      return absl::OkStatus();
    }

    if (!grpc_sockaddr_is_v4mapped(resolved_addr, nullptr)) {
      *dsmode = GRPC_DSMODE_IPV6;
      return error_for_fd(*newfd);
    }

    if (*newfd >= 0) {
      close(*newfd);
    }
    family = AF_INET;
  }
  *dsmode = family == AF_INET ? GRPC_DSMODE_IPV4 : GRPC_DSMODE_NONE;
  *newfd = create_socket(factory, family, type, protocol);
  return error_for_fd(*newfd);
}

#endif
