Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/pollset_set.h"
#include <grpc/support/port_platform.h>

// Global variable holding the virtual function table for pollset set operations
grpc_pollset_set_vtable* grpc_pollset_set_impl;

// Sets the implementation vtable for pollset set operations
// This allows for different implementations to be plugged in
// @param vtable Pointer to the vtable structure containing implementation functions
void grpc_set_pollset_set_vtable(grpc_pollset_set_vtable* vtable) {
  grpc_pollset_set_impl = vtable;
}

// Creates a new pollset set using the registered implementation
// @return Pointer to the newly created pollset set
grpc_pollset_set* grpc_pollset_set_create() {
  return grpc_pollset_set_impl->create();
}

// Destroys a pollset set using the registered implementation
// @param pollset_set Pointer to the pollset set to be destroyed
void grpc_pollset_set_destroy(grpc_pollset_set* pollset_set) {
  grpc_pollset_set_impl->destroy(pollset_set);
}

// Adds a pollset to a pollset set using the registered implementation
// @param pollset_set The pollset set to which the pollset will be added
// @param pollset The pollset to add to the set
void grpc_pollset_set_add_pollset(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset) {
  grpc_pollset_set_impl->add_pollset(pollset_set, pollset);
}

// Removes a pollset from a pollset set using the registered implementation
// @param pollset_set The pollset set from which the pollset will be removed
// @param pollset The pollset to remove from the set
void grpc_pollset_set_del_pollset(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset) {
  grpc_pollset_set_impl->del_pollset(pollset_set, pollset);
}

// Adds a pollset set to another pollset set (bag) using the registered implementation
// This is typically used to combine multiple pollset sets
// @param bag The destination pollset set
// @param item The pollset set to be added to the bag
void grpc_pollset_set_add_pollset_set(grpc_pollset_set* bag,
                                      grpc_pollset_set* item) {
  grpc_pollset_set_impl->add_pollset_set(bag, item);
}

// Removes a pollset set from another pollset set (bag) using the registered implementation
// @param bag The destination pollset set
// @param item The pollset set to be removed from the bag
void grpc_pollset_set_del_pollset_set(grpc_pollset_set* bag,
                                      grpc_pollset_set* item) {
  grpc_pollset_set_impl->del_pollset_set(bag, item);
}
```

The comments explain:
1. The purpose of each function
2. The parameters and their roles
3. The return values where applicable
4. The relationship between the functions and the implementation vtable
5. The overall pattern of delegation to implementation-specific functions

The comments maintain a consistent style and provide enough information for future maintainers to understand the code's functionality without being overly verbose.