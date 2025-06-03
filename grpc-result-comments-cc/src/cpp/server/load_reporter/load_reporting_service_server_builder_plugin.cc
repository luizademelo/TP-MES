Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/cpp/server/load_reporter/load_reporting_service_server_builder_plugin.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/server_builder.h>

#include <utility>

namespace grpc {
namespace load_reporter {

// Returns whether the service has synchronous methods.
// If the service is not initialized (service_ is nullptr), returns false.
bool LoadReportingServiceServerBuilderPlugin::has_sync_methods() const {
  if (service_ != nullptr) {
    return service_->has_synchronous_methods();
  }
  return false;
}

// Returns whether the service has asynchronous methods.
// If the service is not initialized (service_ is nullptr), returns false.
bool LoadReportingServiceServerBuilderPlugin::has_async_methods() const {
  if (service_ != nullptr) {
    return service_->has_async_methods();
  }
  return false;
}

// Updates the ServerBuilder by adding a completion queue and creating
// a new LoadReporterAsyncServiceImpl instance with that queue.
void LoadReportingServiceServerBuilderPlugin::UpdateServerBuilder(
    grpc::ServerBuilder* builder) {
  auto cq = builder->AddCompletionQueue();
  service_ = std::make_shared<LoadReporterAsyncServiceImpl>(std::move(cq));
}

// Registers the load reporting service with the server initializer.
void LoadReportingServiceServerBuilderPlugin::InitServer(
    grpc::ServerInitializer* si) {
  si->RegisterService(service_);
}

// Starts the service thread and resets the service shared pointer.
// This is called during server shutdown/cleanup.
void LoadReportingServiceServerBuilderPlugin::Finish(
    grpc::ServerInitializer* ) {
  // Start the thread that will handle async operations
  service_->StartThread();
  // Release the service resources
  service_.reset();
}

}  // namespace load_reporter
}  // namespace grpc
```

The comments added explain:
1. The purpose of each method
2. The behavior when the service is not initialized (nullptr case)
3. What each method does in terms of server initialization and cleanup
4. The flow of operations during server setup and shutdown
5. Important operations like thread starting and resource cleanup

The comments are kept concise while providing enough information for future maintainers to understand the code's functionality without having to dive deep into implementation details.