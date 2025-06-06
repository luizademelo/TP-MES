
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

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

extern grpc_tcp_server_vtable grpc_windows_tcp_server_vtable;
extern grpc_tcp_server_vtable grpc_windows_event_engine_tcp_server_vtable;
extern grpc_tcp_client_vtable grpc_windows_tcp_client_vtable;
extern grpc_timer_vtable grpc_generic_timer_vtable;
extern grpc_pollset_vtable grpc_windows_pollset_vtable;
extern grpc_pollset_set_vtable grpc_windows_pollset_set_vtable;

static void winsock_init(void) {
  WSADATA wsaData;
  int status = WSAStartup(MAKEWORD(2, 0), &wsaData);
  CHECK_EQ(status, 0);
}

static void winsock_shutdown(void) {
  int status = WSACleanup();
  CHECK_EQ(status, 0);
}

static void iomgr_platform_init(void) {
  winsock_init();
  grpc_iocp_init();
  grpc_pollset_global_init();
  grpc_wsa_socket_flags_init();
  grpc_core::ResetDNSResolver(std::make_unique<grpc_core::NativeDNSResolver>());
}

static void iomgr_platform_flush(void) { grpc_iocp_flush(); }

static void iomgr_platform_shutdown(void) {
  grpc_pollset_global_shutdown();
  grpc_iocp_shutdown();
  winsock_shutdown();
  grpc_core::ResetDNSResolver(nullptr);
}

static void iomgr_platform_shutdown_background_closure(void) {}

static bool iomgr_platform_is_any_background_poller_thread(void) {
  return false;
}

static bool iomgr_platform_add_closure_to_background_poller(
    grpc_closure* , grpc_error_handle ) {
  return false;
}

static grpc_iomgr_platform_vtable vtable = {
    iomgr_platform_init,
    iomgr_platform_flush,
    iomgr_platform_shutdown,
    iomgr_platform_shutdown_background_closure,
    iomgr_platform_is_any_background_poller_thread,
    iomgr_platform_add_closure_to_background_poller};

void grpc_set_default_iomgr_platform() {
  grpc_set_tcp_client_impl(&grpc_windows_tcp_client_vtable);
  if (grpc_core::IsEventEngineListenerEnabled()) {
    grpc_set_tcp_server_impl(&grpc_windows_event_engine_tcp_server_vtable);
  } else {
    grpc_set_tcp_server_impl(&grpc_windows_tcp_server_vtable);
  }
  grpc_set_timer_impl(&grpc_generic_timer_vtable);
  grpc_set_pollset_vtable(&grpc_windows_pollset_vtable);
  grpc_set_pollset_set_vtable(&grpc_windows_pollset_set_vtable);
  grpc_set_iomgr_platform_vtable(&vtable);
}

bool grpc_iomgr_run_in_background() {
  return grpc_core::IsEventEngineCallbackCqEnabled();
}

#endif
