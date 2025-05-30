
// Copyright 2015 gRPC authors.

#include <grpc/census.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/surface/call.h"

void grpc_census_call_set_context(grpc_call* call, census_context* context) {
  GRPC_TRACE_LOG(api, INFO) << "grpc_census_call_set_context(call=" << call
                            << ", census_context=" << context << ")";
  if (context != nullptr) {
    grpc_call_get_arena(call)->SetContext<census_context>(context);
  }
}

census_context* grpc_census_call_get_context(grpc_call* call) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_census_call_get_context(call=" << call << ")";
  return grpc_call_get_arena(call)->GetContext<census_context>();
}
