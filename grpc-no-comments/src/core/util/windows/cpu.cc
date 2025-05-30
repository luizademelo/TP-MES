
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS
#include <grpc/support/cpu.h>

#include "src/core/util/crash.h"

unsigned gpr_cpu_num_cores(void) {
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  return si.dwNumberOfProcessors;
}

unsigned gpr_cpu_current_cpu(void) { return GetCurrentProcessorNumber(); }

#endif
