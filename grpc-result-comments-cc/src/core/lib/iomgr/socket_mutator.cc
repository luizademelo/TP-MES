Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/socket_mutator.h"

#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

// Initializes a socket mutator with the given virtual table and sets the initial
// reference count to 1.
void grpc_socket_mutator_init(grpc_socket_mutator* mutator,
                              const grpc_socket_mutator_vtable* vtable) {
  mutator->vtable = vtable;
  gpr_ref_init(&mutator->refcount, 1);
}

// Increments the reference count of the socket mutator and returns it.
grpc_socket_mutator* grpc_socket_mutator_ref(grpc_socket_mutator* mutator) {
  gpr_ref(&mutator->refcount);
  return mutator;
}

// Applies socket mutations based on the file descriptor usage type.
// For server connections, no mutation is applied (returns true).
// For client connections and server listeners, uses the vtable's mutate_fd function.
// If mutate_fd_2 is available in the vtable, uses that instead with additional info.
bool grpc_socket_mutator_mutate_fd(grpc_socket_mutator* mutator, int fd,
                                   grpc_fd_usage usage) {
  if (mutator->vtable->mutate_fd_2 != nullptr) {
    grpc_mutate_socket_info info{fd, usage};
    return mutator->vtable->mutate_fd_2(&info, mutator);
  }
  switch (usage) {
    case GRPC_FD_SERVER_CONNECTION_USAGE:
      return true;
    case GRPC_FD_CLIENT_CONNECTION_USAGE:
    case GRPC_FD_SERVER_LISTENER_USAGE:
      return mutator->vtable->mutate_fd(fd, mutator);
  }
  GPR_UNREACHABLE_CODE(return false);
}

// Compares two socket mutators first by their memory addresses,
// then by their vtable addresses, and finally using their vtable's compare function if needed.
int grpc_socket_mutator_compare(grpc_socket_mutator* a,
                                grpc_socket_mutator* b) {
  int c = grpc_core::QsortCompare(a, b);
  if (c != 0) {
    grpc_socket_mutator* sma = a;
    grpc_socket_mutator* smb = b;
    c = grpc_core::QsortCompare(sma->vtable, smb->vtable);
    if (c == 0) {
      c = sma->vtable->compare(sma, smb);
    }
  }
  return c;
}

// Decrements the reference count of the socket mutator.
// If the count reaches zero, destroys the mutator using the vtable's destroy function.
void grpc_socket_mutator_unref(grpc_socket_mutator* mutator) {
  if (gpr_unref(&mutator->refcount)) {
    mutator->vtable->destroy(mutator);
  }
}

// Copies a socket mutator by incrementing its reference count.
static void* socket_mutator_arg_copy(void* p) {
  return grpc_socket_mutator_ref(static_cast<grpc_socket_mutator*>(p));
}

// Destroys a socket mutator argument by decrementing its reference count.
static void socket_mutator_arg_destroy(void* p) {
  grpc_socket_mutator_unref(static_cast<grpc_socket_mutator*>(p));
}

// Compares two socket mutator arguments using grpc_socket_mutator_compare.
static int socket_mutator_cmp(void* a, void* b) {
  return grpc_socket_mutator_compare(static_cast<grpc_socket_mutator*>(a),
                                     static_cast<grpc_socket_mutator*>(b));
}

// Virtual table for socket mutator arguments containing copy, destroy, and compare functions.
static const grpc_arg_pointer_vtable socket_mutator_arg_vtable = {
    socket_mutator_arg_copy, socket_mutator_arg_destroy, socket_mutator_cmp};

// Creates a channel argument from a socket mutator using the socket mutator argument vtable.
grpc_arg grpc_socket_mutator_to_arg(grpc_socket_mutator* mutator) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_ARG_SOCKET_MUTATOR), mutator,
      &socket_mutator_arg_vtable);
}
```