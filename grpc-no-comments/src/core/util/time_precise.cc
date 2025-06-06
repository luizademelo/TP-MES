
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#if GPR_LINUX
#include <fcntl.h>
#include <unistd.h>
#endif

#include <grpc/support/time.h>

#include <algorithm>

#include "absl/log/log.h"
#include "src/core/util/time_precise.h"

#ifndef GPR_CYCLE_COUNTER_CUSTOM
#if GPR_CYCLE_COUNTER_RDTSC_32 || GPR_CYCLE_COUNTER_RDTSC_64
#if GPR_LINUX
static bool read_freq_from_kernel(double* freq) {

  int fd = open("/sys/devices/system/cpu/cpu0/tsc_freq_khz", O_RDONLY);
  if (fd == -1) {
    return false;
  }
  char line[1024] = {};
  char* err;
  bool ret = false;
  int len = read(fd, line, sizeof(line) - 1);
  if (len > 0) {
    const long val = strtol(line, &err, 10);
    if (line[0] != '\0' && (*err == '\n' || *err == '\0')) {
      *freq = val * 1e3;
      ret = true;
    }
  }
  close(fd);
  return ret;
}
#endif

static double cycles_per_second = 0;
static gpr_cycle_counter start_cycle;

static bool is_fake_clock() {
  gpr_timespec start = gpr_now(GPR_CLOCK_MONOTONIC);
  int64_t sum = 0;
  for (int i = 0; i < 8; ++i) {
    gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
    gpr_timespec delta = gpr_time_sub(now, start);
    sum += delta.tv_sec * GPR_NS_PER_SEC + delta.tv_nsec;
  }

  return sum == 0;
}

void gpr_precise_clock_init(void) {
  VLOG(2) << "Calibrating timers";

#if GPR_LINUX
  if (read_freq_from_kernel(&cycles_per_second)) {
    start_cycle = gpr_get_cycle_counter();
    return;
  }
#endif

  if (is_fake_clock()) {
    cycles_per_second = 1;
    start_cycle = 0;
    return;
  }

  int64_t measurement_ns = GPR_NS_PER_MS;
  double last_freq = -1;
  bool converged = false;
  for (int i = 0; i < 8 && !converged; ++i, measurement_ns *= 2) {
    start_cycle = gpr_get_cycle_counter();
    int64_t loop_ns;
    gpr_timespec start = gpr_now(GPR_CLOCK_MONOTONIC);
    do {

      gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
      gpr_timespec delta = gpr_time_sub(now, start);
      loop_ns = delta.tv_sec * GPR_NS_PER_SEC + delta.tv_nsec;
    } while (loop_ns < measurement_ns);
    gpr_cycle_counter end_cycle = gpr_get_cycle_counter();

    const double freq =
        static_cast<double>(end_cycle - start_cycle) / loop_ns * GPR_NS_PER_SEC;
    converged =
        last_freq != -1 && (freq * 0.99 < last_freq && last_freq < freq * 1.01);
    last_freq = freq;
  }
  cycles_per_second = last_freq;
  VLOG(2) << "... cycles_per_second = " << cycles_per_second << "\n";
}

gpr_timespec gpr_cycle_counter_to_time(gpr_cycle_counter cycles) {
  const double secs =
      static_cast<double>(cycles - start_cycle) / cycles_per_second;
  gpr_timespec ts;
  ts.tv_sec = static_cast<int64_t>(secs);
  ts.tv_nsec = static_cast<int32_t>(GPR_NS_PER_SEC *
                                    (secs - static_cast<double>(ts.tv_sec)));
  ts.clock_type = GPR_CLOCK_PRECISE;
  return ts;
}

gpr_timespec gpr_cycle_counter_sub(gpr_cycle_counter a, gpr_cycle_counter b) {
  const double secs = static_cast<double>(a - b) / cycles_per_second;
  gpr_timespec ts;
  ts.tv_sec = static_cast<int64_t>(secs);
  ts.tv_nsec = static_cast<int32_t>(GPR_NS_PER_SEC *
                                    (secs - static_cast<double>(ts.tv_sec)));
  ts.clock_type = GPR_TIMESPAN;
  return ts;
}

void gpr_precise_clock_now(gpr_timespec* clk) {
  int64_t counter = gpr_get_cycle_counter();
  *clk = gpr_cycle_counter_to_time(counter);
}
#elif GPR_CYCLE_COUNTER_FALLBACK
void gpr_precise_clock_init(void) {}

gpr_cycle_counter gpr_get_cycle_counter() {
  gpr_timespec ts = gpr_now(GPR_CLOCK_REALTIME);
  return gpr_timespec_to_micros(ts);
}

gpr_timespec gpr_cycle_counter_to_time(gpr_cycle_counter cycles) {
  gpr_timespec ts;
  ts.tv_sec = static_cast<int64_t>(cycles / GPR_US_PER_SEC);
  ts.tv_nsec = static_cast<int64_t>((cycles - ts.tv_sec * GPR_US_PER_SEC) *
                                    GPR_NS_PER_US);
  ts.clock_type = GPR_CLOCK_PRECISE;
  return ts;
}

void gpr_precise_clock_now(gpr_timespec* clk) {
  *clk = gpr_now(GPR_CLOCK_REALTIME);
  clk->clock_type = GPR_CLOCK_PRECISE;
}

gpr_timespec gpr_cycle_counter_sub(gpr_cycle_counter a, gpr_cycle_counter b) {
  return gpr_time_sub(gpr_cycle_counter_to_time(a),
                      gpr_cycle_counter_to_time(b));
}
#endif
#endif
