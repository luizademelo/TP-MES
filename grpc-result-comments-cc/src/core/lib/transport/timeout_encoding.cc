Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/lib/transport/timeout_encoding.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <limits>

#include "absl/base/attributes.h"
#include "absl/log/check.h"

namespace grpc_core {

namespace {

// Helper function to perform integer division with rounding up
// Returns the ceiling of (dividend / divisor)
int64_t DivideRoundingUp(int64_t dividend, int64_t divisor) {
  return (dividend - 1 + divisor) / divisor;
}

// Constants for time unit conversions
constexpr int64_t kSecondsPerMinute = 60;
constexpr int64_t kMinutesPerHour = 60;
constexpr int64_t kMaxHours = 27000;  // Maximum allowed hours value (7.5 years)

// Checks if all bytes in range [p, end) are space characters
bool IsAllSpace(const uint8_t* p, const uint8_t* end) {
  while (p != end && *p == ' ') p++;
  return p == end;
}

}  // namespace

// Creates a Timeout from a Duration object by converting to milliseconds
Timeout Timeout::FromDuration(Duration duration) {
  return Timeout::FromMillis(duration.millis());
}

// Calculates the percentage difference between two timeouts
// Returns 100 * (this_timeout/other_timeout - 1)
double Timeout::RatioVersus(Timeout other) const {
  double a = AsDuration().millis();
  double b = other.AsDuration().millis();
  if (b == 0) {
    if (a > 0) return 100;
    if (a < 0) return -100;
    return 0;
  }
  return 100 * (a / b - 1);
}

// Converts the timeout to a Duration object based on its unit
Duration Timeout::AsDuration() const {
  int64_t value = value_;
  switch (unit_) {
    case Unit::kNanoseconds:
      return Duration::Zero();
    case Unit::kMilliseconds:
      return Duration::Milliseconds(value);
    case Unit::kTenMilliseconds:
      return Duration::Milliseconds(value * 10);
    case Unit::kHundredMilliseconds:
      return Duration::Milliseconds(value * 100);
    case Unit::kSeconds:
      return Duration::Seconds(value);
    case Unit::kTenSeconds:
      return Duration::Seconds(value * 10);
    case Unit::kHundredSeconds:
      return Duration::Seconds(value * 100);
    case Unit::kMinutes:
      return Duration::Minutes(value);
    case Unit::kTenMinutes:
      return Duration::Minutes(value * 10);
    case Unit::kHundredMinutes:
      return Duration::Minutes(value * 100);
    case Unit::kHours:
      return Duration::Hours(value);
  }
  GPR_UNREACHABLE_CODE(return Duration::NegativeInfinity());
}

// Encodes the timeout into a string representation (e.g., "100S" for 100 seconds)
Slice Timeout::Encode() const {
  char buf[10];
  char* p = buf;
  uint16_t n = value_;
  int digits;
  
  // Determine number of digits in the value
  if (n >= 10000) {
    digits = 5;
  } else if (n >= 1000) {
    digits = 4;
  } else if (n >= 100) {
    digits = 3;
  } else if (n >= 10) {
    digits = 2;
  } else {
    digits = 1;
  }
  
  // Write digits to buffer
  switch (digits) {
    case 5:
      *p++ = '0' + n / 10000;
      n %= 10000;
      [[fallthrough]];
    case 4:
      *p++ = '0' + n / 1000;
      n %= 1000;
      [[fallthrough]];
    case 3:
      *p++ = '0' + n / 100;
      n %= 100;
      [[fallthrough]];
    case 2:
      *p++ = '0' + n / 10;
      n %= 10;
      [[fallthrough]];
    case 1:
      *p++ = '0' + n;
  }
  
  // Append unit suffix
  switch (unit_) {
    case Unit::kNanoseconds:
      *p++ = 'n';
      break;
    case Unit::kHundredMilliseconds:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kTenMilliseconds:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kMilliseconds:
      *p++ = 'm';
      break;
    case Unit::kHundredSeconds:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kTenSeconds:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kSeconds:
      *p++ = 'S';
      break;
    case Unit::kHundredMinutes:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kTenMinutes:
      *p++ = '0';
      [[fallthrough]];
    case Unit::kMinutes:
      *p++ = 'M';
      break;
    case Unit::kHours:
      *p++ = 'H';
      break;
  }
  return Slice::FromCopiedBuffer(buf, p - buf);
}

// Creates a Timeout from milliseconds, choosing the most appropriate unit
Timeout Timeout::FromMillis(int64_t millis) {
  if (millis <= 0) {
    return Timeout(1, Unit::kNanoseconds);
  } else if (millis < 1000) {
    return Timeout(millis, Unit::kMilliseconds);
  } else if (millis < 10000) {
    int64_t value = DivideRoundingUp(millis, 10);
    if (value % 100 != 0) return Timeout(value, Unit::kTenMilliseconds);
  } else if (millis < 100000) {
    int64_t value = DivideRoundingUp(millis, 100);
    if (value % 10 != 0) return Timeout(value, Unit::kHundredMilliseconds);
  } else if (millis > std::numeric_limits<int64_t>::max() - 999) {
    return Timeout(kMaxHours, Unit::kHours);
  }
  return Timeout::FromSeconds(DivideRoundingUp(millis, 1000));
}

// Creates a Timeout from seconds, choosing the most appropriate unit
Timeout Timeout::FromSeconds(int64_t seconds) {
  DCHECK_NE(seconds, 0);
  if (seconds < 1000) {
    if (seconds % kSecondsPerMinute != 0) {
      return Timeout(seconds, Unit::kSeconds);
    }
  } else if (seconds < 10000) {
    int64_t value = DivideRoundingUp(seconds, 10);
    if ((value * 10) % kSecondsPerMinute != 0) {
      return Timeout(value, Unit::kTenSeconds);
    }
  } else if (seconds < 100000) {
    int64_t value = DivideRoundingUp(seconds, 100);
    if ((value * 100) % kSecondsPerMinute != 0) {
      return Timeout(value, Unit::kHundredSeconds);
    }
  }
  return Timeout::FromMinutes(DivideRoundingUp(seconds, kSecondsPerMinute));
}

// Creates a Timeout from minutes, choosing the most appropriate unit
Timeout Timeout::FromMinutes(int64_t minutes) {
  DCHECK_NE(minutes, 0);
  if (minutes < 1000) {
    if (minutes % kMinutesPerHour != 0) {
      return Timeout(minutes, Unit::kMinutes);
    }
  } else if (minutes < 10000) {
    int64_t value = DivideRoundingUp(minutes, 10);
    if ((value * 10) % kMinutesPerHour != 0) {
      return Timeout(value, Unit::kTenMinutes);
    }
  } else if (minutes < 100000) {
    int64_t value = DivideRoundingUp(minutes, 100);
    if ((value * 100) % kMinutesPerHour != 0) {
      return Timeout(value, Unit::kHundredMinutes);
    }
  }
  return Timeout::FromHours(DivideRoundingUp(minutes, kMinutesPerHour));
}

// Creates a Timeout from hours, clamping to maximum allowed value
Timeout Timeout::FromHours(int64_t hours) {
  DCHECK_NE(hours, 0);
  if (hours < kMaxHours) {
    return Timeout(hours, Unit::kHours);
  }
  return Timeout(kMaxHours, Unit::kHours);
}

// Parses a timeout string into a Duration object
// Format: [0-9]+[n|u|m|S|M|H] (e.g. "100S" for 100 seconds)
std::optional<Duration> ParseTimeout(const Slice& text) {
  int32_t x = 0;
  const uint8_t* p = text.begin();
  const uint8_t* end = text.end();
  int have_digit = 0;

  // Skip leading spaces
  for (; p != end && *p == ' '; p++) {
  }

  // Parse numeric value
  for (; p != end && *p >= '0' && *p <= '9'; p++) {
    int32_t digit = static_cast<int32_t>(*p - static_cast<uint8_t>('0'));
    have_digit = 1;

    // Handle overflow (100,000,000 is maximum value)
    if (x >= (100 * 1000 * 1000)) {
      if (x != (100 * 1000 * 1000) || digit != 0) {
        return Duration::Infinity();
      }
    }
    x = x * 10 + digit;
  }
  if (!have_digit) return std::nullopt;

  // Skip spaces between number and unit
  for (; p != end && *p == ' '; p++) {
  }
  if (p == end) return std::nullopt;

  // Parse time unit and convert to Duration
  Duration timeout;
  switch (*p) {
    case 'n':  // nanoseconds
      timeout = Duration::Milliseconds((x / GPR_NS_PER_MS) +
                                       (x % GPR_NS_PER_MS != 0));
      break;
    case 'u':  // microseconds
      timeout = Duration::Milliseconds((x / GPR_US_PER_MS) +
                                       (x % GPR_US_PER_MS != 0));
      break;
    case 'm':  // milliseconds
      timeout = Duration::Milliseconds(x);
      break;
    case 'S':  // seconds
      timeout = Duration::Seconds(x);
      break;
    case 'M':  // minutes
      timeout = Duration::Minutes(x);
      break;
    case 'H':  // hours
      timeout = Duration::Hours(x);
      break;
    default:
      return std::nullopt;
  }
  p++;
  
  // Verify there's only spaces remaining
  if (!IsAllSpace(p, end)) return std::nullopt;
  return timeout;
}

}  // namespace grpc_core
```