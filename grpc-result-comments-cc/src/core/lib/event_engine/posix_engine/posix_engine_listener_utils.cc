Here's the commented version of the code:

```c++
// Copyright 2022 The gRPC Authors

// Header file for POSIX engine listener utilities
#include "src/core/lib/event_engine/posix_engine/posix_engine_listener_utils.h"

// Standard includes
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// C++ standard library includes
#include <cstdint>
#include <cstring>
#include <string>

// Abseil includes
#include "absl/cleanup/cleanup.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_replace.h"

// gRPC internal includes
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/util/crash.h"
#include "src/core/util/status_helper.h"

// Minimum safe size for accept queue to prevent connection drops
#define MIN_SAFE_ACCEPT_QUEUE_SIZE 100

// Platform-specific includes for POSIX socket utilities
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

// Type aliases for readability
using ResolvedAddress =
    grpc_event_engine::experimental::EventEngine::ResolvedAddress;
using ListenerSocket = ListenerSocketsContainer::ListenerSocket;

#ifdef GRPC_HAVE_IFADDRS

// Finds and returns an unused port number on the system
absl::StatusOr<int> GetUnusedPort() {
  // Create a wildcard IPv6 address
  ResolvedAddress wild = ResolvedAddressMakeWild6(0);
  PosixSocketWrapper::DSMode dsmode;
  
  // Create a dual-stack socket
  auto sock = PosixSocketWrapper::CreateDualStackSocket(nullptr, wild,
                                                        SOCK_STREAM, 0, dsmode);
  GRPC_RETURN_IF_ERROR(sock.status());
  
  // If we're in IPv4-only mode, switch to IPv4 wildcard
  if (dsmode == PosixSocketWrapper::DSMode::DSMODE_IPV4) {
    wild = ResolvedAddressMakeWild4(0);
  }
  
  // Bind the socket to the wildcard address
  if (bind(sock->Fd(), wild.address(), wild.size()) != 0) {
    close(sock->Fd());
    return absl::FailedPreconditionError(
        absl::StrCat("bind(GetUnusedPort): ", std::strerror(errno)));
  }
  
  // Get the socket name to determine the assigned port
  socklen_t len = wild.size();
  if (getsockname(sock->Fd(), const_cast<sockaddr*>(wild.address()), &len) !=
      0) {
    close(sock->Fd());
    return absl::FailedPreconditionError(
        absl::StrCat("getsockname(GetUnusedPort): ", std::strerror(errno)));
  }
  
  // Clean up and return the port number
  close(sock->Fd());
  int port = ResolvedAddressGetPort(wild);
  if (port <= 0) {
    return absl::FailedPreconditionError("Bad port");
  }
  return port;
}

// Returns true if system supports ifaddrs interface
bool SystemHasIfAddrs() { return true; }

#else

// Fallback implementation when ifaddrs is not available
bool SystemHasIfAddrs() { return false; }

#endif

// Initializes and returns the maximum accept queue size by reading system settings
int InitMaxAcceptQueueSize() {
  int n = SOMAXCONN;  // Default system maximum
  char buf[64];
  
  // Try to read the system setting for maximum queue size
  FILE* fp = fopen("/proc/sys/net/core/somaxconn", "r");
  int max_accept_queue_size;
  
  if (fp == nullptr) {
    return SOMAXCONN;  // Fallback to default if file can't be opened
  }
  
  // Parse the value from the system file
  if (fgets(buf, sizeof buf, fp)) {
    char* end;
    long i = strtol(buf, &end, 10);
    if (i > 0 && i <= INT_MAX && end && *end == '\n') {
      n = static_cast<int>(i);
    }
  }
  fclose(fp);
  max_accept_queue_size = n;

  // Log a warning if the queue size seems too small
  if (max_accept_queue_size < MIN_SAFE_ACCEPT_QUEUE_SIZE) {
    LOG(INFO) << "Suspiciously small accept queue (" << max_accept_queue_size
              << ") will probably lead to connection drops";
  }
  return max_accept_queue_size;
}

// Returns the cached maximum accept queue size
int GetMaxAcceptQueueSize() {
  static const int kMaxAcceptQueueSize = InitMaxAcceptQueueSize();
  return kMaxAcceptQueueSize;
}

// Prepares a socket for listening with the given options
absl::Status PrepareSocket(const PosixTcpOptions& options,
                           ListenerSocket& socket) {
  ResolvedAddress sockname_temp;
  int fd = socket.sock.Fd();
  CHECK_GE(fd, 0);  // Ensure we have a valid file descriptor
  bool close_fd = true;
  socket.zero_copy_enabled = false;
  socket.port = 0;
  
  // Setup cleanup to close the socket if we fail
  auto sock_cleanup = absl::MakeCleanup([&close_fd, fd]() -> void {
    if (close_fd && fd >= 0) {
      close(fd);
    }
  });
  
  // Set socket options if supported and requested
  if (PosixSocketWrapper::IsSocketReusePortSupported() &&
      options.allow_reuse_port && socket.addr.address()->sa_family != AF_UNIX &&
      !ResolvedAddressIsVSock(socket.addr)) {
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketReusePort(1));
  }

#ifdef GRPC_LINUX_ERRQUEUE
  // Try to enable zero-copy if supported
  if (!socket.sock.SetSocketZeroCopy().ok()) {
    VLOG(2) << "Node does not support SO_ZEROCOPY, continuing.";
  } else {
    socket.zero_copy_enabled = true;
  }
#endif

  // Set common socket options
  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketNonBlocking(1));
  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketCloexec(1));

  // Set additional options for non-UNIX, non-VSock sockets
  if (socket.addr.address()->sa_family != AF_UNIX &&
      !ResolvedAddressIsVSock(socket.addr)) {
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketLowLatency(1));
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketReuseAddr(1));
    GRPC_RETURN_IF_ERROR(socket.sock.SetSocketDscp(options.dscp));
    socket.sock.TrySetSocketTcpUserTimeout(options, false);
  }
  
  // Set no-sigpipe option if possible
  GRPC_RETURN_IF_ERROR(socket.sock.SetSocketNoSigpipeIfPossible());
  
  // Apply any socket mutators from options
  GRPC_RETURN_IF_ERROR(socket.sock.ApplySocketMutatorInOptions(
      GRPC_FD_SERVER_LISTENER_USAGE, options));

  // Bind the socket to the address
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

  // Start listening on the socket
  if (listen(fd, GetMaxAcceptQueueSize()) < 0) {
    return absl::FailedPreconditionError(
        absl::StrCat("Error in listen: ", std::strerror(errno)));
  }
  
  // Get the socket name to determine the assigned port
  socklen_t len = static_cast<socklen_t>(sizeof(struct sockaddr_storage));
  if (getsockname(fd, const_cast<sockaddr*>(sockname_temp.address()), &len) <
      0) {
    return absl::FailedPreconditionError(
        absl::StrCat("Error in getsockname: ", std::strerror(errno)));
  }

  // Store the assigned port and prevent cleanup from closing the socket
  socket.port =
      ResolvedAddressGetPort(ResolvedAddress(sockname_temp.address(), len));
  close_fd = false;
  return absl::OkStatus();
}

}  // namespace

// Creates and prepares a listener socket with the given options and address
absl::StatusOr<ListenerSocket> CreateAndPrepareListenerSocket(
    const PosixTcpOptions& options, const ResolvedAddress& addr) {
  ResolvedAddress addr4_copy;
  ListenerSocket socket;
  
  // Create a dual-stack socket
  auto result = PosixSocketWrapper::CreateDualStackSocket(
      nullptr, addr, SOCK_STREAM, 0, socket.dsmode);
  if (!result.ok()) {
    return result.status();
  }
  socket.sock = *result;
  
  // Handle IPv4-mapped addresses if we're in IPv4-only mode
  if (socket.dsmode == PosixSocketWrapper::DSMODE_IPV4 &&
      ResolvedAddressIsV4Mapped(addr, &addr4_copy)) {
    socket.addr = addr4_copy;
  } else {
    socket.addr = addr;
  }
  
  // Prepare the socket and verify we got a valid port
  GRPC_RETURN_IF_ERROR(PrepareSocket(options, socket));
  CHECK_GT(socket.port, 0);
  return socket;
}

// Checks if the given resolved address is a link-local address
bool IsSockAddrLinkLocal(const EventEngine::ResolvedAddress* resolved_addr) {
  const sockaddr* addr = resolved_addr->address();
  
  // Check for IPv4 link-local (169.254.0.0/16)
  if (addr->sa_family == AF_INET) {
    const sockaddr_in* addr4 = reinterpret_cast<const sockaddr_in*>(addr);
    if ((addr4->sin_addr.s_addr & htonl(0xFFFF0000)) == htonl(0xA9FE0000)) {
      return true;
    }
  } 
  // Check for IPv6 link-local (fe80::/10)
  else if (addr->sa_family == AF_INET6) {
    const sockaddr_in6* addr6 = reinterpret_cast<const sockaddr_in6*>(addr);
    const uint8_t* addr_bytes = addr6->sin6_addr.s6_addr;
    if ((addr_bytes[0] == 0xfe) && ((addr_bytes[1] & 0xc0) == 0x80)) {
      return true;
    }
  }

  return false;
}

// Adds listener sockets for all local addresses on the requested port
absl::StatusOr<int> ListenerContainerAddAllLocalAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port) {
#ifdef GRPC_HAVE_IFADDRS
  absl::Status op_status = absl::OkStatus();
  struct ifaddrs* ifa = nullptr;
  struct ifaddrs* ifa_it;
  bool no_local_addresses = true;
  int assigned_port = 0;
  
  // If no port was requested, find an unused one
  if (requested_port == 0) {
    auto result = GetUnusedPort();
    GRPC_RETURN_IF_ERROR(result.status());
    requested_port = *result;
    VLOG(2) << "Picked unused port " << requested_port;
  }
  
  // Get system network interfaces
  if (getifaddrs(&ifa) != 0 || ifa == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("getifaddrs: ", std::strerror(errno)));
  }

  // Check if IPv4 is available on the system
  static const bool is_ipv4_available = [] {
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) close(fd);
    return fd >= 0;
  }();

  // Iterate through all network interfaces
  for (ifa_it = ifa; ifa_it != nullptr; ifa_it = ifa_it->ifa_next) {
    ResolvedAddress addr;
    socklen_t len;
    const char* ifa_name = (ifa_it->ifa_name ? ifa_it->ifa_name : "<unknown>");
    
    // Skip interfaces without addresses
    if (ifa_it->ifa_addr == nullptr) {
      continue;
    } 
    // Handle IPv4 addresses
    else if (ifa_it->ifa_addr->sa_family == AF_INET) {
      if (!is_ipv4_available) {
        continue;
      }
      len = static_cast<socklen_t>(sizeof(sockaddr_in));
    } 
    // Handle IPv6 addresses
    else if (ifa_it->ifa_addr->sa_family == AF_INET6) {
      len = static_cast<socklen_t>(sizeof(sockaddr_in6));
    } else {
      continue;
    }
    
    // Create resolved address and set the port
    addr = EventEngine::ResolvedAddress(ifa_it->ifa_addr, len);
    ResolvedAddressSetPort(addr, requested_port);
    std::string addr_str = *ResolvedAddressToString(addr);
    
    // Skip link-local addresses
    if (IsSockAddrLinkLocal(&addr)) {
      continue;
    }
    
    VLOG(2) << absl::StrFormat(
        "Adding local addr from interface %s flags 0x%x to server: %s",
        ifa_name, ifa_it->ifa_flags, addr_str.c_str());

    // Skip duplicate addresses
    if (listener_sockets.Find(addr).ok()) {
      VLOG(2) << "Skipping duplicate addr " << addr_str << " on interface "
              << ifa_name;
      continue;
    }
    
    // Create and prepare listener socket for this address
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
  
  // Clean up and return results
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

// Adds listener sockets for wildcard addresses (0.0.0.0 and ::)
absl::StatusOr<int> ListenerContainerAddWildcardAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port) {
  // Create wildcard addresses for IPv4 and IPv6
  ResolvedAddress wild4 = ResolvedAddressMakeWild4(requested_port);
  ResolvedAddress wild6 = ResolvedAddressMakeWild6(requested_port);
  absl::StatusOr<ListenerSocket> v6_sock;
  absl::StatusOr<ListenerSocket> v4_sock;
  int assigned_port = 0;

  // If system supports ifaddrs and we should expand wildcards, use all local addresses
  if (SystemHasIfAddrs() && options.expand_wildcard_addrs) {
    return ListenerContainerAddAllLocalAddresses(listener_sockets, options,
                                                 requested_port);
  }

  // Try to create IPv6 listener first
  v6_sock = CreateAndPrepareListenerSocket(options, wild6);
  if (v6_sock.ok()) {
    listener_sockets.Append(*v6_sock);
    requested_port = v6_sock->port;
    assigned_port = v6_sock->port;
    // If dual-stack or IPv4 mode, we don't need a separate IPv4 socket
    if (v6_sock->dsmode == PosixSocketWrapper::DSMODE_DUALSTACK ||
        v6_sock->dsmode == PosixSocketWrapper::DSMODE_IPV4) {
      return v6_sock->port;
    }
  }

  // Try to create IPv4 listener if needed
  ResolvedAddressSetPort(wild4, requested_port);
  v4_sock = CreateAndPrepareListenerSocket(options, wild4);
  if (v4_sock.ok()) {
    assigned_port = v4_sock->port;
    listener_sockets.Append(*v4_sock);
  }
  
  // Return results or errors
  if (assigned_port > 0) {
    if (!v6_sock.ok()) {
      VLOG(2