
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_SERVER_CALL_TRACER_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_SERVER_CALL_TRACER_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/resource_quota/arena.h"
#include "src/core/telemetry/call_tracer.h"

namespace grpc {
namespace internal {

class OpenCensusServerCallTracerFactory
    : public grpc_core::ServerCallTracerFactory {
 public:
  grpc_core::ServerCallTracer* CreateNewServerCallTracer(
      grpc_core::Arena* arena, const grpc_core::ChannelArgs& ) override;
};

}
}

#endif
