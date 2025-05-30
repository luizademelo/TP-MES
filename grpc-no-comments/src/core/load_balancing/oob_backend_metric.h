
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_OOB_BACKEND_METRIC_H
#define GRPC_SRC_CORE_LOAD_BALANCING_OOB_BACKEND_METRIC_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/time.h"

namespace grpc_core {

class OobBackendMetricWatcher {
 public:
  virtual ~OobBackendMetricWatcher() = default;

  virtual void OnBackendMetricReport(
      const BackendMetricData& backend_metric_data) = 0;
};

std::unique_ptr<SubchannelInterface::DataWatcherInterface>
MakeOobBackendMetricWatcher(Duration report_interval,
                            std::unique_ptr<OobBackendMetricWatcher> watcher);

}

#endif
