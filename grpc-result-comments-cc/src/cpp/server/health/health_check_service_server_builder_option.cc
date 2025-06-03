Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Includes necessary headers for health check service and server builder functionality
#include <grpcpp/ext/health_check_service_server_builder_option.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>    // For std::unique_ptr
#include <utility>   // For std::move
#include <vector>    // For std::vector

namespace grpc {

// Constructor for HealthCheckServiceServerBuilderOption
// Takes ownership of a HealthCheckServiceInterface implementation via unique_ptr
// Args:
//   hc - unique_ptr to a HealthCheckServiceInterface implementation
HealthCheckServiceServerBuilderOption::HealthCheckServiceServerBuilderOption(
    std::unique_ptr<HealthCheckServiceInterface> hc)
    : hc_(std::move(hc)) {}

// Updates ChannelArguments with the health check service interface
// Transfers ownership of the health check service to the channel arguments
// Args:
//   args - Pointer to ChannelArguments to be modified
void HealthCheckServiceServerBuilderOption::UpdateArguments(
    ChannelArguments* args) {
  // Sets the health check service interface in channel arguments
  // Releases ownership from hc_ and transfers it to the channel arguments
  args->SetPointer(kHealthCheckServiceInterfaceArg, hc_.release());
}

// Placeholder implementation for updating server builder plugins
// This implementation does nothing as health check service doesn't require plugin updates
// Args:
//   plugins - Vector of ServerBuilderPlugin unique_ptrs (unused)
void HealthCheckServiceServerBuilderOption::UpdatePlugins(
    std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) {}

}  // namespace grpc
```

The comments explain:
1. The purpose of each include directive
2. The constructor's role and parameter
3. The ownership transfer happening in UpdateArguments
4. The purpose (or lack thereof) of the empty UpdatePlugins method
5. The namespace closure

The comments are kept concise while providing all the important information about ownership semantics and the purpose of each method.