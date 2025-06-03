Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_RESOURCE_QUOTA_H
#define GRPCPP_RESOURCE_QUOTA_H

// Forward declaration of C-style resource quota structure
struct grpc_resource_quota;

// Include necessary gRPC headers
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/support/config.h>

namespace grpc {

// ResourceQuota class provides mechanisms to control resource allocation
// for gRPC channels. It inherits privately from GrpcLibrary to ensure
// proper initialization of gRPC library.
class ResourceQuota final : private grpc::internal::GrpcLibrary {
 public:
  // Constructor that creates a ResourceQuota with a specific name
  explicit ResourceQuota(const std::string& name);
  
  // Default constructor
  ResourceQuota();
  
  // Destructor (overrides base class virtual destructor)
  ~ResourceQuota() override;

  // Resizes the resource quota to the specified new size
  // Returns reference to self for method chaining
  ResourceQuota& Resize(size_t new_size);

  // Sets the maximum number of threads that can be allocated
  // Returns reference to self for method chaining
  ResourceQuota& SetMaxThreads(int new_max_threads);

  // Returns the underlying C-style resource quota object
  grpc_resource_quota* c_resource_quota() const { return impl_; }

 private:
  // Disabled copy constructor
  ResourceQuota(const ResourceQuota& rhs);
  
  // Disabled assignment operator
  ResourceQuota& operator=(const ResourceQuota& rhs);

  // Pointer to the underlying C implementation of resource quota
  grpc_resource_quota* const impl_;
};

}  // namespace grpc

#endif  // GRPCPP_RESOURCE_QUOTA_H
```

The comments explain:
1. The purpose of the class and its inheritance
2. Each public method's functionality and return behavior
3. The private implementation details and disabled operations
4. The role of the underlying C structure
5. Header guard and include explanations
6. Namespace boundary clarification

The comments are concise yet informative, providing both high-level understanding and specific details about the implementation choices.