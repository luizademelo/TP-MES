
// Copyright 2020 gRPC authors.

#include "src/core/util/examine_stack.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

gpr_current_stack_trace_func g_current_stack_trace_provider = nullptr;

gpr_current_stack_trace_func GetCurrentStackTraceProvider() {
  return g_current_stack_trace_provider;
}

void SetCurrentStackTraceProvider(
    gpr_current_stack_trace_func current_stack_trace_provider) {
  g_current_stack_trace_provider = current_stack_trace_provider;
}

std::optional<std::string> GetCurrentStackTrace() {
  if (g_current_stack_trace_provider != nullptr) {
    return g_current_stack_trace_provider();
  }
  return std::nullopt;
}

}
