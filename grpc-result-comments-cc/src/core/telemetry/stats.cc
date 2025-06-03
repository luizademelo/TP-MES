Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Core telemetry statistics collection and reporting implementation
#include "src/core/telemetry/stats.h"

// Platform-specific configuration and standard library includes
#include <grpc/support/port_platform.h>
#include <stddef.h>

// Standard library includes
#include <algorithm>
#include <vector>

// Abseil string utilities for efficient string operations
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

// Implementation details for statistics collection and reporting
namespace stats_detail {

namespace {
// Helper function to convert an array of values to a JSON array string
// Template parameter I allows for different numeric types (int, uint64_t, etc.)
template <typename I>
std::string ArrayToJson(absl::Span<const I> values) {
  std::vector<std::string> parts;
  // Convert each value to string and store in temporary vector
  for (auto value : values) {
    parts.push_back(absl::StrCat(value));
  }
  // Join all values with commas and wrap in square brackets to form JSON array
  return absl::StrCat("[", absl::StrJoin(parts, ","), "]");
}
}  // anonymous namespace

// Converts statistical data (counters and histograms) to a JSON formatted string
// Arguments:
//   counters - Array of counter values
//   counter_name - Array of counter names (matching counters array)
//   histograms - Array of histogram data structures
//   histogram_name - Array of histogram names (matching histograms array)
// Returns:
//   JSON string containing all statistics in key-value format
std::string StatsAsJson(absl::Span<const uint64_t> counters,
                        absl::Span<const absl::string_view> counter_name,
                        absl::Span<const HistogramView> histograms,
                        absl::Span<const absl::string_view> histogram_name) {
  std::vector<std::string> parts;
  
  // Process counters: create "name": value pairs for each counter
  for (size_t i = 0; i < counters.size(); i++) {
    parts.push_back(absl::StrCat("\"", counter_name[i], "\": ", counters[i]));
  }
  
  // Process histograms: create two entries for each histogram:
  // 1. The bucket counts as a JSON array
  // 2. The bucket boundaries as a JSON array
  for (size_t i = 0; i < histograms.size(); i++) {
    // Add histogram bucket counts
    parts.push_back(
        absl::StrCat("\"", histogram_name[i], "\": ",
                     ArrayToJson(absl::Span<const uint64_t>(
                         histograms[i].buckets, histograms[i].num_buckets))));
    // Add histogram bucket boundaries
    parts.push_back(absl::StrCat(
        "\"", histogram_name[i], "_bkt\": ",
        ArrayToJson(absl::Span<const int>(histograms[i].bucket_boundaries,
                                          histograms[i].num_buckets))));
  }
  
  // Combine all parts into a single JSON object
  return absl::StrCat("{", absl::StrJoin(parts, ", "), "}");
}

}  // namespace stats_detail
}  // namespace grpc_core
```