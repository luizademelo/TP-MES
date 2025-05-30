
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_METRICS_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_METRICS_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_core {

class XdsMetricsReporter {
 public:
  virtual ~XdsMetricsReporter() = default;

  virtual void ReportResourceUpdates(absl::string_view xds_server,
                                     absl::string_view resource_type,
                                     uint64_t num_valid,
                                     uint64_t num_invalid) = 0;

  virtual void ReportServerFailure(absl::string_view xds_server) = 0;
};

}

#endif
