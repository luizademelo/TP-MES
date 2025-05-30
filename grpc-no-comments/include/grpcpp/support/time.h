
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_TIME_H
#define GRPCPP_SUPPORT_TIME_H

#include <grpc/impl/grpc_types.h>
#include <grpcpp/support/config.h>

#include <chrono>

namespace grpc {

template <typename T>
class TimePoint {
 public:

  TimePoint(const T& ) = delete;
  gpr_timespec raw_time() = delete;
};

template <>
class TimePoint<gpr_timespec> {
 public:

  TimePoint(const gpr_timespec& time) : time_(time) {}
  gpr_timespec raw_time() { return time_; }

 private:
  gpr_timespec time_;
};

}

namespace grpc {

void Timepoint2Timespec(const std::chrono::system_clock::time_point& from,
                        gpr_timespec* to);
void TimepointHR2Timespec(
    const std::chrono::high_resolution_clock::time_point& from,
    gpr_timespec* to);

std::chrono::system_clock::time_point Timespec2Timepoint(gpr_timespec t);

template <>
class TimePoint<std::chrono::system_clock::time_point> {
 public:

  TimePoint(const std::chrono::system_clock::time_point& time) {
    Timepoint2Timespec(time, &time_);
  }
  gpr_timespec raw_time() const { return time_; }

 private:
  gpr_timespec time_;
};

}

#endif
