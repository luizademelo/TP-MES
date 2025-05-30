
// Copyright 2015 gRPC authors.

#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

#ifdef GPR_CPU_IPHONE

#include <sys/sysctl.h>

unsigned gpr_cpu_num_cores(void) {
  size_t len;
  unsigned int ncpu;
  len = sizeof(ncpu);
  sysctlbyname("hw.ncpu", &ncpu, &len, NULL, 0);

  return ncpu;
}

unsigned gpr_cpu_current_cpu(void) { return 0; }

#endif
