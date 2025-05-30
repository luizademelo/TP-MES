
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TIME_PRECISE_H
#define GRPC_SRC_CORE_UTIL_TIME_PRECISE_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#if GPR_CYCLE_COUNTER_CUSTOM
typedef int64_t gpr_cycle_counter;
gpr_cycle_counter gpr_get_cycle_counter();
#elif GPR_CYCLE_COUNTER_RDTSC_32
typedef int64_t gpr_cycle_counter;
inline gpr_cycle_counter gpr_get_cycle_counter() {
  int64_t ret;
  __asm__ volatile("rdtsc" : "=A"(ret));
  return ret;
}
#elif GPR_CYCLE_COUNTER_RDTSC_64
typedef int64_t gpr_cycle_counter;
inline gpr_cycle_counter gpr_get_cycle_counter() {
  uint64_t low, high;
  __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
  return (high << 32) | low;
}
#elif GPR_CYCLE_COUNTER_FALLBACK

typedef double gpr_cycle_counter;
gpr_cycle_counter gpr_get_cycle_counter();
#else
#error Must define exactly one of \
    GPR_CYCLE_COUNTER_RDTSC_32, \
    GPR_CYCLE_COUNTER_RDTSC_64, \
    GPR_CYCLE_COUNTER_CUSTOM, or \
    GPR_CYCLE_COUNTER_FALLBACK
#endif

void gpr_precise_clock_init(void);
void gpr_precise_clock_now(gpr_timespec* clk);
gpr_timespec gpr_cycle_counter_to_time(gpr_cycle_counter cycles);
gpr_timespec gpr_cycle_counter_sub(gpr_cycle_counter a, gpr_cycle_counter b);

#endif
