Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "absl/log/check.h"

// Compares two gpr_timespec values
// Returns:
//   -1 if a < b
//    0 if a == b
//    1 if a > b
int gpr_time_cmp(gpr_timespec a, gpr_timespec b) {
  int cmp = (a.tv_sec > b.tv_sec) - (a.tv_sec < b.tv_sec);
  CHECK(a.clock_type == b.clock_type);  // Ensure clock types match
  if (cmp == 0 && a.tv_sec != INT64_MAX && a.tv_sec != INT64_MIN) {
    // If seconds are equal and not at min/max bounds, compare nanoseconds
    cmp = (a.tv_nsec > b.tv_nsec) - (a.tv_nsec < b.tv_nsec);
  }
  return cmp;
}

// Returns the minimum of two gpr_timespec values
gpr_timespec gpr_time_min(gpr_timespec a, gpr_timespec b) {
  return gpr_time_cmp(a, b) < 0 ? a : b;
}

// Returns the maximum of two gpr_timespec values
gpr_timespec gpr_time_max(gpr_timespec a, gpr_timespec b) {
  return gpr_time_cmp(a, b) > 0 ? a : b;
}

// Creates a zero time value with specified clock type
gpr_timespec gpr_time_0(gpr_clock_type type) {
  gpr_timespec out;
  out.tv_sec = 0;
  out.tv_nsec = 0;
  out.clock_type = type;
  return out;
}

// Creates a time value representing infinite future with specified clock type
gpr_timespec gpr_inf_future(gpr_clock_type type) {
  gpr_timespec out;
  out.tv_sec = INT64_MAX;
  out.tv_nsec = 0;
  out.clock_type = type;
  return out;
}

// Creates a time value representing infinite past with specified clock type
gpr_timespec gpr_inf_past(gpr_clock_type type) {
  gpr_timespec out;
  out.tv_sec = INT64_MIN;
  out.tv_nsec = 0;
  out.clock_type = type;
  return out;
}

// Converts sub-second units (like nanoseconds) to gpr_timespec
// Handles special cases for INT64_MAX (inf future) and INT64_MIN (inf past)
static gpr_timespec to_seconds_from_sub_second_time(int64_t time_in_units,
                                                    int64_t units_per_sec,
                                                    gpr_clock_type type) {
  gpr_timespec out;
  if (time_in_units == INT64_MAX) {
    out = gpr_inf_future(type);
  } else if (time_in_units == INT64_MIN) {
    out = gpr_inf_past(type);
  } else {
    DCHECK_EQ(GPR_NS_PER_SEC % units_per_sec, 0);  // Ensure clean division

    out.tv_sec = time_in_units / units_per_sec;
    out.tv_nsec =
        static_cast<int32_t>((time_in_units - (out.tv_sec * units_per_sec)) *
        (GPR_NS_PER_SEC / units_per_sec);

    // Handle negative nanoseconds
    if (out.tv_nsec < 0) {
      out.tv_nsec += GPR_NS_PER_SEC;
      out.tv_sec--;
    }

    out.clock_type = type;
  }
  return out;
}

// Converts above-second units (like hours) to gpr_timespec
// Handles overflow cases by returning infinite future/past
static gpr_timespec to_seconds_from_above_second_time(int64_t time_in_units,
                                                      int64_t secs_per_unit,
                                                      gpr_clock_type type) {
  gpr_timespec out;
  if (time_in_units >= INT64_MAX / secs_per_unit) {
    out = gpr_inf_future(type);
  } else if (time_in_units <= INT64_MIN / secs_per_unit) {
    out = gpr_inf_past(type);
  } else {
    out.tv_sec = time_in_units * secs_per_unit;
    out.tv_nsec = 0;
    out.clock_type = type;
  }
  return out;
}

// Conversion functions from various time units to gpr_timespec
gpr_timespec gpr_time_from_nanos(int64_t ns, gpr_clock_type clock_type) {
  return to_seconds_from_sub_second_time(ns, GPR_NS_PER_SEC, clock_type);
}

gpr_timespec gpr_time_from_micros(int64_t us, gpr_clock_type clock_type) {
  return to_seconds_from_sub_second_time(us, GPR_US_PER_SEC, clock_type);
}

gpr_timespec gpr_time_from_millis(int64_t ms, gpr_clock_type clock_type) {
  return to_seconds_from_sub_second_time(ms, GPR_MS_PER_SEC, clock_type);
}

gpr_timespec gpr_time_from_seconds(int64_t s, gpr_clock_type clock_type) {
  return to_seconds_from_sub_second_time(s, 1, clock_type);
}

gpr_timespec gpr_time_from_minutes(int64_t m, gpr_clock_type clock_type) {
  return to_seconds_from_above_second_time(m, 60, clock_type);
}

gpr_timespec gpr_time_from_hours(int64_t h, gpr_clock_type clock_type) {
  return to_seconds_from_above_second_time(h, 3600, clock_type);
}

// Adds two time values (b must be a timespan)
// Handles overflow/underflow cases by returning infinite future/past
gpr_timespec gpr_time_add(gpr_timespec a, gpr_timespec b) {
  gpr_timespec sum;
  int64_t inc = 0;
  CHECK(b.clock_type == GPR_TIMESPAN);  // b must be a timespan

  CHECK_GE(b.tv_nsec, 0);  // Nanoseconds must be non-negative
  sum.clock_type = a.clock_type;
  sum.tv_nsec = a.tv_nsec + b.tv_nsec;
  if (sum.tv_nsec >= GPR_NS_PER_SEC) {  // Handle nanosecond overflow
    sum.tv_nsec -= GPR_NS_PER_SEC;
    inc++;
  }
  if (a.tv_sec == INT64_MAX || a.tv_sec == INT64_MIN) {
    sum = a;  // Infinity cases
  } else if (b.tv_sec == INT64_MAX ||
             (b.tv_sec >= 0 && a.tv_sec >= INT64_MAX - b.tv_sec)) {
    sum = gpr_inf_future(sum.clock_type);  // Overflow to future infinity
  } else if (b.tv_sec == INT64_MIN ||
             (b.tv_sec <= 0 && a.tv_sec <= INT64_MIN - b.tv_sec)) {
    sum = gpr_inf_past(sum.clock_type);  // Underflow to past infinity
  } else {
    sum.tv_sec = a.tv_sec + b.tv_sec;
    if (inc != 0 && sum.tv_sec == INT64_MAX - 1) {
      sum = gpr_inf_future(sum.clock_type);  // Handle carry overflow
    } else {
      sum.tv_sec += inc;
    }
  }
  return sum;
}

// Subtracts two time values (returns timespan if b is not a timespan)
// Handles underflow/overflow cases by returning infinite future/past
gpr_timespec gpr_time_sub(gpr_timespec a, gpr_timespec b) {
  gpr_timespec diff;
  int64_t dec = 0;
  if (b.clock_type == GPR_TIMESPAN) {
    diff.clock_type = a.clock_type;

    CHECK_GE(b.tv_nsec, 0);  // Nanoseconds must be non-negative
  } else {
    CHECK(a.clock_type == b.clock_type);  // Clock types must match
    diff.clock_type = GPR_TIMESPAN;       // Result is a timespan
  }
  diff.tv_nsec = a.tv_nsec - b.tv_nsec;
  if (diff.tv_nsec < 0) {  // Handle nanosecond underflow
    diff.tv_nsec += GPR_NS_PER_SEC;
    dec++;
  }
  if (a.tv_sec == INT64_MAX || a.tv_sec == INT64_MIN) {
    diff.tv_sec = a.tv_sec;
    diff.tv_nsec = a.tv_nsec;
  } else if (b.tv_sec == INT64_MIN ||
             (b.tv_sec <= 0 && a.tv_sec >= INT64_MAX + b.tv_sec)) {
    diff = gpr_inf_future(GPR_CLOCK_REALTIME);  // Overflow to future infinity
  } else if (b.tv_sec == INT64_MAX ||
             (b.tv_sec >= 0 && a.tv_sec <= INT64_MIN + b.tv_sec)) {
    diff = gpr_inf_past(GPR_CLOCK_REALTIME);  // Underflow to past infinity
  } else {
    diff.tv_sec = a.tv_sec - b.tv_sec;
    if (dec != 0 && diff.tv_sec == INT64_MIN + 1) {
      diff = gpr_inf_past(GPR_CLOCK_REALTIME);  // Handle carry underflow
    } else {
      diff.tv_sec -= dec;
    }
  }
  return diff;
}

// Checks if two times are within a threshold of each other
int gpr_time_similar(gpr_timespec a, gpr_timespec b, gpr_timespec threshold) {
  int cmp_ab;

  CHECK(a.clock_type == b.clock_type);          // Clock types must match
  CHECK(threshold.clock_type == GPR_TIMESPAN);  // Threshold must be a timespan

  cmp_ab = gpr_time_cmp(a, b);
  if (cmp_ab == 0) return 1;  // Exactly equal
  if (cmp_ab < 0) {
    return gpr_time_cmp(gpr_time_sub(b, a), threshold) <= 0;
  } else {
    return gpr_time_cmp(gpr_time_sub(a, b), threshold) <= 0;
  }
}

// Converts gpr_timespec to milliseconds (with overflow protection)
int32_t gpr_time_to_millis(gpr_timespec t) {
  if (t.tv_sec >= 2147483) {  // Near 32-bit overflow (seconds)
    if (t.tv_sec == 2147483 && t.tv_nsec < 648 * GPR_NS_PER_MS) {
      return (2147483 * GPR_MS_PER_SEC) + (t.tv_nsec / GPR_NS_PER_MS);
    }
    return 2147483647;  // Return max 32-bit value
  } else if (t.tv_sec <= -2147483) {  // Near 32-bit underflow (seconds)
    return -2147483647;  // Return min 32-bit value
  } else {
    return static_cast<int32_t>((t.tv_sec * GPR_MS_PER_SEC) +
                                (t.tv_nsec / GPR_NS_PER_MS));
  }
}

// Converts gpr_timespec to microseconds as a double
double gpr_timespec_to_micros(gpr_timespec t) {
  return (static_cast<double>(t.tv_sec) * GPR_US_PER_SEC) + (t.tv_nsec * 1e-3);
}

// Converts a time value to a different clock type
gpr_timespec gpr_convert_clock_type(gpr_timespec t, gpr_clock_type clock_type) {
  if (t.clock_type == clock_type) {
    return t;  // No conversion needed
  }

  // Infinite times just need their clock type changed
  if (t.tv_sec == INT64_MAX || t.tv_sec == INT64_MIN) {
    t.clock_type = clock_type;
    return t;
  }

  // Converting to timespan: return difference from now
  if (clock_type == GPR_TIMESPAN) {
    return gpr_time_sub(t, gpr_now(t.clock_type));
  }

  // Converting from timespan: add to current time in new clock
  if (t.clock_type == GPR_TIMESPAN) {
    return gpr_time_add(gpr_now(clock_type), t);
  }

  // General case: convert via timespan intermediate
  return gpr_time_add(gpr_now(clock_type),
                      gpr_time_sub(t, gpr_now(t.clock_type)));
}
```