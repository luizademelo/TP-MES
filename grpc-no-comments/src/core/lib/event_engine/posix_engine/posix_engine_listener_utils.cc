// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/posix_engine_listener_utils.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdint>
#include <cstring>
#include <string>

#include "absl/cleanup/cleanup.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_replace.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/util/crash.h"
#include "src/core/util/status_helper.h"

#define MIN_SAFE_ACCEPT_QUEUE_SIZE 100

#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON
#include <errno.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace grpc_event_engine::experimental {

#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON

namespace {

using ResolvedAddress =
    grpc_event_engine::experimental::EventEngine::ResolvedAddress;
using ListenerSocket = ListenerSocketsContainer::ListenerSocket;

#ifdef GRPC_HAVE_IFADDRS

absl::StatusOr<int> GetUnusedPort() {
  ResolvedAddress wild = ResolvedAddressMakeWild6(0);
  PosixSocketWrapper::DSMode dsmode;
  auto sock = PosixSocketWrapper::CreateDualStackSocket(nullptr, wild,
                                                        SOCK_STREAM, 0, dsmode);
  GRPC_RETURN_IF_ERROR(sock.status());
  if (dsmode == PosixSocketWrapper::DSMode::DSMODE_IPV4) {
    wild = ResolvedAddressMakeWild4(0);
  }
  if (bind(sock->Fd(), wild.address(), wild.size()) != 0) {
    close(sock->Fd());
    return absl::FailedPreconditionError(
        absl::StrCat("bind(GetUnusedPort): ", std::strerror(errno)));
  }
  socklen_t len = wild.size();
  if (getsockname(sock->Fd(), const_cast<sockaddr*>(wild.address()), &len) !=
      0) {
    close(sock->Fd());
    return absl::FailedPreconditionError(
        absl::StrCat("getsockname(GetUnusedPort): ", std::strerror(errno)));
  }
  close(sock->Fd());
  int port = ResolvedAddressGetPort(wild);
  if (port <= 0) {
    return absl::FailedPreconditionError("Bad port");
  }
  return port;
}

bool SystemHasIfAddrs() { return true; }

#else

bool SystemHasIfAddrs() { return false; }

#endif

int InitMaxAcceptQueueSize() {
  int n = SOMAXCONN;
  char buf[64];
  FILE* fp = fopen("/proc/sys/net/core/somaxconn", "r");
  int max_accept_queue_size;
  if (fp == nullptr) {

    return SOMAXCONN;
  }
  if (fgets(buf, sizeof buf, fp)) {
    char* end;
    long i = strtol(buf, &end, 10);
    if (i > 0 && i <= INT_MAX && end && *end == '\n') {
      n = static_cast<int>(i);
    }
  }
  fclose(fp);
  max_accept_queue_size = n;

  if (max_accept_queue_size < MIN_SAFE_ACCEPT_QUEUE_SIZE) {
    LOG(INFO) << "Suspiciously small accept queue (" << max_accept_queue_size
              << ") will probably lead to connection drops";
  }
  return max_accept_queue_size;
}

int GetMaxAcceptQueueSize() {
  static const int kMaxAcceptQueueSize = InitMaxAcceptQueueSize();
  return kMaxAcceptQueueSize;
}

absl::Status PrepareSocket(const PosixTcpOptions& options,
                           ListenerSocket& socket) {
  ResolvedAddress sockname_temp;
  int fd = socket.sock.Fd();
  CHECK_GE(fd, 0);
  bool close_fd = true;
  socket.zero_copy_enabled = false;
  socket.port = 0;
  auto sock_cleanup = absl::MakeCleanup([&close_fd, fd]() -> void {
    if (close_fd && fd >= 0) {
      close(fd);
    }
  });
  if (PosixSocketWrapper::IsSocketReusePortSupported() &&
      options.allow_reuse_port && socket.addr.address()->sa_family != AF_UNIX &&
      !ResolvedAddressIsVSock(socket.addr)) {
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketReusePort(1));
  }

#ifdef GRPC_LINUX_ERRQUEUE
  if (!socket.sock.SetSocketZeroCopy().ok()) {

    VLOG(2) << "Node does not support SO_ZEROCOPY, continuing.";
  } else {
    socket.zero_copy_enabled = true;
  }
#endif

  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketNonBlocking(1));
  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketCloexec(1));

  if (socket.addr.address()->sa_family != AF_UNIX &&
      !ResolvedAddressIsVSock(socket.addr)) {
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketLowLatency(1));
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketReuseAddr(1));
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketDscp(options.dscp));
    socket.sock.TrySetSocketTcpUserTimeout(options, false);
  }
  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketNoSigpipeIfPossible());
  GRPC_RETURN_IF_ERROR(socket.sock.ApplySocketMutatorInOptions(
      GRPC_FD_SERVER_LISTENER_USAGE, options));

  if (bind(fd, socket.addr.address(), socket.addr.size()) < 0) {
    auto sockaddr_str = ResolvedAddressToString(socket.addr);
    if (!sockaddr_str.ok()) {
      LOG(ERROR) << "Could not convert sockaddr to string: "
                 << sockaddr_str.status();
      sockaddr_str = "<unparsable>";
    }
    sockaddr_str = absl::StrReplaceAll(*sockaddr_str, {{"\0", "@"}});
    return absl::FailedPreconditionError(
        absl::StrCat("Error in bind for address '", *sockaddr_str,
                     "': ", std::strerror(errno)));
  }

  if (listen(fd, GetMaxAcceptQueueSize()) < 0) {
    return absl::FailedPreconditionError(
        absl::StrCat("Error in listen: ", std::strerror(errno)));
  }
  socklen_t len = static_cast<socklen_t>(sizeof(struct sockaddr_storage));

  if (getsockname(fd, const_cast<sockaddr*>(sockname_temp.address()), &len) <
      0) {
    return absl::FailedPreconditionError(
        absl::StrCat("Error in getsockname: ", std::strerror(errno)));
  }

  socket.port =
      ResolvedAddressGetPort(ResolvedAddress(sockname_temp.address(), len));

  close_fd = false;
  return absl::OkStatus();
}

}

absl::StatusOr<ListenerSocket> CreateAndPrepareListenerSocket(
    const PosixTcpOptions& options, const ResolvedAddress& addr) {
  ResolvedAddress addr4_copy;
  ListenerSocket socket;
  auto result = PosixSocketWrapper::CreateDualStackSocket(
      nullptr, addr, SOCK_STREAM, 0, socket.dsmode);
  if (!result.ok()) {
    return result.status();
  }
  socket.sock = *result;
  if (socket.dsmode == PosixSocketWrapper::DSMODE_IPV4 &&
      ResolvedAddressIsV4Mapped(addr, &addr4_copy)) {
    socket.addr = addr4_copy;
  } else {
    socket.addr = addr;
  }
  GRPC_RETURN_IF_ERROR(PrepareSocket(options, socket));
  CHECK_GT(socket.port, 0);
  return socket;
}

bool IsSockAddrLinkLocal(const EventEngine::ResolvedAddress* resolved_addr) {
  const sockaddr* addr = resolved_addr->address();
  if (addr->sa_family == AF_INET) {
    const sockaddr_in* addr4 = reinterpret_cast<const sockaddr_in*>(addr);

    if ((addr4->sin_addr.s_addr & htonl(0xFFFF0000)) == htonl(0xA9FE0000)) {
      return true;
    }
  } else if (addr->sa_family == AF_INET6) {
    const sockaddr_in6* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
    const uint8_t* addr_bytes = addr6->sin6_addr.s6_addr;

    if ((addr_bytes[0] == 0xfe) && ((addr_bytes[1] & 0xc0) == 0x80)) {
      return true;
    }
  }

  return false;
}

absl::StatusOr<int> ListenerContainerAddAllLocalAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port) {
#ifdef GRPC_HAVE_IFADDRS
  absl::Status op_status = absl::OkStatus();
  struct ifaddrs* ifa = nullptr;
  struct ifaddrs* ifa_it;
  bool no_local_addresses = true;
  int assigned_port = 0;
  if (requested_port == 0) {
    auto result = GetUnusedPort();
    GRPC_RETURN_IF_ERROR(result.status());
    requested_port = *result;
    VLOG(2) << "Picked unused port " << requested_port;
  }
  if (getifaddrs(&ifa) != 0 || ifa == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("getifaddrs: ", std::strerror(errno)));
  }

  static const bool is_ipv4_available = [] {
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) close(fd);
    return fd >= 0;
  }();

  for (ifa_it = ifa; ifa_it != nullptr; ifa_it = ifa_it->ifa_next) {
    ResolvedAddress addr;
    socklen_t len;
    const char* ifa_name = (ifa_it->ifa_name ? ifa_it->ifa_name : "<unknown>");
    if (ifa_it->ifa_addr == nullptr) {
      continue;
    } else if (ifa_it->ifa_addr->sa_family == AF_INET) {
      if (!is_ipv4_available) {
        continue;
      }
      len = static_cast<socklen_t>(sizeof(sockaddr_in));
    } else if (ifa_it->ifa_addr->sa_family == AF_INET6) {
      len = static_cast<socklen_t>(sizeof(sockaddr_in6));
    } else {
      continue;
    }
    addr = EventEngine::ResolvedAddress(ifa_it->ifa_addr, len);
    ResolvedAddressSetPort(addr, requested_port);
    std::string addr_str = *ResolvedAddressToString(addr);
    if (IsSockAddrLinkLocal(&addr)) {

      continue;
    }
    VLOG(2) << absl::StrFormat(
        "Adding local addr from interface %s flags 0x%x to server: %s",
        ifa_name, ifa_it->ifa_flags, addr_str.c_str());

    if (listener_sockets.Find(addr).ok()) {
      VLOG(2) << "Skipping duplicate addr " << addr_str << " on interface "
              << ifa_name;
      continue;
    }
    auto result = CreateAndPrepareListenerSocket(options, addr);
    if (!result.ok()) {
      op_status = absl::FailedPreconditionError(
          absl::StrCat("Failed to add listener: ", addr_str,
                       " due to error: ", result.status().message()));
      break;
    } else {
      listener_sockets.Append(*result);
      assigned_port = result->port;
      no_local_addresses = false;
    }
  }
  freeifaddrs(ifa);
  GRPC_RETURN_IF_ERROR(op_status);
  if (no_local_addresses) {
    return absl::FailedPreconditionError("No local addresses");
  }
  return assigned_port;

#else
  (void)listener_sockets;
  (void)options;
  (void)requested_port;
  grpc_core::Crash("System does not support ifaddrs");
#endif
}

absl::StatusOr<int> ListenerContainerAddWildcardAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port) {
  ResolvedAddress wild4 = ResolvedAddressMakeWild4(requested_port);
  ResolvedAddress wild6 = ResolvedAddressMakeWild6(requested_port);
  absl::StatusOr<ListenerSocket> v6_sock;
  absl::StatusOr<ListenerSocket> v4_sock;
  int assigned_port = 0;

  if (SystemHasIfAddrs() && options.expand_wildcard_addrs) {
    return ListenerContainerAddAllLocalAddresses(listener_sockets, options,
                                                 requested_port);
  }

  v6_sock = CreateAndPrepareListenerSocket(options, wild6);
  if (v6_sock.ok()) {
    listener_sockets.Append(*v6_sock);
    requested_port = v6_sock->port;
    assigned_port = v6_sock->port;
    if (v6_sock->dsmode == PosixSocketWrapper::DSMODE_DUALSTACK ||
        v6_sock->dsmode == PosixSocketWrapper::DSMODE_IPV4) {
      return v6_sock->port;
    }
  }

  ResolvedAddressSetPort(wild4, requested_port);
  v4_sock = CreateAndPrepareListenerSocket(options, wild4);
  if (v4_sock.ok()) {
    assigned_port = v4_sock->port;
    listener_sockets.Append(*v4_sock);
  }
  if (assigned_port > 0) {
    if (!v6_sock.ok()) {
      VLOG(2) << "Failed to add :: listener, the environment may not support "
                 "IPv6: "
              << v6_sock.status();
    }
    if (!v4_sock.ok()) {
      VLOG(2) << "Failed to add 0.0.0.0 listener, "
                 "the environment may not support IPv4: "
              << v4_sock.status();
    }
    return assigned_port;
  } else {
    CHECK(!v6_sock.ok());
    CHECK(!v4_sock.ok());
    return absl::FailedPreconditionError(absl::StrCat(
        "Failed to add any wildcard listeners: ", v6_sock.status().message(),
        v4_sock.status().message()));
  }
}

#else

absl::StatusOr<ListenerSocketsContainer::ListenerSocket>
CreateAndPrepareListenerSocket(const PosixTcpOptions& ,
                               const grpc_event_engine::experimental::
                                   EventEngine::ResolvedAddress& ) {
  grpc_core::Crash(
      "CreateAndPrepareListenerSocket is not supported on this platform");
}

absl::StatusOr<int> ListenerContainerAddWildcardAddresses(
    ListenerSocketsContainer& ,
    const PosixTcpOptions& , int ) {
  grpc_core::Crash(
      "ListenerContainerAddWildcardAddresses is not supported on this "
      "platform");
}

absl::StatusOr<int> ListenerContainerAddAllLocalAddresses(
    ListenerSocketsContainer& ,
    const PosixTcpOptions& , int ) {
  grpc_core::Crash(
      "ListenerContainerAddAllLocalAddresses is not supported on this "
      "platform");
}

#endif

}
