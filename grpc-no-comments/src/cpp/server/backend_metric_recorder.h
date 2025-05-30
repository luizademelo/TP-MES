
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_BACKEND_METRIC_RECORDER_H
#define GRPC_SRC_CPP_SERVER_BACKEND_METRIC_RECORDER_H

#include <grpcpp/ext/call_metric_recorder.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/string_ref.h>
#include <stdint.h>

#include <atomic>
#include <map>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/ext/filters/backend_metrics/backend_metric_provider.h"
#include "src/core/load_balancing/backend_metric_data.h"

namespace grpc {
namespace experimental {

struct ServerMetricRecorder::BackendMetricDataState {
  grpc_core::BackendMetricData data;
  uint64_t sequence_number = 0;
};

}

class BackendMetricState : public grpc_core::BackendMetricProvider,
                           public experimental::CallMetricRecorder {
 public:

  explicit BackendMetricState(
      experimental::ServerMetricRecorder* server_metric_recorder)
      : server_metric_recorder_(server_metric_recorder) {}
  experimental::CallMetricRecorder& RecordCpuUtilizationMetric(
      double value) override;
  experimental::CallMetricRecorder& RecordMemoryUtilizationMetric(
      double value) override;
  experimental::CallMetricRecorder& RecordApplicationUtilizationMetric(
      double value) override;
  experimental::CallMetricRecorder& RecordQpsMetric(double value) override;
  experimental::CallMetricRecorder& RecordEpsMetric(double value) override;
  experimental::CallMetricRecorder& RecordUtilizationMetric(
      string_ref name, double value) override;
  experimental::CallMetricRecorder& RecordRequestCostMetric(
      string_ref name, double value) override;
  experimental::CallMetricRecorder& RecordNamedMetric(string_ref name,
                                                      double value) override;

  grpc_core::BackendMetricData GetBackendMetricData() override;

 private:
  experimental::ServerMetricRecorder* server_metric_recorder_;
  std::atomic<double> cpu_utilization_{-1.0};
  std::atomic<double> mem_utilization_{-1.0};
  std::atomic<double> application_utilization_{-1.0};
  std::atomic<double> qps_{-1.0};
  std::atomic<double> eps_{-1.0};
  internal::Mutex mu_;
  std::map<absl::string_view, double> utilization_ ABSL_GUARDED_BY(mu_);
  std::map<absl::string_view, double> request_cost_ ABSL_GUARDED_BY(mu_);
  std::map<absl::string_view, double> named_metrics_ ABSL_GUARDED_BY(mu_);
};

}

#endif
