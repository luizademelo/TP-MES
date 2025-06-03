Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Core I/O manager port definitions
#include "src/core/lib/iomgr/port.h"

// Only compile this file for POSIX socket-based I/O manager
#ifdef GRPC_POSIX_SOCKET_IOMGR

// POSIX-specific event and I/O management headers
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolve_address_posix.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/tcp_posix.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/timer.h"

// External declarations of POSIX-specific virtual function tables
extern grpc_tcp_server_vtable grpc_posix_tcp_server_vtable;
extern grpc_tcp_client_vtable grpc_posix_tcp_client_vtable;
extern grpc_timer_vtable grpc_generic_timer_vtable;
extern grpc_pollset_vtable grpc_posix_pollset_vtable;
extern grpc_pollset_set_vtable grpc_posix_pollset_set_vtable;

/**
 * Initializes platform-specific I/O manager components.
 * - Sets up DNS resolver with native implementation
 * - Initializes wakeup file descriptor functionality
 * - Initializes event engine
 * - Initializes POSIX TCP functionality
 */
static void iomgr_platform_init(void) {
  grpc_core::ResetDNSResolver(std::make_unique<grpc_core::NativeDNSResolver>());
  grpc_wakeup_fd_global_init();
  grpc_event_engine_init();
  grpc_tcp_posix_init();
}

// No-op flush function for platform I/O manager
static void iomgr_platform_flush(void) {}

/**
 * Shuts down platform-specific I/O manager components.
 * - Shuts down POSIX TCP functionality
 * - Shuts down event engine
 * - Cleans up wakeup file descriptor functionality
 * - Resets DNS resolver
 */
static void iomgr_platform_shutdown(void) {
  grpc_tcp_posix_shutdown();
  grpc_event_engine_shutdown();
  grpc_wakeup_fd_global_destroy();
  grpc_core::ResetDNSResolver(nullptr);
}

// Shuts down all background closures in the I/O manager
static void iomgr_platform_shutdown_background_closure(void) {
  grpc_shutdown_background_closure();
}

// Checks if current thread is a background poller thread
static bool iomgr_platform_is_any_background_poller_thread(void) {
  return grpc_is_any_background_poller_thread();
}

/**
 * Adds a closure to be executed by a background poller thread.
 * @param closure The closure to execute
 * @param error Error handle to pass to the closure
 * @return true if the closure was successfully added, false otherwise
 */
static bool iomgr_platform_add_closure_to_background_poller(
    grpc_closure* closure, grpc_error_handle error) {
  return grpc_add_closure_to_background_poller(closure, error);
}

// Virtual function table for platform-specific I/O manager operations
static grpc_iomgr_platform_vtable vtable = {
    iomgr_platform_init,
    iomgr_platform_flush,
    iomgr_platform_shutdown,
    iomgr_platform_shutdown_background_closure,
    iomgr_platform_is_any_background_poller_thread,
    iomgr_platform_add_closure_to_background_poller};

/**
 * Sets up default POSIX implementations for various I/O manager components.
 * - Configures TCP client/server implementations
 * - Sets timer implementation
 * - Configures pollset and pollset-set implementations
 * - Initializes global TCP client functionality
 * - Sets the platform vtable for I/O management
 */
void grpc_set_default_iomgr_platform() {
  grpc_set_tcp_client_impl(&grpc_posix_tcp_client_vtable);
  grpc_set_tcp_server_impl(&grpc_posix_tcp_server_vtable);
  grpc_set_timer_impl(&grpc_generic_timer_vtable);
  grpc_set_pollset_vtable(&grpc_posix_pollset_vtable);
  grpc_set_pollset_set_vtable(&grpc_posix_pollset_set_vtable);
  grpc_tcp_client_global_init();
  grpc_set_iomgr_platform_vtable(&vtable);
}

/**
 * Checks if I/O manager should run operations in background threads.
 * @return true if either EventEngine callback completion queue is enabled
 *         or if the event engine is configured to run in background
 */
bool grpc_iomgr_run_in_background() {
  return grpc_core::IsEventEngineCallbackCqEnabled() ||
         grpc_event_engine_run_in_background();
}

#endif  // GRPC_POSIX_SOCKET_IOMGR
```