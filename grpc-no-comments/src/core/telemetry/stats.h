
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_STATS_H
#define GRPC_SRC_CORE_TELEMETRY_STATS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/telemetry/histogram_view.h"
#include "src/core/telemetry/stats_data.h"

namespace grpc_core {

namespace stats_detail {
std::string StatsAsJson(absl::Span<const uint64_t> counters,
                        absl::Span<const absl::string_view> counter_name,
                        absl::Span<const HistogramView> histograms,
                        absl::Span<const absl::string_view> histogram_name);
}

template <typename T>
std::string StatsAsJson(T* data) {
  std::vector<HistogramView> histograms;
  for (int i = 0; i < static_cast<int>(T::Histogram::COUNT); i++) {
    histograms.push_back(
        data->histogram(static_cast<typename T::Histogram>(i)));
  }
  return stats_detail::StatsAsJson(
      absl::Span<const uint64_t>(data->counters,
                                 static_cast<int>(T::Counter::COUNT)),
      T::counter_name, histograms, T::histogram_name);
}

}

#endif
