
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_SOCKET_UTILS_POSIX_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>

#include <cstddef>
#include <memory>
#include <utility>

#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"

#ifdef GRPC_LINUX_ERRQUEUE
#ifndef SO_ZEROCOPY
#define SO_ZEROCOPY 60
#endif
#ifndef SO_EE_ORIGIN_ZEROCOPY
#define SO_EE_ORIGIN_ZEROCOPY 5
#endif
#endif

namespace grpc_core {

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
  int dscp = kDscpNotSet;
  bool expand_wildcard_addrs = false;
  bool allow_reuse_port = false;
  RefCountedPtr<ResourceQuota> resource_quota;
  struct grpc_socket_mutator* socket_mutator = nullptr;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine;
  PosixTcpOptions() = default;

  PosixTcpOptions(PosixTcpOptions&& other) noexcept {
    socket_mutator = std::exchange(other.socket_mutator, nullptr);
    resource_quota = std::move(other.resource_quota);
    event_engine = std::move(other.event_engine);
    CopyIntegerOptions(other);
  }

  PosixTcpOptions& operator=(PosixTcpOptions&& other) noexcept {
    if (socket_mutator != nullptr) {
      grpc_socket_mutator_unref(socket_mutator);
    }
    socket_mutator = std::exchange(other.socket_mutator, nullptr);
    resource_quota = std::move(other.resource_quota);
    event_engine = std::move(other.event_engine);
    CopyIntegerOptions(other);
    return *this;
  }

  PosixTcpOptions(const PosixTcpOptions& other) {
    if (other.socket_mutator != nullptr) {
      socket_mutator = grpc_socket_mutator_ref(other.socket_mutator);
    }
    resource_quota = other.resource_quota;
    event_engine = other.event_engine;
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
    event_engine = other.event_engine;
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

}

grpc_core::PosixTcpOptions TcpOptionsFromEndpointConfig(
    const grpc_event_engine::experimental::EndpointConfig& config);

int grpc_accept4(int sockfd, grpc_resolved_address* resolved_addr, int nonblock,
                 int cloexec);

grpc_error_handle grpc_set_socket_zerocopy(int fd);

grpc_error_handle grpc_set_socket_nonblocking(int fd, int non_blocking);

grpc_error_handle grpc_set_socket_cloexec(int fd, int close_on_exec);

grpc_error_handle grpc_set_socket_reuse_addr(int fd, int reuse);

bool grpc_is_socket_reuse_port_supported();

grpc_error_handle grpc_set_socket_low_latency(int fd, int low_latency);

grpc_error_handle grpc_set_socket_reuse_port(int fd, int reuse);

grpc_error_handle grpc_set_socket_dscp(int fd, int dscp);

void config_default_tcp_user_timeout(bool enable, int timeout, bool is_client);

grpc_error_handle grpc_set_socket_tcp_user_timeout(
    int fd, const grpc_core::PosixTcpOptions& options, bool is_client);

int grpc_ipv6_loopback_available(void);

grpc_error_handle grpc_set_socket_no_sigpipe_if_possible(int fd);

grpc_error_handle grpc_set_socket_ip_pktinfo_if_possible(int fd);

grpc_error_handle grpc_set_socket_ipv6_recvpktinfo_if_possible(int fd);

grpc_error_handle grpc_set_socket_sndbuf(int fd, int buffer_size_bytes);

grpc_error_handle grpc_set_socket_rcvbuf(int fd, int buffer_size_bytes);

grpc_error_handle grpc_set_socket_with_mutator(int fd, grpc_fd_usage usage,
                                               grpc_socket_mutator* mutator);

grpc_error_handle grpc_apply_socket_mutator_in_args(
    int fd, grpc_fd_usage usage, const grpc_core::PosixTcpOptions& options);

typedef enum grpc_dualstack_mode {

  GRPC_DSMODE_NONE,

  GRPC_DSMODE_IPV4,

  GRPC_DSMODE_IPV6,

  GRPC_DSMODE_DUALSTACK
} grpc_dualstack_mode;

extern int grpc_forbid_dualstack_sockets_for_testing;

int grpc_set_socket_dualstack(int fd);

grpc_error_handle grpc_create_dualstack_socket(
    const grpc_resolved_address* addr, int type, int protocol,
    grpc_dualstack_mode* dsmode, int* newfd);

grpc_error_handle grpc_create_dualstack_socket_using_factory(
    grpc_socket_factory* factory, const grpc_resolved_address* addr, int type,
    int protocol, grpc_dualstack_mode* dsmode, int* newfd);

#endif
