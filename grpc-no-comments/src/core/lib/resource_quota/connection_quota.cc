// Copyright 2024 gRPC authors.

#include "src/core/lib/resource_quota/connection_quota.h"

#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>

#include "absl/log/check.h"

namespace grpc_core {

ConnectionQuota::ConnectionQuota() = default;

void ConnectionQuota::SetMaxIncomingConnections(int max_incoming_connections) {

  CHECK_LT(max_incoming_connections, INT_MAX);
  CHECK(max_incoming_connections_.exchange(
            max_incoming_connections, std::memory_order_release) == INT_MAX);
}

bool ConnectionQuota::AllowIncomingConnection(MemoryQuotaRefPtr mem_quota,
                                              absl::string_view ) {
  if (mem_quota->IsMemoryPressureHigh()) {
    return false;
  }

  if (max_incoming_connections_.load(std::memory_order_relaxed) == INT_MAX) {
    return true;
  }

  int curr_active_connections =
      active_incoming_connections_.load(std::memory_order_acquire);
  do {
    if (curr_active_connections >=
        max_incoming_connections_.load(std::memory_order_relaxed)) {
      return false;
    }
  } while (!active_incoming_connections_.compare_exchange_weak(
      curr_active_connections, curr_active_connections + 1,
      std::memory_order_acq_rel, std::memory_order_relaxed));
  return true;
}

void ConnectionQuota::ReleaseConnections(int num_connections) {
  if (max_incoming_connections_.load(std::memory_order_relaxed) == INT_MAX) {
    return;
  }
  CHECK(active_incoming_connections_.fetch_sub(
            num_connections, std::memory_order_acq_rel) >= num_connections);
}

}
