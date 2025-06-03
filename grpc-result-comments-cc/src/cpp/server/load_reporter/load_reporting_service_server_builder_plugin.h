Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTING_SERVICE_SERVER_BUILDER_PLUGIN_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTING_SERVICE_SERVER_BUILDER_PLUGIN_H

// Include necessary headers
#include <grpc/support/port_platform.h>  // Platform-specific configuration
#include <grpcpp/grpcpp.h>               // Core gRPC C++ functionality
#include <grpcpp/impl/server_builder_plugin.h>  // ServerBuilderPlugin interface
#include <grpcpp/server_builder.h>       // ServerBuilder class
#include <grpcpp/support/channel_arguments.h>  // ChannelArguments class

#include <memory>  // For std::shared_ptr and std::unique_ptr
#include <string>  // For std::string

// Load reporter service implementation
#include "src/cpp/server/load_reporter/load_reporter_async_service_impl.h"

namespace grpc {
namespace load_reporter {

// A ServerBuilderPlugin implementation for the Load Reporting Service.
// This plugin integrates the load reporting service with gRPC server initialization.
class LoadReportingServiceServerBuilderPlugin : public ServerBuilderPlugin {
 public:
  // Destructor override
  ~LoadReportingServiceServerBuilderPlugin() override = default;
  
  // Returns the name of this plugin
  std::string name() override { return "load_reporting_service"; }

  // Updates the ServerBuilder with this plugin's configuration
  void UpdateServerBuilder(ServerBuilder* builder) override;

  // Initializes the server with this plugin's services
  void InitServer(ServerInitializer* si) override;

  // Performs cleanup when server initialization is complete
  void Finish(ServerInitializer* si) override;

  // Placeholder for changing arguments (not implemented)
  void ChangeArguments(const std::string& , void* ) override {}
  
  // Placeholder for updating channel arguments (not implemented)
  void UpdateChannelArguments(grpc::ChannelArguments* ) override {}
  
  // Returns whether this plugin has synchronous methods
  bool has_sync_methods() const override;
  
  // Returns whether this plugin has asynchronous methods
  bool has_async_methods() const override;

 private:
  // The async service implementation for load reporting
  std::shared_ptr<LoadReporterAsyncServiceImpl> service_;
};

// Factory function to create an instance of LoadReportingServiceServerBuilderPlugin
std::unique_ptr<grpc::ServerBuilderPlugin>
CreateLoadReportingServiceServerBuilderPlugin();

}  // namespace load_reporter
}  // namespace grpc

// End of header guard
#endif  // GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTING_SERVICE_SERVER_BUILDER_PLUGIN_H
```

The comments explain:
1. The purpose of each include directive
2. The overall purpose of the class as a ServerBuilderPlugin for load reporting
3. The role of each method in the plugin lifecycle
4. The private member variable holding the service implementation
5. The factory function for creating plugin instances
6. The header guard purpose and structure

The comments maintain a consistent style and provide meaningful context without being overly verbose. They help future developers understand both the high-level purpose and specific implementation details of each component.