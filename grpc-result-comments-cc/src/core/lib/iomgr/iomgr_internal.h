Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_IOMGR_INTERNAL_H
#define GRPC_SRC_CORE_LIB_IOMGR_IOMGR_INTERNAL_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"

// Structure representing an I/O manager object that can be linked in a doubly-linked list
typedef struct grpc_iomgr_object {
  char* name;                     // Name identifier for the object
  struct grpc_iomgr_object* next; // Pointer to next object in the list
  struct grpc_iomgr_object* prev; // Pointer to previous object in the list
} grpc_iomgr_object;

// Virtual function table for platform-specific I/O manager implementations
typedef struct grpc_iomgr_platform_vtable {
  void (*init)(void);                             // Initialization function
  void (*flush)(void);                            // Flush pending operations
  void (*shutdown)(void);                         // Shutdown I/O manager
  void (*shutdown_background_closure)(void);      // Shutdown background closures
  bool (*is_any_background_poller_thread)(void);  // Check if current thread is a background poller
  bool (*add_closure_to_background_poller)(grpc_closure* closure,
                                           grpc_error_handle error); // Add closure to background poller
} grpc_iomgr_platform_vtable;

// Registers an I/O manager object with the given name
void grpc_iomgr_register_object(grpc_iomgr_object* obj, const char* name);

// Unregisters an I/O manager object
void grpc_iomgr_unregister_object(grpc_iomgr_object* obj);

// Checks if the I/O manager platform has been determined
bool grpc_have_determined_iomgr_platform();

// Sets the platform-specific virtual function table for I/O management
void grpc_set_iomgr_platform_vtable(grpc_iomgr_platform_vtable* vtable);

// Sets the default I/O manager platform implementation
void grpc_set_default_iomgr_platform();

// Initializes the platform-specific I/O manager
void grpc_iomgr_platform_init(void);

// Flushes any pending operations in the platform-specific I/O manager
void grpc_iomgr_platform_flush(void);

// Shuts down the platform-specific I/O manager
void grpc_iomgr_platform_shutdown(void);

// Shuts down background closures in the platform-specific I/O manager
void grpc_iomgr_platform_shutdown_background_closure(void);

// Checks if current thread is a background poller thread in the platform implementation
bool grpc_iomgr_platform_is_any_background_poller_thread(void);

// Adds a closure to be executed by the background poller in the platform implementation
bool grpc_iomgr_platform_add_closure_to_background_poller(
    grpc_closure* closure, grpc_error_handle error);

// Returns whether to abort if I/O manager leaks are detected (for debugging)
bool grpc_iomgr_abort_on_leaks(void);

#endif  // GRPC_SRC_CORE_LIB_IOMGR_IOMGR_INTERNAL_H
```

The comments explain:
1. The purpose of each structure and its members
2. The functionality of each function
3. The overall role of this header file in managing I/O operations
4. The platform-specific nature of many of these operations
5. The debugging capability for leak detection

The comments are kept concise while providing enough information for maintenance developers to understand the code's purpose and functionality.