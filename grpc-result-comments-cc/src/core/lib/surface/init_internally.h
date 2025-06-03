Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_INIT_INTERNALLY_H
#define GRPC_SRC_CORE_LIB_SURFACE_INIT_INTERNALLY_H

namespace grpc_core {

// Function pointers for internal gRPC initialization management:
// - InitInternally: Initializes gRPC internals
// - ShutdownInternally: Shuts down gRPC internals
// - IsInitializedInternally: Checks if gRPC is initialized
extern void (*InitInternally)();
extern void (*ShutdownInternally)();
extern bool (*IsInitializedInternally)();

// RAII (Resource Acquisition Is Initialization) class for managing gRPC initialization state.
// Ensures proper initialization and shutdown of gRPC internals during its lifetime.
class KeepsGrpcInitialized {
 public:
  // Constructor that optionally initializes gRPC
  // @param enabled: If true, initializes gRPC immediately. If false, does nothing.
  explicit KeepsGrpcInitialized(bool enabled = true) : enabled_(enabled) {
    if (enabled_) {
      InitInternally();
    }
  }

  // Destructor that shuts down gRPC if it was initialized by this instance
  ~KeepsGrpcInitialized() {
    if (enabled_) {
      ShutdownInternally();
    }
  }

  // Delete copy constructor and assignment operator to prevent multiple
  // instances from managing the same initialization state
  KeepsGrpcInitialized(const KeepsGrpcInitialized&) = delete;
  KeepsGrpcInitialized& operator=(const KeepsGrpcInitialized&) = delete;

 private:
  bool enabled_;  // Flag indicating whether this instance manages initialization
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_SURFACE_INIT_INTERNALLY_H
```

The comments explain:
1. The purpose of the function pointers for gRPC initialization management
2. The RAII pattern used by KeepsGrpcInitialized class
3. The constructor and destructor behavior
4. The reason for deleting copy operations
5. The purpose of the private member variable
6. The overall namespace and header guard structure

The comments are concise yet informative, helping future developers understand both the high-level purpose and implementation details of the code.