Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/telemetry/histogram_view.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

// Returns the total count of all samples in the histogram by summing all bucket counts
double HistogramView::Count() const {
  double sum = 0;
  // Iterate through all buckets and accumulate their counts
  for (int i = 0; i < num_buckets; i++) {
    sum += buckets[i];
  }
  return sum;
}

// Finds the threshold value where the cumulative count reaches or exceeds count_below
// Uses linear interpolation between bucket boundaries when needed
double HistogramView::ThresholdForCountBelow(double count_below) const {
  double lower_bound;
  double upper_bound;
  int upper_idx;

  // Find the first bucket where cumulative count meets or exceeds count_below
  double count_so_far = 0.0;
  int lower_idx = 0;
  for (; lower_idx < num_buckets; lower_idx++) {
    count_so_far += static_cast<double>(buckets[lower_idx]);
    if (count_so_far >= count_below) {
      break;
    }
  }

  // Exact match case: return midpoint between current and next non-empty bucket
  if (count_so_far == count_below) {
    // Find next non-empty bucket
    for (upper_idx = lower_idx + 1; upper_idx < num_buckets; upper_idx++) {
      if (buckets[upper_idx]) {
        break;
      }
    }
    return (bucket_boundaries[lower_idx] + bucket_boundaries[upper_idx]) / 2.0;
  } else {
    // Interpolation case: calculate exact threshold within the found bucket
    lower_bound = bucket_boundaries[lower_idx];
    upper_bound = bucket_boundaries[lower_idx + 1];
    // Linear interpolation formula:
    // upper_bound - (distance_to_upper_bound * remaining_count / bucket_count)
    return upper_bound -
           ((upper_bound - lower_bound) * (count_so_far - count_below) /
            static_cast<double>(buckets[lower_idx]));
  }
}

// Calculates the value at a given percentile (p) in the histogram distribution
// Returns 0 if histogram is empty
double HistogramView::Percentile(double p) const {
  const double count = Count();
  if (count == 0) return 0.0;
  // Convert percentile to count threshold and find corresponding value
  return ThresholdForCountBelow(count * p / 100.0);
}

}  // namespace grpc_core
```

Key improvements in the comments:
1. Added clear function-level descriptions explaining each method's purpose
2. Added detailed comments for the algorithm steps in ThresholdForCountBelow
3. Explained the linear interpolation logic and exact match case
4. Clarified the percentile calculation process
5. Added note about empty histogram case
6. Improved code structure with consistent spacing and closing namespace comment

The comments now provide a clear understanding of:
- What each function does
- How the histogram calculations work
- The edge cases being handled
- The mathematical operations being performed