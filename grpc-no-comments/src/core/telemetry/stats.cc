
// Copyright 2017 gRPC authors.

#include "src/core/telemetry/stats.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

namespace stats_detail {

namespace {
template <typename I>
std::string ArrayToJson(absl::Span<const I> values) {
  std::vector<std::string> parts;
  for (auto value : values) {
    parts.push_back(absl::StrCat(value));
  }
  return absl::StrCat("[", absl::StrJoin(parts, ","), "]");
}
}

std::string StatsAsJson(absl::Span<const uint64_t> counters,
                        absl::Span<const absl::string_view> counter_name,
                        absl::Span<const HistogramView> histograms,
                        absl::Span<const absl::string_view> histogram_name) {
  std::vector<std::string> parts;
  for (size_t i = 0; i < counters.size(); i++) {
    parts.push_back(absl::StrCat("\"", counter_name[i], "\": ", counters[i]));
  }
  for (size_t i = 0; i < histograms.size(); i++) {
    parts.push_back(
        absl::StrCat("\"", histogram_name[i], "\": ",
                     ArrayToJson(absl::Span<const uint64_t>(
                         histograms[i].buckets, histograms[i].num_buckets))));
    parts.push_back(absl::StrCat(
        "\"", histogram_name[i], "_bkt\": ",
        ArrayToJson(absl::Span<const int>(histograms[i].bucket_boundaries,
                                          histograms[i].num_buckets))));
  }
  return absl::StrCat("{", absl::StrJoin(parts, ", "), "}");
}

}
}
