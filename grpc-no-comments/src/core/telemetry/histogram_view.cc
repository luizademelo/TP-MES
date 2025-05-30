// Copyright 2021 gRPC authors.

#include "src/core/telemetry/histogram_view.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

double HistogramView::Count() const {
  double sum = 0;
  for (int i = 0; i < num_buckets; i++) {
    sum += buckets[i];
  }
  return sum;
}

double HistogramView::ThresholdForCountBelow(double count_below) const {
  double lower_bound;
  double upper_bound;
  int upper_idx;

  double count_so_far = 0.0;
  int lower_idx = 0;
  for (; lower_idx < num_buckets; lower_idx++) {
    count_so_far += static_cast<double>(buckets[lower_idx]);
    if (count_so_far >= count_below) {
      break;
    }
  }
  if (count_so_far == count_below) {

    for (upper_idx = lower_idx + 1; upper_idx < num_buckets; upper_idx++) {
      if (buckets[upper_idx]) {
        break;
      }
    }
    return (bucket_boundaries[lower_idx] + bucket_boundaries[upper_idx]) / 2.0;
  } else {

    lower_bound = bucket_boundaries[lower_idx];
    upper_bound = bucket_boundaries[lower_idx + 1];
    return upper_bound -
           ((upper_bound - lower_bound) * (count_so_far - count_below) /
            static_cast<double>(buckets[lower_idx]));
  }
}

double HistogramView::Percentile(double p) const {
  const double count = Count();
  if (count == 0) return 0.0;
  return ThresholdForCountBelow(count * p / 100.0);
}

}
