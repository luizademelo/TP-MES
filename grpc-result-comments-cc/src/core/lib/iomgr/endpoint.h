Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"

// Forward declarations for endpoint structures
typedef struct grpc_endpoint grpc_endpoint;
typedef struct grpc_endpoint_vtable grpc_endpoint_vtable;

// Virtual function table for endpoint operations
// This defines the interface that all endpoint implementations must support
struct grpc_endpoint_vtable {
  // Function pointer for asynchronous read operation
  // ep: endpoint to read from
  // slices: buffer to store read data
  // cb: callback to invoke when read completes
  // urgent: indicates if this is an urgent read
  // min_progress_size: minimum progress size for the read operation
  void (*read)(grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
               bool urgent, int min_progress_size);

  // Function pointer for asynchronous write operation
  // ep: endpoint to write to
  // slices: data to write
  // cb: callback to invoke when write completes
  // args: additional write arguments
  void (*write)(
      grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
      grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args);

  // Function to add endpoint to a pollset for event notification
  void (*add_to_pollset)(grpc_endpoint* ep, grpc_pollset* pollset);

  // Function to add endpoint to a pollset set for event notification
  void (*add_to_pollset_set)(grpc_endpoint* ep, grpc_pollset_set* pollset);

  // Function to remove endpoint from a pollset set
  void (*delete_from_pollset_set)(grpc_endpoint* ep, grpc_pollset_set* pollset);

  // Function to destroy/cleanup endpoint resources
  void (*destroy)(grpc_endpoint* ep);

  // Function to get peer address/name
  absl::string_view (*get_peer)(grpc_endpoint* ep);

  // Function to get local address
  absl::string_view (*get_local_address)(grpc_endpoint* ep);

  // Function to get file descriptor (if applicable)
  int (*get_fd)(grpc_endpoint* ep);

  // Function to check if endpoint can track errors
  bool (*can_track_err)(grpc_endpoint* ep);
};

// Public API functions for endpoint operations:

// Initiates an asynchronous read operation on the endpoint
void grpc_endpoint_read(grpc_endpoint* ep, grpc_slice_buffer* slices,
                        grpc_closure* cb, bool urgent, int min_progress_size);

// Gets the peer address/name of the endpoint
absl::string_view grpc_endpoint_get_peer(grpc_endpoint* ep);

// Gets the local address of the endpoint
absl::string_view grpc_endpoint_get_local_address(grpc_endpoint* ep);

// Gets the file descriptor associated with the endpoint (if applicable)
int grpc_endpoint_get_fd(grpc_endpoint* ep);

// Initiates an asynchronous write operation on the endpoint
void grpc_endpoint_write(
    grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
    grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs arg);

// Destroys/cleans up the endpoint
void grpc_endpoint_destroy(grpc_endpoint* ep);

// Adds the endpoint to a pollset for event notification
void grpc_endpoint_add_to_pollset(grpc_endpoint* ep, grpc_pollset* pollset);

// Adds the endpoint to a pollset set for event notification
void grpc_endpoint_add_to_pollset_set(grpc_endpoint* ep,
                                      grpc_pollset_set* pollset_set);

// Removes the endpoint from a pollset set
void grpc_endpoint_delete_from_pollset_set(grpc_endpoint* ep,
                                           grpc_pollset_set* pollset_set);

// Checks if the endpoint can track errors
bool grpc_endpoint_can_track_err(grpc_endpoint* ep);

// Base endpoint structure
struct grpc_endpoint {
  // Virtual function table containing all endpoint operations
  const grpc_endpoint_vtable* vtable;

  // Convenience method to destroy the endpoint
  void Orphan() { grpc_endpoint_destroy(this); }
};

#endif  // GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_H
```

The comments explain:
1. The purpose of each structure and function
2. The parameters for each function
3. The relationship between the vtable and concrete implementations
4. The overall architecture of the endpoint abstraction
5. The role of each API function in the endpoint interface

The comments are designed to help future developers understand:
- How to implement a new endpoint type
- How to use the existing endpoint API
- The expected behavior of each endpoint operation
- The relationship between different components of the endpoint system