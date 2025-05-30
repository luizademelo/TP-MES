
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_CFSTREAM_IOMGR

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/ev_apple.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolve_address_posix.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/tcp_posix.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/timer.h"

static const char* grpc_cfstream_env_var = "grpc_cfstream";
static const char* grpc_cfstream_run_loop_env_var = "GRPC_CFSTREAM_RUN_LOOP";

extern grpc_tcp_server_vtable grpc_posix_tcp_server_vtable;
extern grpc_tcp_client_vtable grpc_posix_tcp_client_vtable;
extern grpc_tcp_client_vtable grpc_cfstream_client_vtable;
extern grpc_timer_vtable grpc_generic_timer_vtable;
extern grpc_pollset_vtable grpc_posix_pollset_vtable;
extern grpc_pollset_set_vtable grpc_posix_pollset_set_vtable;

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

static grpc_iomgr_platform_vtable apple_vtable = {
    apple_iomgr_platform_init,
    apple_iomgr_platform_flush,
    apple_iomgr_platform_shutdown,
    apple_iomgr_platform_shutdown_background_closure,
    apple_iomgr_platform_is_any_background_poller_thread,
    apple_iomgr_platform_add_closure_to_background_poller};

namespace {
struct CFStreamEnv {
  bool enable_cfstream;
  bool enable_cfstream_run_loop;
};

CFStreamEnv ParseEnvForCFStream() {
  CFStreamEnv env;
  char* enable_cfstream_str = getenv(grpc_cfstream_env_var);
  env.enable_cfstream =
      enable_cfstream_str == nullptr || enable_cfstream_str[0] != '0';
  char* enable_cfstream_run_loop_str = getenv(grpc_cfstream_run_loop_env_var);

  env.enable_cfstream_run_loop = enable_cfstream_run_loop_str != nullptr &&
                                 enable_cfstream_run_loop_str[0] == '1';
  return env;
}

void MaybeInitializeTcpPosix(void) {
  CFStreamEnv env = ParseEnvForCFStream();
  if (!env.enable_cfstream || !env.enable_cfstream_run_loop) {
    grpc_tcp_posix_init();
  }
}

void MaybeShutdownTcpPosix(void) {
  CFStreamEnv env = ParseEnvForCFStream();
  if (!env.enable_cfstream || !env.enable_cfstream_run_loop) {
    grpc_tcp_posix_shutdown();
  }
}
}

static void iomgr_platform_init(void) {
  MaybeInitializeTcpPosix();
  grpc_wakeup_fd_global_init();
  grpc_event_engine_init();
}

static void iomgr_platform_flush(void) {}

static void iomgr_platform_shutdown(void) {
  grpc_event_engine_shutdown();
  grpc_wakeup_fd_global_destroy();
  MaybeShutdownTcpPosix();
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

static grpc_iomgr_platform_vtable vtable = {
    iomgr_platform_init,
    iomgr_platform_flush,
    iomgr_platform_shutdown,
    iomgr_platform_shutdown_background_closure,
    iomgr_platform_is_any_background_poller_thread,
    iomgr_platform_add_closure_to_background_poller};

void grpc_set_default_iomgr_platform() {
  CFStreamEnv env = ParseEnvForCFStream();
  if (!env.enable_cfstream) {

    grpc_set_tcp_client_impl(&grpc_posix_tcp_client_vtable);
    grpc_set_tcp_server_impl(&grpc_posix_tcp_server_vtable);
    grpc_set_pollset_vtable(&grpc_posix_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_posix_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&vtable);
  } else if (env.enable_cfstream && !env.enable_cfstream_run_loop) {

    grpc_set_tcp_client_impl(&grpc_cfstream_client_vtable);
    grpc_set_tcp_server_impl(&grpc_posix_tcp_server_vtable);
    grpc_set_pollset_vtable(&grpc_posix_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_posix_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&vtable);
  } else {

    grpc_set_tcp_client_impl(&grpc_cfstream_client_vtable);
    grpc_set_pollset_vtable(&grpc_apple_pollset_vtable);
    grpc_set_pollset_set_vtable(&grpc_apple_pollset_set_vtable);
    grpc_set_iomgr_platform_vtable(&apple_vtable);
  }
  grpc_tcp_client_global_init();
  grpc_set_timer_impl(&grpc_generic_timer_vtable);
  grpc_core::ResetDNSResolver(std::make_unique<grpc_core::NativeDNSResolver>());
}

bool grpc_iomgr_run_in_background() {
  if (grpc_core::IsEventEngineCallbackCqEnabled()) {
    return true;
  }
  char* enable_cfstream_str = getenv(grpc_cfstream_env_var);
  bool enable_cfstream =
      enable_cfstream_str == nullptr || enable_cfstream_str[0] != '0';
  char* enable_cfstream_run_loop_str = getenv(grpc_cfstream_run_loop_env_var);

  bool enable_cfstream_run_loop = enable_cfstream_run_loop_str != nullptr &&
                                  enable_cfstream_run_loop_str[0] == '1';
  if (enable_cfstream && enable_cfstream_run_loop) {
    return false;
  } else {
    return grpc_event_engine_run_in_background();
  }
}

#endif
