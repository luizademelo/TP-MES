Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_TIMEOUT_ENCODING_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_TIMEOUT_ENCODING_H

#include <grpc/support/port_platform.h>  // Platform-specific support
#include <stdint.h>                      // Standard integer types

#include <optional>                      // For std::optional

#include "src/core/lib/slice/slice.h"    // Slice class for binary data
#include "src/core/util/time.h"          // Duration type

namespace grpc_core {

// Class representing a timeout value with various units of measurement
// Provides conversion methods between different representations
class Timeout {
 public:
  // Creates a Timeout from a Duration object
  static Timeout FromDuration(Duration duration);

  // Calculates the ratio between this timeout and another timeout
  double RatioVersus(Timeout other) const;
  
  // Encodes the timeout into a Slice (binary format)
  Slice Encode() const;
  
  // Converts the timeout to a Duration object
  Duration AsDuration() const;

 private:
  // Enumeration of possible time units for the timeout
  enum class Unit : uint8_t {
    kNanoseconds,        // Nanoseconds
    kMilliseconds,       // Milliseconds
    kTenMilliseconds,    // 10 Milliseconds
    kHundredMilliseconds,// 100 Milliseconds
    kSeconds,           // Seconds
    kTenSeconds,         // 10 Seconds
    kHundredSeconds,     // 100 Seconds
    kMinutes,            // Minutes
    kTenMinutes,         // 10 Minutes
    kHundredMinutes,     // 100 Minutes
    kHours,             // Hours
  };

  // Private constructor - use factory methods instead
  Timeout(uint16_t value, Unit unit) : value_(value), unit_(unit) {}

  // Factory methods for creating Timeout objects from different units
  static Timeout FromMillis(int64_t millis);
  static Timeout FromSeconds(int64_t seconds);
  static Timeout FromMinutes(int64_t minutes);
  static Timeout FromHours(int64_t hours);

  // Internal storage of timeout value and unit
  uint16_t value_ = 0;          // Numeric value of the timeout
  Unit unit_ = Unit::kNanoseconds;  // Unit of measurement (default: nanoseconds)
};

// Parses a timeout from text representation into a Duration
// Returns std::nullopt if parsing fails
std::optional<Duration> ParseTimeout(const Slice& text);

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_TRANSPORT_TIMEOUT_ENCODING_H
```

The comments explain:
1. The purpose of each include directive
2. The overall purpose of the Timeout class
3. Each public method's functionality
4. The meaning of each unit in the enum
5. The private implementation details
6. The purpose of the ParseTimeout function
7. The role of the header guard

The comments are concise yet informative, providing enough context for future maintainers to understand the code's functionality without being overly verbose.