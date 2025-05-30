
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS_TIME

#include <grpc/support/time.h>
#include <limits.h>
#include <process.h>
#include <sys/timeb.h>

#include "absl/log/check.h"
#include "src/core/util/time_precise.h"

static LARGE_INTEGER g_start_time = []() {
  LARGE_INTEGER x;
  QueryPerformanceCounter(&x);
  return x;
}();
static double g_time_scale = []() {
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);
  return 1.0 / (double)frequency.QuadPart;
}();

void gpr_time_init(void) {}

static gpr_timespec now_impl(gpr_clock_type clock) {
  gpr_timespec now_tv;
  LONGLONG diff;
  struct _timeb now_tb;
  LARGE_INTEGER timestamp;
  double now_dbl;
  now_tv.clock_type = clock;
  switch (clock) {
    case GPR_CLOCK_REALTIME:
      _ftime_s(&now_tb);
      now_tv.tv_sec = (int64_t)now_tb.time;
      now_tv.tv_nsec = now_tb.millitm * 1000000;
      break;
    case GPR_CLOCK_MONOTONIC:
    case GPR_CLOCK_PRECISE:
      QueryPerformanceCounter(&timestamp);
      diff = timestamp.QuadPart - g_start_time.QuadPart;

      now_dbl = 5.0 + (double)diff * g_time_scale;
      now_tv.tv_sec = (int64_t)now_dbl;
      now_tv.tv_nsec = (int32_t)((now_dbl - (double)now_tv.tv_sec) * 1e9);
      break;
    case GPR_TIMESPAN:
      abort();
      break;
  }
  return now_tv;
}

gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type) = now_impl;

gpr_timespec gpr_now(gpr_clock_type clock_type) {
  return gpr_now_impl(clock_type);
}

void gpr_sleep_until(gpr_timespec until) {
  gpr_timespec now;
  gpr_timespec delta;
  int64_t sleep_millis;

  for (;;) {

    now = gpr_now(until.clock_type);
    if (gpr_time_cmp(until, now) <= 0) {
      return;
    }

    delta = gpr_time_sub(until, now);
    sleep_millis =
        delta.tv_sec * GPR_MS_PER_SEC + delta.tv_nsec / GPR_NS_PER_MS;
    CHECK_GE(sleep_millis, 0);
    CHECK_LE(sleep_millis, INT_MAX);
    Sleep((DWORD)sleep_millis);
  }
}

#endif
