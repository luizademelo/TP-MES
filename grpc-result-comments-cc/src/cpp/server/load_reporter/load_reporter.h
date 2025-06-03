Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTER_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTER_H

#include <google/protobuf/repeated_ptr_field.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "src/core/util/sync.h"
#include "src/cpp/server/load_reporter/load_data_store.h"
#include "src/proto/grpc/lb/v1/load_reporter.grpc.pb.h"

namespace grpc {
namespace load_reporter {

// Abstract base class for providing census view data.
// Manages view descriptors and provides methods to fetch view data.
class CensusViewProvider {
 public:
  // Map of view names to their corresponding ViewData.
  using ViewDataMap =
      std::unordered_map<std::string, ::opencensus::stats::ViewData>;

  // Map of view names to their corresponding ViewDescriptor.
  using ViewDescriptorMap =
      std::unordered_map<std::string, ::opencensus::stats::ViewDescriptor>;

  CensusViewProvider();
  virtual ~CensusViewProvider() = default;

  // Fetches current view data from census.
  virtual ViewDataMap FetchViewData() = 0;

  // Helper methods to extract specific data types from view data.
  static double GetRelatedViewDataRowDouble(
      const ViewDataMap& view_data_map, const char* view_name,
      size_t view_name_len, const std::vector<std::string>& tag_values);
  static uint64_t GetRelatedViewDataRowInt(
      const ViewDataMap& view_data_map, const char* view_name,
      size_t view_name_len, const std::vector<std::string>& tag_values);

 protected:
  // Provides access to the view descriptor map.
  const ViewDescriptorMap& view_descriptor_map() const {
    return view_descriptor_map_;
  }

 private:
  // Map of view names to their descriptors.
  ViewDescriptorMap view_descriptor_map_;

  // Tag keys used for categorizing census data.
  ::opencensus::tags::TagKey tag_key_token_;
  ::opencensus::tags::TagKey tag_key_host_;
  ::opencensus::tags::TagKey tag_key_user_id_;
  ::opencensus::tags::TagKey tag_key_status_;
  ::opencensus::tags::TagKey tag_key_metric_name_;
};

// Default implementation of CensusViewProvider.
class CensusViewProviderDefaultImpl : public CensusViewProvider {
 public:
  CensusViewProviderDefaultImpl();

  // Fetches view data from census using the default implementation.
  ViewDataMap FetchViewData() override;

 private:
  // Map of view names to their corresponding View objects.
  std::unordered_map<std::string, ::opencensus::stats::View> view_map_;
};

// Abstract base class for providing CPU statistics.
class CpuStatsProvider {
 public:
  // Pair representing CPU stats: (usage, limit).
  using CpuStatsSample = std::pair<uint64_t, uint64_t>;

  virtual ~CpuStatsProvider() = default;

  // Returns current CPU statistics.
  virtual CpuStatsSample GetCpuStats() = 0;
};

// Default implementation of CpuStatsProvider.
class CpuStatsProviderDefaultImpl : public CpuStatsProvider {
 public:
  // Returns CPU statistics using the default implementation.
  CpuStatsSample GetCpuStats() override;
};

// Main class for load reporting functionality.
// Collects and reports load statistics to the load balancer.
class LoadReporter {
 public:
  // Constructor initializes with:
  // - feedback_sample_window_seconds: duration to keep feedback samples
  // - census_view_provider: implementation for fetching census data
  // - cpu_stats_provider: implementation for fetching CPU stats
  LoadReporter(uint32_t feedback_sample_window_seconds,
               std::unique_ptr<CensusViewProvider> census_view_provider,
               std::unique_ptr<CpuStatsProvider> cpu_stats_provider)
      : feedback_sample_window_seconds_(feedback_sample_window_seconds),
        census_view_provider_(std::move(census_view_provider)),
        cpu_stats_provider_(std::move(cpu_stats_provider)) {
    // Initialize with an empty feedback record
    AppendNewFeedbackRecord(0, 0);
  }

  // Fetches and samples current load data.
  void FetchAndSample();

  // Generates load reports for the given hostname and load balancer ID.
  ::google::protobuf::RepeatedPtrField<grpc::lb::v1::Load> GenerateLoads(
      const std::string& hostname, const std::string& lb_id);

  // Generates load balancing feedback based on collected samples.
  grpc::lb::v1::LoadBalancingFeedback GenerateLoadBalancingFeedback();

  // Called when a new load reporting stream is created.
  void ReportStreamCreated(const std::string& hostname,
                           const std::string& lb_id,
                           const std::string& load_key);

  // Called when a load reporting stream is closed.
  void ReportStreamClosed(const std::string& hostname,
                          const std::string& lb_id);

  // Generates a new unique load balancer ID.
  std::string GenerateLbId();

  // Accessors for the provider implementations.
  CensusViewProvider* census_view_provider() {
    return census_view_provider_.get();
  }
  CpuStatsProvider* cpu_stats_provider() { return cpu_stats_provider_.get(); }

 private:
  // Structure representing a single feedback record.
  struct LoadBalancingFeedbackRecord {
    std::chrono::system_clock::time_point end_time;
    uint64_t rpcs;          // Number of RPCs in this sample
    uint64_t errors;        // Number of errors in this sample
    uint64_t cpu_usage;     // CPU usage in this sample
    uint64_t cpu_limit;     // CPU limit at time of sample

    LoadBalancingFeedbackRecord(
        const std::chrono::system_clock::time_point& end_time, uint64_t rpcs,
        uint64_t errors, uint64_t cpu_usage, uint64_t cpu_limit)
        : end_time(end_time),
          rpcs(rpcs),
          errors(errors),
          cpu_usage(cpu_usage),
          cpu_limit(cpu_limit) {}
  };

  // Processes call start metrics from view data.
  void ProcessViewDataCallStart(
      const CensusViewProvider::ViewDataMap& view_data_map);

  // Processes call end metrics from view data.
  void ProcessViewDataCallEnd(
      const CensusViewProvider::ViewDataMap& view_data_map);

  // Processes other call metrics from view data.
  void ProcessViewDataOtherCallMetrics(
      const CensusViewProvider::ViewDataMap& view_data_map);

  // Checks if a feedback record is within the current time window.
  bool IsRecordInWindow(const LoadBalancingFeedbackRecord& record,
                        std::chrono::system_clock::time_point now) {
    return record.end_time > now - feedback_sample_window_seconds_;
  }

  // Adds a new feedback record to the history.
  void AppendNewFeedbackRecord(uint64_t rpcs, uint64_t errors);

  // Attaches orphan load IDs to the load report.
  void AttachOrphanLoadId(grpc::lb::v1::Load* load,
                          const PerBalancerStore& per_balancer_store);

  // Counter for generating unique load balancer IDs.
  std::atomic<int64_t> next_lb_id_{0};
  // Duration to keep feedback samples.
  const std::chrono::seconds feedback_sample_window_seconds_;
  // Mutex for protecting feedback records.
  grpc_core::Mutex feedback_mu_;
  // Queue of historical feedback records.
  std::deque<LoadBalancingFeedbackRecord> feedback_records_;

  // Mutex for protecting load data store.
  grpc_core::Mutex store_mu_;
  // Storage for load data.
  LoadDataStore load_data_store_;
  // Provider for census data.
  std::unique_ptr<CensusViewProvider> census_view_provider_;
  // Provider for CPU statistics.
  std::unique_ptr<CpuStatsProvider> cpu_stats_provider_;
};

}  // namespace load_reporter
}  // namespace grpc

#endif
```