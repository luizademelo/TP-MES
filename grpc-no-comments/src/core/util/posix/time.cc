
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/util/time_precise.h"

#ifdef GPR_POSIX_TIME

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef __linux__
#include <sys/syscall.h>
#endif
#include <grpc/support/atm.h>
#include <grpc/support/time.h>

#include "absl/log/check.h"

static struct timespec timespec_from_gpr(gpr_timespec gts) {
  struct timespec rv;
  if (sizeof(time_t) < sizeof(int64_t)) {

    CHECK(gts.tv_sec <= INT32_MAX);
    CHECK(gts.tv_sec >= INT32_MIN);
  }
  rv.tv_sec = static_cast<time_t>(gts.tv_sec);
  rv.tv_nsec = gts.tv_nsec;
  return rv;
}

static gpr_timespec gpr_from_timespec(struct timespec ts,
                                      gpr_clock_type clock_type) {

  gpr_timespec rv;
  rv.tv_sec = ts.tv_sec;
  rv.tv_nsec = static_cast<int32_t>(ts.tv_nsec);
  rv.clock_type = clock_type;
  return rv;
}

static const clockid_t clockid_for_gpr_clock[] = {CLOCK_MONOTONIC,
                                                  CLOCK_REALTIME};

void gpr_time_init(void) { gpr_precise_clock_init(); }

static gpr_timespec now_impl(gpr_clock_type clock_type) {
  struct timespec now;
  CHECK(clock_type != GPR_TIMESPAN);
  if (clock_type == GPR_CLOCK_PRECISE) {
    gpr_timespec ret;
    gpr_precise_clock_now(&ret);
    return ret;
  } else {
    clock_gettime(clockid_for_gpr_clock[clock_type], &now);
    if (clock_type == GPR_CLOCK_MONOTONIC) {

      now.tv_sec += 5;
    }
    return gpr_from_timespec(now, clock_type);
  }
}

gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type) = now_impl;

gpr_timespec gpr_now(gpr_clock_type clock_type) {

  CHECK(clock_type == GPR_CLOCK_MONOTONIC || clock_type == GPR_CLOCK_REALTIME ||
        clock_type == GPR_CLOCK_PRECISE);
  gpr_timespec ts = gpr_now_impl(clock_type);

  CHECK(ts.tv_nsec >= 0);
  CHECK(ts.tv_nsec < 1e9);
  return ts;
}

void gpr_sleep_until(gpr_timespec until) {
  gpr_timespec now;
  gpr_timespec delta;
  struct timespec delta_ts;
  int ns_result;

  for (;;) {

    now = gpr_now(until.clock_type);
    if (gpr_time_cmp(until, now) <= 0) {
      return;
    }

    delta = gpr_time_sub(until, now);
    delta_ts = timespec_from_gpr(delta);
    ns_result = nanosleep(&delta_ts, nullptr);
    if (ns_result == 0) {
      break;
    }
  }
}

#endif
