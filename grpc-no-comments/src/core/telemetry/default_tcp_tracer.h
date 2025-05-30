// Copyright 2025 The gRPC Authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_DEFAULT_TCP_TRACER_H
#define GRPC_SRC_CORE_TELEMETRY_DEFAULT_TCP_TRACER_H

#include <optional>

#include "absl/base/thread_annotations.h"
#include "absl/time/time.h"
#include "absl/types/optional.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/telemetry/tcp_tracer.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class DefaultTcpTracer final : public TcpConnectionTracer {
 public:
  explicit DefaultTcpTracer(
      std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>) {}
  ~DefaultTcpTracer() override = default;

  void RecordConnectionMetrics(TcpConnectionMetrics metrics) override;

 private:
  Mutex mu_;
  TcpConnectionMetrics connection_metrics_ ABSL_GUARDED_BY(mu_);
};

}

#endif
