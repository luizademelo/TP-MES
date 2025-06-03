Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Core utilities for time management in gRPC
#include "src/core/util/time.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <atomic>
#include <chrono>
#include <limits>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {

namespace {
// Global variables to store process start time in seconds and CPU cycles
std::atomic<int64_t> g_process_epoch_seconds;
std::atomic<gpr_cycle_counter> g_process_epoch_cycles;

// Time source implementation that uses gpr_now() as its time source
class GprNowTimeSource final : public Timestamp::Source {
 public:
  // Gets current timestamp using gpr_now() with monotonic clock
  Timestamp Now() override {
    return Timestamp::FromTimespecRoundDown(gpr_now(GPR_CLOCK_MONOTONIC));
  }
};

// Initializes and returns the process start time in seconds and cycles
// Uses a 21-iteration loop to get stable measurements
GPR_ATTRIBUTE_NOINLINE std::pair<int64_t, gpr_cycle_counter> InitTime() {
  gpr_cycle_counter cycles_start = 0;
  gpr_cycle_counter cycles_end = 0;
  int64_t process_epoch_seconds = 0;

  // Attempt to get a stable time measurement
  for (int i = 0; i < 21; i++) {
    cycles_start = gpr_get_cycle_counter();
    gpr_timespec now = gpr_now(GPR_CLOCK_MONOTONIC);
    cycles_end = gpr_get_cycle_counter();
    process_epoch_seconds = now.tv_sec;
    if (process_epoch_seconds > 1) {
      break;
    }
    LOG(INFO) << "gpr_now(GPR_CLOCK_MONOTONIC) returns a very small number: "
                 "sleeping for 100ms";
    gpr_sleep_until(gpr_time_add(now, gpr_time_from_millis(100, GPR_TIMESPAN)));
  }

  // Ensure we got a valid time measurement
  CHECK_GT(process_epoch_seconds, 1);

  // Store the process epoch time (1 second before first measurement)
  process_epoch_seconds -= 1;
  int64_t expected = 0;
  gpr_cycle_counter process_epoch_cycles = (cycles_start + cycles_end) / 2;
  CHECK_NE(process_epoch_cycles, 0);
  // Atomically store the values if they haven't been set yet
  if (!g_process_epoch_seconds.compare_exchange_strong(
          expected, process_epoch_seconds, std::memory_order_relaxed,
          std::memory_order_relaxed)) {
    process_epoch_seconds = expected;
    do {
      process_epoch_cycles =
          g_process_epoch_cycles.load(std::memory_order_relaxed);
    } while (process_epoch_cycles == 0);
  } else {
    g_process_epoch_cycles.store(process_epoch_cycles,
                                 std::memory_order_relaxed);
  }
  return std::pair(process_epoch_seconds, process_epoch_cycles);
}

// Returns the process start time in timespec format
gpr_timespec StartTime() {
  int64_t sec = g_process_epoch_seconds.load(std::memory_order_relaxed);
  if (GPR_UNLIKELY(sec == 0)) sec = InitTime().first;
  return {sec, 0, GPR_CLOCK_MONOTONIC};
}

// Returns the process start time in CPU cycles
gpr_cycle_counter StartCycleCounter() {
  gpr_cycle_counter cycles =
      g_process_epoch_cycles.load(std::memory_order_relaxed);
  if (GPR_UNLIKELY(cycles == 0)) cycles = InitTime().second;
  return cycles;
}

// Converts milliseconds to timespec, handling infinity cases
gpr_timespec MillisecondsAsTimespec(int64_t millis, gpr_clock_type clock_type) {
  // Handle special cases for maximum and minimum values
  if (millis == std::numeric_limits<int64_t>::max()) {
    return gpr_inf_future(clock_type);
  }
  if (millis == std::numeric_limits<int64_t>::min()) {
    return gpr_inf_past(clock_type);
  }

  // Convert milliseconds to timespec
  if (clock_type == GPR_TIMESPAN) {
    return gpr_time_from_millis(millis, GPR_TIMESPAN);
  }
  return gpr_time_add(gpr_convert_clock_type(StartTime(), clock_type),
                      gpr_time_from_millis(millis, GPR_TIMESPAN));
}

// Converts timespan to milliseconds with rounding up
int64_t TimespanToMillisRoundUp(gpr_timespec ts) {
  CHECK(ts.clock_type == GPR_TIMESPAN);
  double x = GPR_MS_PER_SEC * static_cast<double>(ts.tv_sec) +
             (static_cast<double>(ts.tv_nsec) / GPR_NS_PER_MS) +
             (static_cast<double>(GPR_NS_PER_SEC - 1) /
              static_cast<double>(GPR_NS_PER_SEC));
  // Handle potential overflow
  if (x <= static_cast<double>(std::numeric_limits<int64_t>::min())) {
    return std::numeric_limits<int64_t>::min();
  }
  if (x >= static_cast<double>(std::numeric_limits<int64_t>::max())) {
    return std::numeric_limits<int64_t>::max();
  }
  return static_cast<int64_t>(x);
}

// Converts timespan to milliseconds with rounding down
int64_t TimespanToMillisRoundDown(gpr_timespec ts) {
  CHECK(ts.clock_type == GPR_TIMESPAN);
  double x = GPR_MS_PER_SEC * static_cast<double>(ts.tv_sec) +
             (static_cast<double>(ts.tv_nsec) / GPR_NS_PER_MS);
  // Handle potential overflow
  if (x <= static_cast<double>(std::numeric_limits<int64_t>::min())) {
    return std::numeric_limits<int64_t>::min();
  }
  if (x >= static_cast<double>(std::numeric_limits<int64_t>::max())) {
    return std::numeric_limits<int64_t>::max();
  }
  return static_cast<int64_t>(x);
}

}  // namespace

// Thread-local time source initialized to use gpr_now()
thread_local Timestamp::Source* Timestamp::thread_local_time_source_{
    NoDestructSingleton<GprNowTimeSource>::Get()};

// Gets current time from cache or underlying time source if not cached
Timestamp ScopedTimeCache::Now() {
  if (!cached_time_.has_value()) {
    previous()->InvalidateCache();
    cached_time_ = previous()->Now();
  }
  return cached_time_.value();
}

// Creates Timestamp from timespec with rounding up
Timestamp Timestamp::FromTimespecRoundUp(gpr_timespec ts) {
  return FromMillisecondsAfterProcessEpoch(TimespanToMillisRoundUp(gpr_time_sub(
      gpr_convert_clock_type(ts, GPR_CLOCK_MONOTONIC), StartTime())));
}

// Creates Timestamp from timespec with rounding down
Timestamp Timestamp::FromTimespecRoundDown(gpr_timespec ts) {
  return FromMillisecondsAfterProcessEpoch(
      TimespanToMillisRoundDown(gpr_time_sub(
          gpr_convert_clock_type(ts, GPR_CLOCK_MONOTONIC), StartTime())));
}

// Creates Timestamp from cycle counter with rounding up
Timestamp Timestamp::FromCycleCounterRoundUp(gpr_cycle_counter c) {
  return Timestamp::FromMillisecondsAfterProcessEpoch(
      TimespanToMillisRoundUp(gpr_cycle_counter_sub(c, StartCycleCounter())));
}

// Creates Timestamp from cycle counter with rounding down
Timestamp Timestamp::FromCycleCounterRoundDown(gpr_cycle_counter c) {
  return Timestamp::FromMillisecondsAfterProcessEpoch(
      TimespanToMillisRoundDown(gpr_cycle_counter_sub(c, StartCycleCounter())));
}

// Converts Timestamp to timespec in specified clock type
gpr_timespec Timestamp::as_timespec(gpr_clock_type clock_type) const {
  return MillisecondsAsTimespec(millis_, clock_type);
}

// Returns string representation of Timestamp
std::string Timestamp::ToString() const {
  if (millis_ == std::numeric_limits<int64_t>::max()) {
    return "@∞";
  }
  if (millis_ == std::numeric_limits<int64_t>::min()) {
    return "@-∞";
  }
  return "@" + std::to_string(millis_) + "ms";
}

// Converts Duration to timespec
gpr_timespec Duration::as_timespec() const {
  return MillisecondsAsTimespec(millis_, GPR_TIMESPAN);
}

// Creates Duration from timespec
Duration Duration::FromTimespec(gpr_timespec t) {
  return Duration::Milliseconds(TimespanToMillisRoundUp(t));
}

// Returns string representation of Duration
std::string Duration::ToString() const {
  if (millis_ == std::numeric_limits<int64_t>::max()) {
    return "∞";
  }
  if (millis_ == std::numeric_limits<int64_t>::min()) {
    return "-∞";
  }
  return std::to_string(millis_) + "ms";
}

// Returns JSON string representation of Duration
std::string Duration::ToJsonString() const {
  gpr_timespec ts = as_timespec();
  return absl::StrFormat("%d.%09ds", ts.tv_sec, ts.tv_nsec);
}

// Converts Duration to EventEngine::Duration
Duration::operator grpc_event_engine::experimental::EventEngine::Duration()
    const {
  return std::chrono::milliseconds(
      Clamp(millis_, std::numeric_limits<int64_t>::min() / GPR_NS_PER_MS,
            std::numeric_limits<int64_t>::max() / GPR_NS_PER_MS));
}

// For testing only: sets the process epoch time
void TestOnlySetProcessEpoch(gpr_timespec epoch) {
  g_process_epoch_seconds.store(
      gpr_convert_clock_type(epoch, GPR_CLOCK_MONOTONIC).tv_sec);
  g_process_epoch_cycles.store(gpr_get_cycle_counter());
}

// Output operator for Timestamp
std::ostream& operator<<(std::ostream& out, Timestamp timestamp) {
  return out << timestamp.ToString();
}

// Output operator for Duration
std::ostream& operator<<(std::ostream& out, Duration duration) {
  return out << duration.ToString();
}

}  // namespace grpc_core
```