
// Copyright 2015 gRPC authors.

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <grpc/support/port_platform.h>

#ifdef GPR_CPU_LINUX

#include <errno.h>
#include <grpc/support/cpu.h>
#include <grpc/support/sync.h>
#include <sched.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"

static int ncpus = 0;

static void init_num_cpus() {
#ifndef GPR_MUSL_LIBC_COMPAT
  if (sched_getcpu() < 0) {
    LOG(ERROR) << "Error determining current CPU: "
               << grpc_core::StrError(errno) << "\n";
    ncpus = 1;
    return;
  }
#endif

  ncpus = static_cast<int>(sysconf(_SC_NPROCESSORS_CONF));
  if (ncpus < 1) {
    LOG(ERROR) << "Cannot determine number of CPUs: assuming 1";
    ncpus = 1;
  }
}

unsigned gpr_cpu_num_cores(void) {
  static gpr_once once = GPR_ONCE_INIT;
  gpr_once_init(&once, init_num_cpus);
  return static_cast<unsigned>(ncpus);
}

unsigned gpr_cpu_current_cpu(void) {
#ifdef GPR_MUSL_LIBC_COMPAT

  return 0;
#else
  if (gpr_cpu_num_cores() == 1) {
    return 0;
  }
  int cpu = sched_getcpu();
  if (cpu < 0) {
    LOG(ERROR) << "Error determining current CPU: "
               << grpc_core::StrError(errno) << "\n";
    return 0;
  }
  if (static_cast<unsigned>(cpu) >= gpr_cpu_num_cores()) {
    VLOG(2) << "Cannot handle hot-plugged CPUs";
    return 0;
  }
  return static_cast<unsigned>(cpu);
#endif
}

#endif
