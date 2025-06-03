Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_GRPC_LIBRARY_H
#define GRPCPP_IMPL_GRPC_LIBRARY_H

// Include necessary gRPC headers
#include <grpc/grpc.h>               // Core gRPC functionality
#include <grpcpp/impl/codegen/config.h>  // gRPC C++ configuration

#include <iostream>  // Standard I/O operations

// Main gRPC namespace
namespace grpc {

// Internal implementation details namespace
namespace internal {

// Class responsible for managing gRPC library initialization and shutdown
class GrpcLibrary {
 public:
  // Constructor that optionally initializes the gRPC library
  // @param call_grpc_init: If true, initializes gRPC library on construction
  explicit GrpcLibrary(bool call_grpc_init = true) : grpc_init_called_(false) {
    if (call_grpc_init) {
      grpc_init();                  // Initialize gRPC library
      grpc_init_called_ = true;    // Mark initialization as done
    }
  }

  // Virtual destructor that ensures proper cleanup
  // If this instance initialized gRPC, it will shut it down
  virtual ~GrpcLibrary() {
    if (grpc_init_called_) {
      grpc_shutdown();  // Clean up gRPC library resources
    }
  }

 private:
  bool grpc_init_called_;  // Flag tracking whether we initialized gRPC
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPCPP_IMPL_GRPC_LIBRARY_H
```

Key improvements made:
1. Added detailed header guard explanation
2. Documented each include statement's purpose
3. Added clear class-level documentation
4. Detailed constructor parameters and behavior
5. Explained destructor's role in cleanup
6. Documented the purpose of the private member variable
7. Added namespace closing comments for better readability
8. Included parameter documentation for the constructor
9. Explained the virtual destructor's significance

The comments now provide a clear understanding of:
- The class's responsibility (library initialization management)
- The RAII (Resource Acquisition Is Initialization) pattern being used
- The conditional initialization behavior
- The cleanup guarantees
- The internal state tracking