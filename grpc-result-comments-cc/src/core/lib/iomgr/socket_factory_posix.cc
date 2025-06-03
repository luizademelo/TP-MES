Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

// This implementation is only compiled if GRPC_POSIX_SOCKET_SOCKET_FACTORY is defined
#ifdef GRPC_POSIX_SOCKET_SOCKET_FACTORY

#include <grpc/impl/grpc_types.h>
#include <grpc/support/sync.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/socket_factory_posix.h"
#include "src/core/util/useful.h"

// Initializes a socket factory with the given virtual table and sets initial refcount to 1
void grpc_socket_factory_init(grpc_socket_factory* factory,
                              const grpc_socket_factory_vtable* vtable) {
  factory->vtable = vtable;
  gpr_ref_init(&factory->refcount, 1);
}

// Creates a socket using the factory's virtual table implementation
int grpc_socket_factory_socket(grpc_socket_factory* factory, int domain,
                               int type, int protocol) {
  return factory->vtable->socket(factory, domain, type, protocol);
}

// Binds a socket using the factory's virtual table implementation
int grpc_socket_factory_bind(grpc_socket_factory* factory, int sockfd,
                             const grpc_resolved_address* addr) {
  return factory->vtable->bind(factory, sockfd, addr);
}

// Compares two socket factories first by address, then by vtable, and finally using the vtable's compare function
int grpc_socket_factory_compare(grpc_socket_factory* a,
                                grpc_socket_factory* b) {
  // First compare the factory pointers themselves
  int c = grpc_core::QsortCompare(a, b);
  if (c != 0) {
    grpc_socket_factory* sma = a;
    grpc_socket_factory* smb = b;
    // If different factories, compare their vtables
    c = grpc_core::QsortCompare(sma->vtable, smb->vtable);
    if (c == 0) {
      // If vtables are the same, use the vtable's compare function
      c = sma->vtable->compare(sma, smb);
    }
  }
  return c;
}

// Increments the factory's reference count and returns the factory
grpc_socket_factory* grpc_socket_factory_ref(grpc_socket_factory* factory) {
  gpr_ref(&factory->refcount);
  return factory;
}

// Decrements the factory's reference count and destroys it if count reaches zero
void grpc_socket_factory_unref(grpc_socket_factory* factory) {
  if (gpr_unref(&factory->refcount)) {
    factory->vtable->destroy(factory);
  }
}

// Copy function for socket factory argument - increments reference count
static void* socket_factory_arg_copy(void* p) {
  return grpc_socket_factory_ref(static_cast<grpc_socket_factory*>(p));
}

// Destroy function for socket factory argument - decrements reference count
static void socket_factory_arg_destroy(void* p) {
  grpc_socket_factory_unref(static_cast<grpc_socket_factory*>(p));
}

// Compare function for socket factory arguments
static int socket_factory_cmp(void* a, void* b) {
  return grpc_socket_factory_compare(static_cast<grpc_socket_factory*>(a),
                                     static_cast<grpc_socket_factory*>(b));
}

// Virtual table for socket factory arguments containing copy, destroy and compare functions
static const grpc_arg_pointer_vtable socket_factory_arg_vtable = {
    socket_factory_arg_copy, socket_factory_arg_destroy, socket_factory_cmp};

// Creates a channel argument from a socket factory
grpc_arg grpc_socket_factory_to_arg(grpc_socket_factory* factory) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_ARG_SOCKET_FACTORY), factory,
      &socket_factory_arg_vtable);
}

#endif
```

The comments explain:
1. The overall purpose of each function
2. The reference counting mechanism
3. The comparison logic between factories
4. The virtual table operations
5. The channel argument conversion
6. Memory management responsibilities

The comments are placed directly above the relevant code blocks and provide clear explanations of both the high-level purpose and implementation details where necessary.