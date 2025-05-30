
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_BACKEND_METRICS_LB_POLICY_H
#define GRPC_TEST_CPP_INTEROP_BACKEND_METRICS_LB_POLICY_H

#include <grpc/support/port_platform.h>
#include <grpcpp/support/channel_arguments.h>

#include "src/core/config/core_configuration.h"
#include "src/proto/grpc/testing/messages.pb.h"

namespace grpc {
namespace testing {
class LoadReportTracker {
 public:

  using LoadReportEntry = std::optional<TestOrcaReport>;

  ChannelArguments GetChannelArguments();
  void ResetCollectedLoadReports();
  void RecordPerRpcLoadReport(
      const grpc_core::BackendMetricData* backend_metric_data);
  void RecordOobLoadReport(const grpc_core::BackendMetricData& oob_metric_data);

  std::optional<LoadReportEntry> GetNextLoadReport();
  LoadReportEntry WaitForOobLoadReport(
      const std::function<bool(const TestOrcaReport&)>& predicate,
      absl::Duration poll_timeout, size_t max_attempts);

 private:
  std::deque<LoadReportEntry> per_rpc_load_reports_
      ABSL_GUARDED_BY(load_reports_mu_);
  std::deque<TestOrcaReport> oob_load_reports_
      ABSL_GUARDED_BY(load_reports_mu_);
  grpc_core::Mutex load_reports_mu_;
  grpc_core::CondVar load_reports_cv_ ABSL_GUARDED_BY(load_reports_mu_);
};

void RegisterBackendMetricsLbPolicy(
    grpc_core::CoreConfiguration::Builder* builder);
}
}

#endif
