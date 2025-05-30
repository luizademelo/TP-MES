
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_TRACER_UTIL_H
#define GRPC_TEST_CORE_TEST_UTIL_TRACER_UTIL_H

namespace grpc_core {
class TraceFlag;

namespace testing {

void grpc_tracer_enable_flag(TraceFlag* flag);

}
}

#endif
