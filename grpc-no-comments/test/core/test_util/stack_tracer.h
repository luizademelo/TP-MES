
// Copyright 2020 the gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_STACK_TRACER_H
#define GRPC_TEST_CORE_TEST_UTIL_STACK_TRACER_H

#include <grpc/support/port_platform.h>

#include <string>

namespace grpc_core {
namespace testing {

std::string GetCurrentStackTrace();

void InitializeStackTracer(const char* argv0);

}
}

#endif
