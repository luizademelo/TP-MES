Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H
#define GRPCPP_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H

// Include necessary headers
#include <grpcpp/health_check_service_interface.h>  // Health check service interface
#include <grpcpp/impl/server_builder_option.h>     // ServerBuilderOption base class
#include <grpcpp/support/config.h>                 // gRPC configuration support

#include <memory>  // For std::unique_ptr

namespace grpc {

// A ServerBuilderOption implementation that adds health check service support
// to a gRPC server. This class allows configuring health checking functionality
// during server construction.
class HealthCheckServiceServerBuilderOption : public ServerBuilderOption {
 public:
  // Constructor that takes ownership of a HealthCheckServiceInterface implementation
  // Parameters:
  //   hc - unique_ptr to a HealthCheckServiceInterface implementation
  explicit HealthCheckServiceServerBuilderOption(
      std::unique_ptr<HealthCheckServiceInterface> hc);

  // Default destructor
  ~HealthCheckServiceServerBuilderOption() override {}

  // Updates the ChannelArguments with health check service configuration
  // Parameters:
  //   args - Pointer to ChannelArguments to be modified
  void UpdateArguments(ChannelArguments* args) override;

  // Updates the server builder plugins with health check service configuration
  // Parameters:
  //   plugins - Pointer to vector of ServerBuilderPlugin unique_ptrs to be modified
  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) override;

 private:
  // The health check service implementation that this option manages
  std::unique_ptr<HealthCheckServiceInterface> hc_;
};

}  // namespace grpc

#endif  // GRPCPP_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H
```

The comments explain:
1. The purpose of each include directive
2. The overall purpose of the class
3. Each public method's functionality and parameters
4. The private member variable's role
5. The header guard's purpose
6. The namespace declaration

The comments are kept concise while providing enough information for future maintainers to understand the code's functionality without having to dive into implementation details.