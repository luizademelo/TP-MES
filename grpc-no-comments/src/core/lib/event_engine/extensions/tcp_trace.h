// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_TCP_TRACE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_TCP_TRACE_H

#include <memory>

#include "absl/strings/string_view.h"
#include "src/core/telemetry/tcp_tracer.h"

namespace grpc_event_engine::experimental {

#define GRPC_ARG_TCP_TRACING_ENABLED "grpc.tcp_tracing_enabled"

class TcpTraceExtension {
 public:
  virtual ~TcpTraceExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.tcp_trace";
  }
  virtual void SetTcpTracer(
      std::shared_ptr<grpc_core::TcpConnectionTracer> tracer) = 0;
};

}

#endif
