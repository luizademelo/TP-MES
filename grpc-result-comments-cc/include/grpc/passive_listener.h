Here's the commented version of the code:

```c++
// Copyright 2024 The gRPC Authors

// Header guard to prevent multiple inclusions
#ifndef GRPC_PASSIVE_LISTENER_H
#define GRPC_PASSIVE_LISTENER_H

// Include necessary headers
#include <grpc/event_engine/event_engine.h>  // For EventEngine functionality
#include <grpc/grpc.h>                       // Core gRPC functionality

#include <memory>  // For std::unique_ptr and std::shared_ptr

namespace grpc_core {
class Server;  // Forward declaration of Server class

namespace experimental {
// Forward declaration of implementation class
class PassiveListenerImpl;

// Abstract base class for passive listeners in gRPC
// Passive listeners accept incoming connections without actively listening on a port
class PassiveListener {
 public:
  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~PassiveListener() = default;

  // Pure virtual method to accept a connected endpoint
  // Takes ownership of the endpoint via unique_ptr
  // Returns absl::Status indicating success or failure
  virtual absl::Status AcceptConnectedEndpoint(
      std::unique_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
          endpoint) = 0;

  // Pure virtual method to accept a connected file descriptor
  // Takes a file descriptor representing the connection
  // Returns absl::Status indicating success or failure
  virtual absl::Status AcceptConnectedFd(int fd) = 0;
};

}  // namespace experimental
}  // namespace grpc_core

// Function to add a passive listener to a gRPC server
// Parameters:
//   server: The gRPC server to add the listener to
//   credentials: Server credentials for the connection
//   passive_listener: Shared pointer to the passive listener implementation
// Returns: absl::Status indicating success or failure of the operation
absl::Status grpc_server_add_passive_listener(
    grpc_core::Server* server, grpc_server_credentials* credentials,
    std::shared_ptr<grpc_core::experimental::PassiveListenerImpl>
        passive_listener);

#endif  // GRPC_PASSIVE_LISTENER_H
```

The comments explain:
1. The purpose of each section and component
2. The role of the PassiveListener abstract class
3. The functionality of each virtual method
4. The parameters and return values of the public API function
5. The relationships between components
6. Ownership semantics for smart pointers
7. The overall purpose of passive listeners in the gRPC system

The comments are designed to help future developers understand:
- How to implement a PassiveListener
- How to use the passive listener functionality
- The expected behavior of each component
- The memory management approach being used