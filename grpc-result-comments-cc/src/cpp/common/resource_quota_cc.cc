Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/resource_quota.h>
#include <stddef.h>

#include <string>

namespace grpc {

// Constructor for ResourceQuota with default name (nullptr)
// Creates a new gRPC resource quota instance with no specific name
ResourceQuota::ResourceQuota() : impl_(grpc_resource_quota_create(nullptr)) {}

// Constructor for ResourceQuota with a specific name
// Creates a new gRPC resource quota instance with the given name
// @param name: The name to associate with this resource quota
ResourceQuota::ResourceQuota(const std::string& name)
    : impl_(grpc_resource_quota_create(name.c_str())) {}

// Destructor for ResourceQuota
// Releases the reference to the underlying gRPC resource quota instance
ResourceQuota::~ResourceQuota() { grpc_resource_quota_unref(impl_); }

// Resizes the resource quota to the specified new size
// @param new_size: The new size to set for the resource quota
// @return: Reference to this ResourceQuota object for method chaining
ResourceQuota& ResourceQuota::Resize(size_t new_size) {
  grpc_resource_quota_resize(impl_, new_size);
  return *this;
}

// Sets the maximum number of threads allowed for this resource quota
// @param new_max_threads: The new maximum thread count
// @return: Reference to this ResourceQuota object for method chaining
ResourceQuota& ResourceQuota::SetMaxThreads(int new_max_threads) {
  grpc_resource_quota_set_max_threads(impl_, new_max_threads);
  return *this;
}

}  // namespace grpc
```

The comments explain:
1. The purpose of each constructor and their differences
2. The destructor's cleanup responsibility
3. The functionality of each method, including their parameters and return values
4. The method chaining pattern used in the Resize and SetMaxThreads methods
5. The connection to the underlying gRPC C API functions

I've maintained the original code structure while adding explanatory comments that would help future developers understand and maintain this resource quota implementation.