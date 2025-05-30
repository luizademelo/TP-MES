
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_USAGE_TIMER_H
#define GRPC_TEST_CPP_QPS_USAGE_TIMER_H

class UsageTimer {
 public:
  UsageTimer();

  struct Result {
    double wall;
    double user;
    double system;
    unsigned long long total_cpu_time;
    unsigned long long idle_cpu_time;
  };

  Result Mark() const;

  static double Now();

 private:
  static Result Sample();

  const Result start_;
};

#endif
