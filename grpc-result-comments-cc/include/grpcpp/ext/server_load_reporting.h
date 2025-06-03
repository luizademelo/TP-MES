Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_EXT_SERVER_LOAD_REPORTING_H
#define GRPCPP_EXT_SERVER_LOAD_REPORTING_H

// Include necessary headers
#include <grpc/load_reporting.h>               // Core gRPC load reporting functionality
#include <grpc/support/port_platform.h>        // Platform-specific configuration
#include <grpcpp/impl/server_builder_option.h> // ServerBuilderOption interface
#include <grpcpp/server_context.h>             // Server context utilities
#include <grpcpp/support/config.h>             // gRPC C++ configuration

namespace grpc {
namespace load_reporter {
namespace experimental {

// A ServerBuilderOption implementation for enabling load reporting service
// This class allows configuring server channels with load reporting capabilities
class LoadReportingServiceServerBuilderOption
    : public grpc::ServerBuilderOption {
 public:
  // Updates channel arguments to enable load reporting
  // @param args Pointer to ChannelArguments to be modified
  void UpdateArguments(grpc::ChannelArguments* args) override;

  // Updates server builder plugins to include load reporting functionality
  // @param plugins Pointer to vector of ServerBuilderPlugin unique pointers
  void UpdatePlugins(std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>>*
                         plugins) override;
};

// Adds a load reporting cost metric to the current RPC context
// This allows servers to report custom cost metrics associated with processing RPCs
// @param ctx The server context for the current RPC
// @param cost_name The name/identifier of the cost metric
// @param cost_value The numeric value of the cost metric
void AddLoadReportingCost(grpc::ServerContext* ctx,
                          const std::string& cost_name, double cost_value);

}  // namespace experimental
}  // namespace load_reporter
}  // namespace grpc

#endif  // GRPCPP_EXT_SERVER_LOAD_REPORTING_H
```

Key improvements made:
1. Added detailed header guard comment
2. Documented each include statement's purpose
3. Added comprehensive class-level documentation for LoadReportingServiceServerBuilderOption
4. Added detailed parameter documentation for all methods
5. Added clear namespace closing comments
6. Explained the purpose of each function and its parameters
7. Maintained consistent formatting while adding comments
8. Added note about custom cost metrics in AddLoadReportingCost function

The comments now provide clear context about:
- What each component does
- How the pieces fit together
- The purpose of each parameter
- The relationship between the different elements
- The overall functionality of the load reporting system