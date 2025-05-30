// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_HISTOGRAM_VIEW_H
#define GRPC_SRC_CORE_TELEMETRY_HISTOGRAM_VIEW_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

namespace grpc_core {

struct HistogramView {
  int (*bucket_for)(int value);
  const int* bucket_boundaries;
  int num_buckets;
  const uint64_t* buckets;

  double Percentile(double p) const;
  double Count() const;
  double ThresholdForCountBelow(double count_below) const;
};

}

#endif
