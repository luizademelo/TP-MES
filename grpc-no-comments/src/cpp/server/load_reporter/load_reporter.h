
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

class CensusViewProvider {
 public:

  using ViewDataMap =
      std::unordered_map<std::string, ::opencensus::stats::ViewData>;

  using ViewDescriptorMap =
      std::unordered_map<std::string, ::opencensus::stats::ViewDescriptor>;

  CensusViewProvider();
  virtual ~CensusViewProvider() = default;

  virtual ViewDataMap FetchViewData() = 0;

  static double GetRelatedViewDataRowDouble(
      const ViewDataMap& view_data_map, const char* view_name,
      size_t view_name_len, const std::vector<std::string>& tag_values);
  static uint64_t GetRelatedViewDataRowInt(
      const ViewDataMap& view_data_map, const char* view_name,
      size_t view_name_len, const std::vector<std::string>& tag_values);

 protected:
  const ViewDescriptorMap& view_descriptor_map() const {
    return view_descriptor_map_;
  }

 private:
  ViewDescriptorMap view_descriptor_map_;

  ::opencensus::tags::TagKey tag_key_token_;
  ::opencensus::tags::TagKey tag_key_host_;
  ::opencensus::tags::TagKey tag_key_user_id_;
  ::opencensus::tags::TagKey tag_key_status_;
  ::opencensus::tags::TagKey tag_key_metric_name_;
};

class CensusViewProviderDefaultImpl : public CensusViewProvider {
 public:
  CensusViewProviderDefaultImpl();

  ViewDataMap FetchViewData() override;

 private:
  std::unordered_map<std::string, ::opencensus::stats::View> view_map_;
};

class CpuStatsProvider {
 public:

  using CpuStatsSample = std::pair<uint64_t, uint64_t>;

  virtual ~CpuStatsProvider() = default;

  virtual CpuStatsSample GetCpuStats() = 0;
};

class CpuStatsProviderDefaultImpl : public CpuStatsProvider {
 public:
  CpuStatsSample GetCpuStats() override;
};

class LoadReporter {
 public:

  LoadReporter(uint32_t feedback_sample_window_seconds,
               std::unique_ptr<CensusViewProvider> census_view_provider,
               std::unique_ptr<CpuStatsProvider> cpu_stats_provider)
      : feedback_sample_window_seconds_(feedback_sample_window_seconds),
        census_view_provider_(std::move(census_view_provider)),
        cpu_stats_provider_(std::move(cpu_stats_provider)) {

    AppendNewFeedbackRecord(0, 0);
  }

  void FetchAndSample();

  ::google::protobuf::RepeatedPtrField<grpc::lb::v1::Load> GenerateLoads(
      const std::string& hostname, const std::string& lb_id);

  grpc::lb::v1::LoadBalancingFeedback GenerateLoadBalancingFeedback();

  void ReportStreamCreated(const std::string& hostname,
                           const std::string& lb_id,
                           const std::string& load_key);

  void ReportStreamClosed(const std::string& hostname,
                          const std::string& lb_id);

  std::string GenerateLbId();

  CensusViewProvider* census_view_provider() {
    return census_view_provider_.get();
  }
  CpuStatsProvider* cpu_stats_provider() { return cpu_stats_provider_.get(); }

 private:
  struct LoadBalancingFeedbackRecord {
    std::chrono::system_clock::time_point end_time;
    uint64_t rpcs;
    uint64_t errors;
    uint64_t cpu_usage;
    uint64_t cpu_limit;

    LoadBalancingFeedbackRecord(
        const std::chrono::system_clock::time_point& end_time, uint64_t rpcs,
        uint64_t errors, uint64_t cpu_usage, uint64_t cpu_limit)
        : end_time(end_time),
          rpcs(rpcs),
          errors(errors),
          cpu_usage(cpu_usage),
          cpu_limit(cpu_limit) {}
  };

  void ProcessViewDataCallStart(
      const CensusViewProvider::ViewDataMap& view_data_map);

  void ProcessViewDataCallEnd(
      const CensusViewProvider::ViewDataMap& view_data_map);

  void ProcessViewDataOtherCallMetrics(
      const CensusViewProvider::ViewDataMap& view_data_map);

  bool IsRecordInWindow(const LoadBalancingFeedbackRecord& record,
                        std::chrono::system_clock::time_point now) {
    return record.end_time > now - feedback_sample_window_seconds_;
  }

  void AppendNewFeedbackRecord(uint64_t rpcs, uint64_t errors);

  void AttachOrphanLoadId(grpc::lb::v1::Load* load,
                          const PerBalancerStore& per_balancer_store);

  std::atomic<int64_t> next_lb_id_{0};
  const std::chrono::seconds feedback_sample_window_seconds_;
  grpc_core::Mutex feedback_mu_;
  std::deque<LoadBalancingFeedbackRecord> feedback_records_;

  grpc_core::Mutex store_mu_;
  LoadDataStore load_data_store_;
  std::unique_ptr<CensusViewProvider> census_view_provider_;
  std::unique_ptr<CpuStatsProvider> cpu_stats_provider_;
};

}
}

#endif
