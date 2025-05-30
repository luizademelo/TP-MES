
// Copyright 2015 gRPC authors.

#include "test/core/test_util/grpc_profiler.h"

#if GRPC_HAVE_PERFTOOLS
#include <gperftools/profiler.h>

void grpc_profiler_start(const char* filename) { ProfilerStart(filename); }

void grpc_profiler_stop() { ProfilerStop(); }
#else
#include "absl/log/log.h"

void grpc_profiler_start(const char* filename) {
  static int printed_warning = 0;
  if (!printed_warning) {
    VLOG(2) << "You do not have google-perftools installed, profiling is "
               "disabled [for "
            << filename << "]";
    VLOG(2) << "To install on ubuntu: sudo apt-get install google-perftools "
               "libgoogle-perftools-dev";
    printed_warning = 1;
  }
}

void grpc_profiler_stop(void) {}
#endif
