Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CALL_HOOK_H
#define GRPCPP_IMPL_CALL_HOOK_H

namespace grpc {

namespace internal {
// Forward declarations of classes used in this header
class CallOpSetInterface;
class Call;

// Abstract base class for call hook functionality in gRPC.
// This class provides an interface for performing operations on gRPC calls.
class CallHook {
 public:
  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~CallHook() {}
  
  // Pure virtual function that must be implemented by derived classes.
  // Performs operations on a gRPC call using the provided operation set.
  // @param ops Pointer to the CallOpSetInterface containing operations to perform
  // @param call Pointer to the Call object on which to perform operations
  virtual void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) = 0;
};

} // namespace internal

} // namespace grpc

#endif // GRPCPP_IMPL_CALL_HOOK_H
```

The comments explain:
1. The purpose of the header guard
2. The namespace structure
3. The forward declarations
4. The abstract CallHook class and its virtual methods
5. The purpose of each method and its parameters
6. The closing of namespaces and header guard

The comments are concise yet informative, providing enough context for future maintainers to understand the purpose and usage of this interface without being overly verbose.