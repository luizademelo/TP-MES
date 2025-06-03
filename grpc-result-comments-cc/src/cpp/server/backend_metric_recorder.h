Here's the commented version of the code:

```c++
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

// Structure to hold backend metric data along with a sequence number
// for versioning/tracking updates.
struct ServerMetricRecorder::BackendMetricDataState {
  grpc_core::BackendMetricData data;  // Actual backend metric data
  uint64_t sequence_number = 0;       // Sequence number for tracking updates
};

}  // namespace experimental

// Class that implements both BackendMetricProvider and CallMetricRecorder
// interfaces to record and provide backend metrics for gRPC calls.
class BackendMetricState : public grpc_core::BackendMetricProvider,
                           public experimental::CallMetricRecorder {
 public:
  // Constructor that takes a pointer to the server metric recorder
  explicit BackendMetricState(
      experimental::ServerMetricRecorder* server_metric_recorder)
      : server_metric_recorder_(server_metric_recorder) {}

  // Metric recording methods that return CallMetricRecorder for method chaining

  // Records CPU utilization metric
  experimental::CallMetricRecorder& RecordCpuUtilizationMetric(
      double value) override;
  
  // Records memory utilization metric
  experimental::CallMetricRecorder& RecordMemoryUtilizationMetric(
      double value) override;
  
  // Records application-specific utilization metric
  experimental::CallMetricRecorder& RecordApplicationUtilizationMetric(
      double value) override;
  
  // Records queries per second (QPS) metric
  experimental::CallMetricRecorder& RecordQpsMetric(double value) override;
  
  // Records errors per second (EPS) metric
  experimental::CallMetricRecorder& RecordEpsMetric(double value) override;
  
  // Records a generic utilization metric with a custom name
  experimental::CallMetricRecorder& RecordUtilizationMetric(
      string_ref name, double value) override;
  
  // Records a request cost metric with a custom name
  experimental::CallMetricRecorder& RecordRequestCostMetric(
      string_ref name, double value) override;
  
  // Records a named metric with a custom name
  experimental::CallMetricRecorder& RecordNamedMetric(string_ref name,
                                                      double value) override;

  // Returns the collected backend metric data
  grpc_core::BackendMetricData GetBackendMetricData() override;

 private:
  // Pointer to the server metric recorder
  experimental::ServerMetricRecorder* server_metric_recorder_;
  
  // Atomic metric values (initialized to -1.0 indicating no value)
  std::atomic<double> cpu_utilization_{-1.0};           // CPU utilization value
  std::atomic<double> mem_utilization_{-1.0};           // Memory utilization value
  std::atomic<double> application_utilization_{-1.0};   // Application-specific utilization
  std::atomic<double> qps_{-1.0};                       // Queries per second
  std::atomic<double> eps_{-1.0};                       // Errors per second
  
  // Mutex-protected metric maps
  internal::Mutex mu_;
  std::map<absl::string_view, double> utilization_ ABSL_GUARDED_BY(mu_);   // Custom utilization metrics
  std::map<absl::string_view, double> request_cost_ ABSL_GUARDED_BY(mu_);  // Request cost metrics
  std::map<absl::string_view, double> named_metrics_ ABSL_GUARDED_BY(mu_); // Generic named metrics
};

}  // namespace grpc

#endif  // GRPC_SRC_CPP_SERVER_BACKEND_METRIC_RECORDER_H
```

Key improvements made:
1. Added detailed class and struct descriptions
2. Documented each public method's purpose
3. Explained the purpose of each member variable
4. Noted the significance of atomic variables and mutex-protected maps
5. Added comments about initialization values (-1.0 indicating no value)
6. Added namespace closing comments
7. Added header guard closing comment
8. Organized comments to follow a consistent style

The comments now provide clear documentation for future maintainers about:
- The overall purpose of the class
- What each method does
- The significance of different member variables
- Thread safety considerations (atomic variables and mutex usage)
- The structure of stored metric data