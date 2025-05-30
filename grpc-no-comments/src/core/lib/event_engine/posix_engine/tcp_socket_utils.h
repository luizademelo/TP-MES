// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TCP_SOCKET_UTILS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TCP_SOCKET_UTILS_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"

#ifdef GRPC_POSIX_SOCKET_UTILS_COMMON
#include <sys/socket.h>
#endif

#ifdef GRPC_LINUX_ERRQUEUE
#ifndef SO_ZEROCOPY
#define SO_ZEROCOPY 60
#endif
#ifndef SO_EE_ORIGIN_ZEROCOPY
#define SO_EE_ORIGIN_ZEROCOPY 5
#endif
#endif

namespace grpc_event_engine::experimental {

struct PosixTcpOptions {
  static constexpr int kDefaultReadChunkSize = 8192;
  static constexpr int kDefaultMinReadChunksize = 256;
  static constexpr int kDefaultMaxReadChunksize = 4 * 1024 * 1024;
  static constexpr int kZerocpTxEnabledDefault = 0;
  static constexpr int kMaxChunkSize = 32 * 1024 * 1024;
  static constexpr int kDefaultMaxSends = 4;
  static constexpr size_t kDefaultSendBytesThreshold = 16 * 1024;

  static constexpr int kReadBufferSizeUnset = -1;
  static constexpr int kDscpNotSet = -1;
  int tcp_read_chunk_size = kDefaultReadChunkSize;
  int tcp_min_read_chunk_size = kDefaultMinReadChunksize;
  int tcp_max_read_chunk_size = kDefaultMaxReadChunksize;
  int tcp_tx_zerocopy_send_bytes_threshold = kDefaultSendBytesThreshold;
  int tcp_tx_zerocopy_max_simultaneous_sends = kDefaultMaxSends;
  int tcp_receive_buffer_size = kReadBufferSizeUnset;
  bool tcp_tx_zero_copy_enabled = kZerocpTxEnabledDefault;
  int keep_alive_time_ms = 0;
  int keep_alive_timeout_ms = 0;
  bool expand_wildcard_addrs = false;
  bool allow_reuse_port = false;
  int dscp = kDscpNotSet;
  grpc_core::RefCountedPtr<grpc_core::ResourceQuota> resource_quota;
  struct grpc_socket_mutator* socket_mutator = nullptr;
  grpc_event_engine::experimental::MemoryAllocatorFactory*
      memory_allocator_factory = nullptr;
  PosixTcpOptions() = default;

  PosixTcpOptions(PosixTcpOptions&& other) noexcept {
    socket_mutator = std::exchange(other.socket_mutator, nullptr);
    resource_quota = std::move(other.resource_quota);
    CopyIntegerOptions(other);
  }

  PosixTcpOptions& operator=(PosixTcpOptions&& other) noexcept {
    if (socket_mutator != nullptr) {
      grpc_socket_mutator_unref(socket_mutator);
    }
    socket_mutator = std::exchange(other.socket_mutator, nullptr);
    resource_quota = std::move(other.resource_quota);
    memory_allocator_factory =
        std::exchange(other.memory_allocator_factory, nullptr);
    CopyIntegerOptions(other);
    return *this;
  }

  PosixTcpOptions(const PosixTcpOptions& other) {
    if (other.socket_mutator != nullptr) {
      socket_mutator = grpc_socket_mutator_ref(other.socket_mutator);
    }
    resource_quota = other.resource_quota;
    memory_allocator_factory = other.memory_allocator_factory;
    CopyIntegerOptions(other);
  }

  PosixTcpOptions& operator=(const PosixTcpOptions& other) {
    if (&other == this) {
      return *this;
    }
    if (socket_mutator != nullptr) {
      grpc_socket_mutator_unref(socket_mutator);
      socket_mutator = nullptr;
    }
    if (other.socket_mutator != nullptr) {
      socket_mutator = grpc_socket_mutator_ref(other.socket_mutator);
    }
    resource_quota = other.resource_quota;
    memory_allocator_factory = other.memory_allocator_factory;
    CopyIntegerOptions(other);
    return *this;
  }

  ~PosixTcpOptions() {
    if (socket_mutator != nullptr) {
      grpc_socket_mutator_unref(socket_mutator);
    }
  }

 private:
  void CopyIntegerOptions(const PosixTcpOptions& other) {
    tcp_read_chunk_size = other.tcp_read_chunk_size;
    tcp_min_read_chunk_size = other.tcp_min_read_chunk_size;
    tcp_max_read_chunk_size = other.tcp_max_read_chunk_size;
    tcp_tx_zerocopy_send_bytes_threshold =
        other.tcp_tx_zerocopy_send_bytes_threshold;
    tcp_tx_zerocopy_max_simultaneous_sends =
        other.tcp_tx_zerocopy_max_simultaneous_sends;
    tcp_tx_zero_copy_enabled = other.tcp_tx_zero_copy_enabled;
    keep_alive_time_ms = other.keep_alive_time_ms;
    keep_alive_timeout_ms = other.keep_alive_timeout_ms;
    expand_wildcard_addrs = other.expand_wildcard_addrs;
    allow_reuse_port = other.allow_reuse_port;
    dscp = other.dscp;
  }
};

PosixTcpOptions TcpOptionsFromEndpointConfig(
    const grpc_event_engine::experimental::EndpointConfig& config);

int Accept4(int sockfd,
            grpc_event_engine::experimental::EventEngine::ResolvedAddress& addr,
            int nonblock, int cloexec);

void UnlinkIfUnixDomainSocket(
    const EventEngine::ResolvedAddress& resolved_addr);

class PosixSocketWrapper {
 public:
  explicit PosixSocketWrapper(int fd) : fd_(fd) { CHECK_GT(fd_, 0); }

  PosixSocketWrapper() : fd_(-1) {};

  ~PosixSocketWrapper() = default;

  absl::StatusOr<int> SetSocketRcvLowat(int bytes);

  absl::Status SetSocketZeroCopy();

  absl::Status SetSocketNonBlocking(int non_blocking);

  absl::Status SetSocketCloexec(int close_on_exec);

  absl::Status SetSocketReuseAddr(int reuse);

  absl::Status SetSocketLowLatency(int low_latency);

  absl::Status SetSocketReusePort(int reuse);

  absl::Status SetSocketDscp(int dscp);

  void TrySetSocketTcpUserTimeout(const PosixTcpOptions& options,
                                  bool is_client);

  absl::Status SetSocketNoSigpipeIfPossible();

  absl::Status SetSocketIpPktInfoIfPossible();

  absl::Status SetSocketIpv6RecvPktInfoIfPossible();

  absl::Status SetSocketSndBuf(int buffer_size_bytes);

  absl::Status SetSocketRcvBuf(int buffer_size_bytes);

  absl::Status SetSocketMutator(grpc_fd_usage usage,
                                grpc_socket_mutator* mutator);

  absl::Status ApplySocketMutatorInOptions(grpc_fd_usage usage,
                                           const PosixTcpOptions& options);

  absl::StatusOr<EventEngine::ResolvedAddress> LocalAddress();

  absl::StatusOr<EventEngine::ResolvedAddress> PeerAddress();

  absl::StatusOr<std::string> LocalAddressString();

  absl::StatusOr<std::string> PeerAddressString();

  enum DSMode {

    DSMODE_NONE,

    DSMODE_IPV4,

    DSMODE_IPV6,

    DSMODE_DUALSTACK
  };

  int Fd() const { return fd_; }

  static void ConfigureDefaultTcpUserTimeout(bool enable, int timeout,
                                             bool is_client);

  static bool IsSocketReusePortSupported();

  static bool IsIpv6LoopbackAvailable();

  static absl::StatusOr<PosixSocketWrapper> CreateDualStackSocket(
      std::function<int(int , int , int )>
          socket_factory,
      const experimental::EventEngine::ResolvedAddress& addr, int type,
      int protocol, DSMode& dsmode);

  struct PosixSocketCreateResult;

  static absl::StatusOr<PosixSocketCreateResult>
  CreateAndPrepareTcpClientSocket(
      const PosixTcpOptions& options,
      const EventEngine::ResolvedAddress& target_addr);

 private:
  int fd_;
};

struct PosixSocketWrapper::PosixSocketCreateResult {
  PosixSocketWrapper sock;
  EventEngine::ResolvedAddress mapped_target_addr;
};

bool SetSocketDualStack(int fd);

}

#endif
