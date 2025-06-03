Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific includes and definitions
#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// Only compile this code for Windows Sockets (Winsock) implementation
#ifdef GRPC_WINSOCK_SOCKET

// Include necessary headers
#include "absl/log/check.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolve_address_windows.h"
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/util/crash.h"

// External declarations of platform-specific implementations
extern grpc_tcp_server_vtable grpc_windows_tcp_server_vtable;
extern grpc_tcp_server_vtable grpc_windows_event_engine_tcp_server_vtable;
extern grpc_tcp_client_vtable grpc_windows_tcp_client_vtable;
extern grpc_timer_vtable grpc_generic_timer_vtable;
extern grpc_pollset_vtable grpc_windows_pollset_vtable;
extern grpc_pollset_set_vtable grpc_windows_pollset_set_vtable;

// Initialize Windows Sockets API (Winsock)
static void winsock_init(void) {
  WSADATA wsaData;
  int status = WSAStartup(MAKEWORD(2, 0), &wsaData);
  CHECK_EQ(status, 0);  // Verify initialization succeeded
}

// Shutdown Windows Sockets API (Winsock)
static void winsock_shutdown(void) {
  int status = WSACleanup();
  CHECK_EQ(status, 0);  // Verify cleanup succeeded
}

// Initialize the I/O manager platform components
static void iomgr_platform_init(void) {
  winsock_init();  // Initialize Winsock
  grpc_iocp_init();  // Initialize IOCP (I/O Completion Port)
  grpc_pollset_global_init();  // Initialize pollset
  grpc_wsa_socket_flags_init();  // Initialize WSA socket flags
  // Reset DNS resolver to use Windows native implementation
  grpc_core::ResetDNSResolver(std::make_unique<grpc_core::NativeDNSResolver>());
}

// Flush any pending I/O operations
static void iomgr_platform_flush(void) { grpc_iocp_flush(); }

// Shutdown the I/O manager platform components
static void iomgr_platform_shutdown(void) {
  grpc_pollset_global_shutdown();  // Shutdown pollset
  grpc_iocp_shutdown();  // Shutdown IOCP
  winsock_shutdown();  // Shutdown Winsock
  grpc_core::ResetDNSResolver(nullptr);  // Reset DNS resolver
}

// No-op implementation for background closure shutdown
static void iomgr_platform_shutdown_background_closure(void) {}

// Check if current thread is a background poller thread (always false for Windows)
static bool iomgr_platform_is_any_background_poller_thread(void) {
  return false;
}

// Attempt to add closure to background poller (not supported on Windows)
static bool iomgr_platform_add_closure_to_background_poller(
    grpc_closure* , grpc_error_handle ) {
  return false;
}

// Platform-specific virtual function table for I/O manager
static grpc_iomgr_platform_vtable vtable = {
    iomgr_platform_init,
    iomgr_platform_flush,
    iomgr_platform_shutdown,
    iomgr_platform_shutdown_background_closure,
    iomgr_platform_is_any_background_poller_thread,
    iomgr_platform_add_closure_to_background_poller};

// Set default platform implementations for Windows
void grpc_set_default_iomgr_platform() {
  // Set TCP client implementation
  grpc_set_tcp_client_impl(&grpc_windows_tcp_client_vtable);
  
  // Set TCP server implementation based on whether EventEngine is enabled
  if (grpc_core::IsEventEngineListenerEnabled()) {
    grpc_set_tcp_server_impl(&grpc_windows_event_engine_tcp_server_vtable);
  } else {
    grpc_set_tcp_server_impl(&grpc_windows_tcp_server_vtable);
  }
  
  // Set timer, pollset, and pollset_set implementations
  grpc_set_timer_impl(&grpc_generic_timer_vtable);
  grpc_set_pollset_vtable(&grpc_windows_pollset_vtable);
  grpc_set_pollset_set_vtable(&grpc_windows_pollset_set_vtable);
  
  // Set the platform-specific vtable
  grpc_set_iomgr_platform_vtable(&vtable);
}

// Check if I/O manager should run in background (based on EventEngine setting)
bool grpc_iomgr_run_in_background() {
  return grpc_core::IsEventEngineCallbackCqEnabled();
}

#endif  // GRPC_WINSOCK_SOCKET
```