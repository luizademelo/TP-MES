
// Copyright 2015 gRPC authors.

#include <grpc/support/time.h>
#include <grpcpp/support/time.h>

#include <chrono>
#include <cstdint>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace grpc {

void Timepoint2Timespec(const system_clock::time_point& from,
                        gpr_timespec* to) {
  system_clock::duration deadline = from.time_since_epoch();
  seconds secs = duration_cast<seconds>(deadline);
  if (from == system_clock::time_point::max() ||
      secs.count() >= gpr_inf_future(GPR_CLOCK_REALTIME).tv_sec ||
      secs.count() < 0) {
    *to = gpr_inf_future(GPR_CLOCK_REALTIME);
    return;
  }
  nanoseconds nsecs = duration_cast<nanoseconds>(deadline - secs);
  to->tv_sec = static_cast<int64_t>(secs.count());
  to->tv_nsec = static_cast<int32_t>(nsecs.count());
  to->clock_type = GPR_CLOCK_REALTIME;
}

void TimepointHR2Timespec(const high_resolution_clock::time_point& from,
                          gpr_timespec* to) {
  high_resolution_clock::duration deadline = from.time_since_epoch();
  seconds secs = duration_cast<seconds>(deadline);
  if (from == high_resolution_clock::time_point::max() ||
      secs.count() >= gpr_inf_future(GPR_CLOCK_REALTIME).tv_sec ||
      secs.count() < 0) {
    *to = gpr_inf_future(GPR_CLOCK_REALTIME);
    return;
  }
  nanoseconds nsecs = duration_cast<nanoseconds>(deadline - secs);
  to->tv_sec = static_cast<int64_t>(secs.count());
  to->tv_nsec = static_cast<int32_t>(nsecs.count());
  to->clock_type = GPR_CLOCK_REALTIME;
}

system_clock::time_point Timespec2Timepoint(gpr_timespec t) {
  if (gpr_time_cmp(t, gpr_inf_future(t.clock_type)) == 0) {
    return system_clock::time_point::max();
  }
  t = gpr_convert_clock_type(t, GPR_CLOCK_REALTIME);
  system_clock::time_point tp;
  tp += duration_cast<system_clock::time_point::duration>(seconds(t.tv_sec));
  tp +=
      duration_cast<system_clock::time_point::duration>(nanoseconds(t.tv_nsec));
  return tp;
}

}
