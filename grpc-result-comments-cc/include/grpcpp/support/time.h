Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_SUPPORT_TIME_H
#define GRPCPP_SUPPORT_TIME_H

// Include necessary headers
#include <grpc/impl/grpc_types.h>  // For gpr_timespec type
#include <grpcpp/support/config.h> // For gRPC C++ configuration

#include <chrono> // For std::chrono time utilities

namespace grpc {

// Primary template for TimePoint class (undefined)
// This serves as a base template that will be specialized for specific types
template <typename T>
class TimePoint {
 public:
  // Deleted constructor and raw_time() function to prevent instantiation
  // of the base template
  TimePoint(const T& ) = delete;
  gpr_timespec raw_time() = delete;
};

// Template specialization for gpr_timespec
// This allows TimePoint to work specifically with gRPC's time representation
template <>
class TimePoint<gpr_timespec> {
 public:
  // Constructor that takes a gpr_timespec and stores it
  explicit TimePoint(const gpr_timespec& time) : time_(time) {}
  
  // Returns the stored gpr_timespec value
  gpr_timespec raw_time() { return time_; }

 private:
  gpr_timespec time_; // Internal storage of the time value
};

} // namespace grpc

namespace grpc {

// Converts a std::chrono::system_clock time_point to gpr_timespec
// from: input time in system_clock format
// to: output parameter where converted time will be stored
void Timepoint2Timespec(const std::chrono::system_clock::time_point& from,
                        gpr_timespec* to);

// Converts a std::chrono::high_resolution_clock time_point to gpr_timespec
// from: input time in high_resolution_clock format
// to: output parameter where converted time will be stored
void TimepointHR2Timespec(
    const std::chrono::high_resolution_clock::time_point& from,
    gpr_timespec* to);

// Converts a gpr_timespec to std::chrono::system_clock::time_point
// t: input time in gpr_timespec format
// returns: converted time in system_clock format
std::chrono::system_clock::time_point Timespec2Timepoint(gpr_timespec t);

// Template specialization for std::chrono::system_clock::time_point
// This allows TimePoint to work with C++ standard library's system clock
template <>
class TimePoint<std::chrono::system_clock::time_point> {
 public:
  // Constructor that converts and stores a system_clock time_point
  explicit TimePoint(const std::chrono::system_clock::time_point& time) {
    Timepoint2Timespec(time, &time_);
  }
  
  // Returns the stored time as gpr_timespec
  gpr_timespec raw_time() const { return time_; }

 private:
  gpr_timespec time_; // Internal storage of the time value (in gpr_timespec format)
};

} // namespace grpc

#endif // GRPCPP_SUPPORT_TIME_H
```

The comments explain:
1. The purpose of each class and function
2. The template specialization approach used
3. The conversion between different time representations
4. The flow of data through the functions
5. The storage strategy for time values
6. The relationship between C++ standard chrono types and gRPC's time representation

The comments are designed to help future developers understand:
- Why certain design choices were made
- How to use these time conversion utilities
- Where to find the implementations of the declared functions
- The relationship between different time representations in the system