
// Copyright 2015 gRPC authors.

#include "src/core/lib/debug/trace.h"

namespace grpc_core {
namespace testing {

void grpc_tracer_enable_flag(TraceFlag* flag) { flag->set_enabled(true); }

}
}
