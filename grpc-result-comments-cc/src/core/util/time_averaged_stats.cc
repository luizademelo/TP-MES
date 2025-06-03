Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/util/time_averaged_stats.h"
#include <grpc/support/port_platform.h>

namespace grpc_core {

// Constructor for TimeAveragedStats class
// Parameters:
//   init_avg: Initial average value used when no samples are present
//   regress_weight: Weight given to the initial average during regression
//   persistence_factor: Factor determining how much previous samples influence current average
TimeAveragedStats::TimeAveragedStats(double init_avg, double regress_weight,
                                     double persistence_factor)
    : init_avg_(init_avg),
      regress_weight_(regress_weight),
      persistence_factor_(persistence_factor) {}

// Adds a new sample to the current batch
// Parameters:
//   value: The sample value to be added
void TimeAveragedStats::AddSample(double value) {
  batch_total_value_ += value;
  ++batch_num_samples_;
}

// Updates the running weighted average with current batch samples and returns the new average
// Returns:
//   The updated weighted average
double TimeAveragedStats::UpdateAverage() {
  // Calculate weighted sum and total weight from current batch
  double weighted_sum = batch_total_value_;
  double total_weight = batch_num_samples_;

  // If regression weight is specified, blend with initial average
  if (regress_weight_ > 0) {
    weighted_sum += regress_weight_ * init_avg_;
    total_weight += regress_weight_;
  }

  // If persistence is enabled, incorporate previous aggregate data
  if (persistence_factor_ > 0) {
    const double prev_sample_weight =
        persistence_factor_ * aggregate_total_weight_;
    weighted_sum += prev_sample_weight * aggregate_weighted_avg_;
    total_weight += prev_sample_weight;
  }

  // Calculate new weighted average (fall back to init_avg if no weights)
  aggregate_weighted_avg_ =
      (total_weight > 0) ? (weighted_sum / total_weight) : init_avg_;
  aggregate_total_weight_ = total_weight;

  // Reset batch statistics for next period
  batch_num_samples_ = 0;
  batch_total_value_ = 0;

  return aggregate_weighted_avg_;
}

}  // namespace grpc_core
```

The comments explain:
1. The class constructor and its parameters
2. The AddSample method's purpose and parameters
3. The UpdateAverage method's functionality, including:
   - How it combines current batch samples
   - The regression towards initial average
   - The persistence of previous aggregates
   - The final average calculation
   - The reset of batch statistics
4. The return value of UpdateAverage

The comments are placed to help future developers understand both the high-level purpose and the detailed implementation logic of each component.