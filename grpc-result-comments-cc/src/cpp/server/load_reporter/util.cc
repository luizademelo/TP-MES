Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers for load reporting functionality
#include <grpc/load_reporting.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/ext/server_load_reporting.h>
#include <grpcpp/server_context.h>
#include <string.h>

// Standard library includes
#include <cmath>
#include <string>

// Include for logging functionality
#include "absl/log/log.h"

namespace grpc {
namespace load_reporter {
namespace experimental {

// Function to add load reporting cost metric to server context
// Parameters:
//   ctx - Pointer to the server context where the metric will be added
//   cost_name - Name of the cost metric being reported
//   cost_value - Numeric value of the cost metric
void AddLoadReportingCost(grpc::ServerContext* ctx,
                          const std::string& cost_name, double cost_value) {
  // Check if the cost value is a normal number (not NaN, infinite, etc.)
  if (std::isnormal(cost_value)) {
    // Create a buffer to store the binary representation of the metric
    std::string buf;
    // Resize buffer to hold both the cost value and name
    buf.resize(sizeof(cost_value) + cost_name.size());
    
    // Copy the binary representation of the cost value into the buffer
    memcpy(&(*buf.begin()), &cost_value, sizeof(cost_value));
    // Copy the cost name string after the cost value in the buffer
    memcpy(&(*buf.begin()) + sizeof(cost_value), cost_name.data(),
           cost_name.size());
    
    // Add the cost metric as trailing metadata to the server context
    // using the predefined gRPC load balancing cost metadata key
    ctx->AddTrailingMetadata(GRPC_LB_COST_MD_KEY, buf);
  } else {
    // Log an error if the cost value is not a normal number
    LOG(ERROR) << "Call metric value is not normal.";
  }
}

}  // namespace experimental
}  // namespace load_reporter
}  // namespace grpc
```