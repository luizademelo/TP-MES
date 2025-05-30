// Copyright 2025 The gRPC Authors.

#include "src/core/telemetry/default_tcp_tracer.h"

#include "src/core/util/sync.h"

namespace grpc_core {

void DefaultTcpTracer::RecordConnectionMetrics(TcpConnectionMetrics metrics) {
  MutexLock lock(&mu_);
  connection_metrics_ = metrics;
}

}
