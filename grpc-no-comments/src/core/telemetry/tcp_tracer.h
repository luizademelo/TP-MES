
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_TCP_TRACER_H
#define GRPC_SRC_CORE_TELEMETRY_TCP_TRACER_H

#include <grpc/event_engine/internal/write_event.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <optional>
#include <string>
#include <vector>

#include "absl/time/time.h"

namespace grpc_core {

struct TcpConnectionMetrics {

  std::string congestion_ctrl;

  std::optional<uint64_t> delivery_rate;

  std::optional<uint64_t> data_retx;

  std::optional<uint64_t> data_sent;

  std::optional<uint32_t> packet_retx;

  std::optional<uint32_t> packet_spurious_retx;

  std::optional<uint32_t> packet_sent;

  std::optional<uint32_t> packet_delivered;

  std::optional<uint32_t> packet_delivered_ce;

  std::optional<uint64_t> data_notsent;

  std::optional<uint32_t> min_rtt;

  std::optional<uint32_t> srtt;

  std::optional<uint32_t> ttl;

  std::optional<uint32_t> recurring_retrans;

  std::optional<int32_t> net_rtt_usec;

  std::optional<uint32_t> timeout_rehash;

  std::optional<uint32_t> ecn_rehash;

  std::optional<uint64_t> edt;

  std::optional<bool> is_delivery_rate_app_limited;

  std::optional<uint64_t> pacing_rate;

  std::optional<uint32_t> congestion_window;

  std::optional<uint32_t> reordering;

  std::optional<uint64_t> busy_usec;

  std::optional<uint64_t> rwnd_limited_usec;

  std::optional<uint64_t> sndbuf_limited_usec;

  std::optional<uint32_t> snd_ssthresh;

  std::optional<uint32_t> time_to_ack_usec;

  std::optional<uint32_t> socket_errno;

  std::optional<uint32_t> peer_rwnd;

  std::optional<uint32_t> rcvq_drops;

  std::optional<uint32_t> nic_rx_delay_usec;
};

class TcpCallTracer {
 public:
  struct TcpEventMetric {
    absl::string_view key;
    int64_t value;

    std::string ToString();
  };

  std::string TcpEventMetricsToString(
      const std::vector<TcpEventMetric>& metrics);

  virtual ~TcpCallTracer() = default;

  virtual void RecordEvent(
      grpc_event_engine::experimental::internal::WriteEvent event,
      absl::Time time, size_t byte_offset,
      std::vector<TcpEventMetric> metrics) = 0;
};

class TcpConnectionTracer {
 public:
  virtual ~TcpConnectionTracer() = default;

  virtual void RecordConnectionMetrics(TcpConnectionMetrics metrics) = 0;
};

}

#endif
