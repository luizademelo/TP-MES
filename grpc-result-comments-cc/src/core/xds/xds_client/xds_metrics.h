Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_METRICS_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_METRICS_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_core {

// Abstract base class for reporting XDS client metrics.
// Implementations should provide concrete reporting logic for XDS-related metrics.
class XdsMetricsReporter {
 public:
  // Virtual destructor to ensure proper cleanup of derived classes.
  virtual ~XdsMetricsReporter() = default;

  // Reports updates to XDS resources.
  // Parameters:
  //   xds_server: The XDS server that provided the resources
  //   resource_type: Type of the XDS resource (e.g., listener, route configuration)
  //   num_valid: Number of valid resources received
  //   num_invalid: Number of invalid resources received
  virtual void ReportResourceUpdates(absl::string_view xds_server,
                                     absl::string_view resource_type,
                                     uint64_t num_valid,
                                     uint64_t num_invalid) = 0;

  // Reports a failure in communication with an XDS server.
  // Parameters:
  //   xds_server: The XDS server that failed
  virtual void ReportServerFailure(absl::string_view xds_server) = 0;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_METRICS_H
```

The comments added explain:
1. The overall purpose of the XdsMetricsReporter class
2. The virtual destructor's role
3. Each method's purpose and parameters
4. The expected usage of the abstract interface
5. Namespace closing comment
6. Header guard closing comment

The comments are designed to help future developers understand:
- What metrics are being tracked
- How to implement a concrete metrics reporter
- The contract that derived classes must fulfill
- The meaning of each parameter in the reporting methods