// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_CONNECTION_QUOTA_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_CONNECTION_QUOTA_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <limits>

#include "absl/base/thread_annotations.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class ConnectionQuota : public RefCounted<ConnectionQuota> {
 public:
  ConnectionQuota();
  ~ConnectionQuota() override = default;

  ConnectionQuota(const ConnectionQuota&) = delete;
  ConnectionQuota& operator=(const ConnectionQuota&) = delete;

  void SetMaxIncomingConnections(int max_incoming_connections);

  bool AllowIncomingConnection(MemoryQuotaRefPtr mem_quota,
                               absl::string_view peer);

  void ReleaseConnections(int num_connections);

  int TestOnlyActiveIncomingConnections() const {
    return active_incoming_connections_;
  }

 private:
  std::atomic<int> active_incoming_connections_{0};
  std::atomic<int> max_incoming_connections_{std::numeric_limits<int>::max()};
};

using ConnectionQuotaRefPtr = RefCountedPtr<ConnectionQuota>;

}

#endif
