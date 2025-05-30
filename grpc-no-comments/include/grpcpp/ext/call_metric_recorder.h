
// Copyright 2022 gRPC authors.

#ifndef GRPCPP_EXT_CALL_METRIC_RECORDER_H
#define GRPCPP_EXT_CALL_METRIC_RECORDER_H

#include <grpcpp/impl/sync.h>
#include <grpcpp/support/slice.h>

#include <memory>
#include <string>

#include "absl/strings/string_view.h"

namespace grpc {
namespace experimental {

class CallMetricRecorder {
 public:
  virtual ~CallMetricRecorder() = default;

  virtual CallMetricRecorder& RecordCpuUtilizationMetric(double value) = 0;

  virtual CallMetricRecorder& RecordMemoryUtilizationMetric(double value) = 0;

  virtual CallMetricRecorder& RecordApplicationUtilizationMetric(
      double value) = 0;

  virtual CallMetricRecorder& RecordQpsMetric(double value) = 0;

  virtual CallMetricRecorder& RecordEpsMetric(double value) = 0;

  virtual CallMetricRecorder& RecordUtilizationMetric(string_ref name,
                                                      double value) = 0;

  virtual CallMetricRecorder& RecordRequestCostMetric(string_ref name,
                                                      double value) = 0;

  virtual CallMetricRecorder& RecordNamedMetric(string_ref name,
                                                double value) = 0;
};

}
}

#endif
