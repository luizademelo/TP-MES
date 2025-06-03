Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific includes and configuration
#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// Only compile this code if GRPC_CFSTREAM_IOMGR is defined
#ifdef GRPC_CFSTREAM_IOMGR

// Core gRPC includes for I/O management
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/ev_apple.h"      // Apple-specific event handling
#include "src/core/lib/iomgr/ev_posix.h"      // POSIX event handling
#include "src/core/lib/iomgr/iomgr_internal.h" // Internal I/O manager interfaces
#include "src/core/lib/iomgr/resolve_address.h" // Address resolution
#include "src/core/lib/iomgr/resolve_address_posix.h" // POSIX address resolution
#include "src/core/lib/iomgr/tcp_client.h"     // TCP client implementation
#include "src/core/lib/iomgr/tcp_posix.h"      // POSIX TCP implementation
#include "src/core/lib/iomgr/tcp_server.h"     // TCP server implementation
#include "src/core/lib/iomgr/timer.h"          // Timer implementation

// Environment variables for configuring CFStream behavior
static const char* grpc_cfstream_env_var = "grpc_cfstream";
static const char* grpc_cfstream_run_loop_env_var = "GRPC_CFSTREAM_RUN_LOOP";

// External declarations of virtual function tables for various components
extern grpc_tcp_server_vtable grpc_posix_tcp_server_vtable;
extern grpc_tcp_client_vtable grpc_posix_tcp_client_vtable;
extern grpc_tcp_client_vtable grpc_cfstream_client_vtable;
extern grpc_timer_vtable grpc_generic_timer_vtable;
extern grpc_pollset_vtable grpc_posix_pollset_vtable;
extern grpc_pollset_set_vtable grpc_posix_pollset_set_vtable;

// Apple-specific I/O manager platform functions
static void apple_iomgr_platform_init(void) { grpc_pollset_global_init(); }
static void apple_iomgr_platform_flush(void) {}
static void apple_iomgr_platform_shutdown(void) {
  grpc_pollset_global_shutdown();
  grpc_core::ResetDNSResolver(nullptr);
}
static void apple_iomgr_platform_shutdown_background_closure(void) {}
static bool apple_iomgr_platform_is_any_background_poller_thread(void) {
  return false;
}
static bool apple_iomgr_platform_add_closure_to_background_poller(
    grpc_closure* , grpc_error_handle ) {
  return false;
}

// Virtual function table for Apple platform I/O manager
static grpc_iomgr_platform_vtable apple_vtable = {
    apple_iomgr_platform_init,
    apple_iomgr_platform_flush,
    apple_iomgr_platform_shutdown,
    apple_iomgr_platform_shutdown_background_closure,
    apple_iomgr_platform_is_any_background_poller_thread,
    apple_iomgr_platform_add_closure_to_background_poller};

namespace {
// Structure to hold CFStream configuration from environment variables
struct CFStreamEnv {
  bool enable_cfstream;            // Whether CFStream is enabled
  bool enable_cfstream_run_loop;   // Whether CFStream run loop is enabled
};

// Parses environment variables to determine CFStream configuration
CFStreamEnv ParseEnvForCFStream() {
  CFStreamEnv env;
  // Check if CFStream is enabled (defaults to true unless explicitly disabled)
  char* enable_cfstream_str = getenv(grpc_cfstream_env_var);
  env.enable_cfstream =
      enable_cfstream_str == nullptr || enable_cfstream_str[0] != '0';
  
  // Check if CFStream run loop is enabled (must be explicitly set to '1')
  char* enable_cfstream_run_loop_str = getenv(grpc_cfstream_run_loop_env_var);
  env.enable_cfstream_run_loop = enable_cfstream_run_loop_str != nullptr &&
                                 enable_cfstream_run_loop_str[0] == '1';
  return env;
}

// Initializes POSIX TCP implementation if CFStream is not fully enabled
void MaybeInitializeTcpPosix(void) {
  CFStreamEnv env = ParseEnvForCFStream();
  if (!env.enable_cfstream || !env.enable_cfstream_run_loop) {
    grpc_tcp_posix_init();
  }
}

// Shuts down POSIX TCP implementation if CFStream is not fully enabled
void MaybeShutdownTcpPosix(void) {
  CFStreamEnv env = ParseEnvForCFStream();
  if (!env.enable_cfstream || !env.enable_cfstream_run_loop) {
    grpc_tcp_posix_shutdown();
  }
}
} // namespace

// Default I/O manager platform functions
static void iomgr_platform_init(void) {
  MaybeInitializeTcpPosix();
  grpc_wakeup_fd_global_init();   // Initialize wakeup file descriptors
  grpc_event_engine_init();       // Initialize event engine
}

static void iomgr_platform_flush(void) {}

static void iomgr_platform_shutdown(void) {
  grpc_event_engine_shutdown();   // Shutdown event engine
  grpc_wakeup_fd_global_destroy(); // Cleanup wakeup file descriptors
  MaybeShutdownTcpPosix();        // Conditionally shutdown POSIX TCP
}

static void iomgr_platform_shutdown_background_closure(void) {
  grpc_shutdown_background_closure();
}

static bool iomgr_platform_is_any_background_poller_thread(void) {
  return grpc_is_any_background_poller_thread();
}

static bool iomgr_platform_add_closure_to_background_poller(
    grpc_closure* closure, grpc_error_handle error) {
  return grpc_add_closure_to_background_poller(closure, error);
}

// Virtual function table for default platform I/O manager
static grpc_iomgr_platform_vtable vtable = {
    iomgr_platform_init,
    iomgr_platform_flush,
    iomgr_platform_shutdown,
    iomgr_platform_shutdown_background_closure,
    iomgr_platform_is_any_background_poller_thread,
    iomgr_platform_add_closure_to_background_poller};

// Sets up the appropriate I/O manager implementation based on configuration
void grpc_set_default_iomgr_platform() {
  CFStreamEnv env = ParseEnvForCFStream();
  
  // Case 1: CFStream completely disabled - use POSIX implementations
  if (!env.enable_cfstream) {
    grpc_set_tcp_client_impl(&grpc_posix_tcp_client_vtable);
    grpc_set_tcp_server_impl(&grpc_posix_tcp_server_vtable);
    grpc_set_pollset_vtable(&grpc_posix_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_posix_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&vtable);
  } 
  // Case 2: CFStream enabled but run loop disabled - hybrid configuration
  else if (env.enable_cfstream && !env.enable_cfstream_run_loop) {
    grpc_set_tcp_client_impl(&grpc_cfstream_client_vtable);
    grpc_set_tcp_server_impl(&grpc_posix_tcp_server_vtable);
    grpc_set_pollset_vtable(&grpc_posix_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_posix_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&vtable);
  } 
  // Case 3: Full CFStream with run loop enabled - Apple-specific configuration
  else {
    grpc_set_tcp_client_impl(&grpc_cfstream_client_vtable);
    grpc_set_pollset_vtable(&grpc_apple_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_apple_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&apple_vtable);
  }
  
  // Common initialization for all configurations
  grpc_tcp_client_global_init();
  grpc_set_timer_impl(&grpc_generic_timer_vtable);
  grpc_core::ResetDNSResolver(std::make_unique<grpc_core::NativeDNSResolver>());
}

// Determines whether I/O manager should run in background based on configuration
bool grpc_iomgr_run_in_background() {
  // EventEngine callback CQ takes precedence
  if (grpc_core::IsEventEngineCallbackCqEnabled()) {
    return true;
  }
  
  // Check CFStream configuration from environment
  char* enable_cfstream_str = getenv(grpc_cfstream_env_var);
  bool enable_cfstream =
      enable_cfstream_str == nullptr || enable_cfstream_str[0] != '0';
  char* enable_cfstream_run_loop_str = getenv(grpc_cfstream_run_loop_env_var);

  bool enable_cfstream_run_loop = enable_cfstream_run_loop_str != nullptr &&
                                  enable_cfstream_run_loop_str[0] == '1';
  
  // Full CFStream with run loop runs in foreground, others in background
  if (enable_cfstream && enable_cfstream_run_loop) {
    return false;
  } else {
    return grpc_event_engine_run_in_background();
  }
}

#endif // GRPC_CFSTREAM_IOMGR
```