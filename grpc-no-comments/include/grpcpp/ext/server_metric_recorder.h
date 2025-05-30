
// Copyright 2023 gRPC authors.

#ifndef GRPCPP_EXT_SERVER_METRIC_RECORDER_H
#define GRPCPP_EXT_SERVER_METRIC_RECORDER_H

#include <grpcpp/impl/sync.h>
#include <grpcpp/support/string_ref.h>

#include <functional>
#include <map>
#include <memory>

namespace grpc_core {
struct BackendMetricData;
}

namespace grpc {
class BackendMetricState;

namespace experimental {

class ServerMetricRecorder {
 public:

  static std::unique_ptr<ServerMetricRecorder> Create();

  void SetCpuUtilization(double value);

  void SetMemoryUtilization(double value);

  void SetApplicationUtilization(double value);

  void SetQps(double value);

  void SetEps(double value);

  void SetNamedUtilization(string_ref name, double value);

  void SetAllNamedUtilization(std::map<string_ref, double> named_utilization);

  void ClearCpuUtilization();

  void ClearMemoryUtilization();

  void ClearApplicationUtilization();

  void ClearQps();

  void ClearEps();

  void ClearNamedUtilization(string_ref name);

 private:

  friend class grpc::BackendMetricState;
  friend class OrcaService;

  struct BackendMetricDataState;

  ServerMetricRecorder();

  void UpdateBackendMetricDataState(
      std::function<void(grpc_core::BackendMetricData*)> updater);

  grpc_core::BackendMetricData GetMetrics() const;

  std::shared_ptr<const BackendMetricDataState> GetMetricsIfChanged() const;

  mutable grpc::internal::Mutex mu_;
  std::shared_ptr<const BackendMetricDataState> metric_state_
      ABSL_GUARDED_BY(mu_);
};

}
}

#endif
