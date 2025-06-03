Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_GCP_ENVIRONMENT_AUTODETECT_H
#define GRPC_SRC_CPP_EXT_GCP_ENVIRONMENT_AUTODETECT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/util/sync.h"

namespace grpc {

namespace internal {

// Initializes GCP Observability functionality
// Returns absl::Status indicating success or failure of initialization
absl::Status GcpObservabilityInit();

// Class for automatically detecting and managing GCP environment information
class EnvironmentAutoDetect {
 public:
  // Structure representing a GCP resource with its type and associated labels
  struct ResourceType {
    // The type of the GCP resource (e.g., "gce_instance", "gke_container")
    std::string resource_type;

    // Key-value pairs of labels associated with the resource
    std::map<std::string, std::string> labels;
  };

  // Returns the singleton instance of EnvironmentAutoDetect
  static EnvironmentAutoDetect& Get();

  // Constructs an EnvironmentAutoDetect instance with the specified GCP project ID
  explicit EnvironmentAutoDetect(std::string project_id);

  // Registers a callback to be invoked when environment detection is complete
  // The callback takes no arguments and returns void
  void NotifyOnDone(absl::AnyInvocable<void()> callback);

  // Returns the detected resource information
  // Thread-safe: uses mutex to protect access to resource_ member
  const ResourceType* resource() {
    grpc_core::MutexLock lock(&mu_);
    return resource_.get();
  }

 private:
  friend absl::Status grpc::internal::GcpObservabilityInit();

  // Creates the singleton instance with the specified GCP project ID
  static void Create(std::string project_id);

  // The GCP project ID this instance is associated with
  const std::string project_id_;

  // Event engine used for asynchronous operations
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;

  // Mutex for thread-safe access to resource_ and callbacks_
  grpc_core::Mutex mu_;

  // The detected GCP resource information (protected by mu_)
  std::unique_ptr<ResourceType> resource_ ABSL_GUARDED_BY(mu_);

  // Collection of callbacks to be invoked when detection is complete (protected by mu_)
  std::vector<absl::AnyInvocable<void()>> callbacks_ ABSL_GUARDED_BY(mu_);
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPC_SRC_CPP_EXT_GCP_ENVIRONMENT_AUTODETECT_H
```

The comments added explain:
1. The overall purpose of the class (GCP environment detection)
2. The ResourceType structure and its members
3. Each public method's functionality and thread safety considerations
4. Private members and their purposes
5. The role of synchronization mechanisms
6. The relationship with GcpObservabilityInit
7. The purpose of the callback system

The comments are designed to help future maintainers understand:
- What the code does
- How to use it
- Thread safety considerations
- The relationships between components
- The purpose of each member variable