
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_EXAMINE_STACK_H
#define GRPC_SRC_CORE_UTIL_EXAMINE_STACK_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

namespace grpc_core {

typedef std::string (*gpr_current_stack_trace_func)();

gpr_current_stack_trace_func GetCurrentStackTraceProvider();

void SetCurrentStackTraceProvider(
    gpr_current_stack_trace_func current_stack_trace_provider);

std::optional<std::string> GetCurrentStackTrace();

}

#endif
