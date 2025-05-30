
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/iomgr_internal.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

static grpc_iomgr_platform_vtable* iomgr_platform_vtable = nullptr;

bool grpc_have_determined_iomgr_platform() {
  return iomgr_platform_vtable != nullptr;
}

void grpc_set_iomgr_platform_vtable(grpc_iomgr_platform_vtable* vtable) {
  iomgr_platform_vtable = vtable;
}

void grpc_iomgr_platform_init() { iomgr_platform_vtable->init(); }

void grpc_iomgr_platform_flush() { iomgr_platform_vtable->flush(); }

void grpc_iomgr_platform_shutdown() { iomgr_platform_vtable->shutdown(); }

void grpc_iomgr_platform_shutdown_background_closure() {
  iomgr_platform_vtable->shutdown_background_closure();
}

bool grpc_iomgr_platform_is_any_background_poller_thread() {
  return iomgr_platform_vtable->is_any_background_poller_thread();
}

bool grpc_iomgr_platform_add_closure_to_background_poller(
    grpc_closure* closure, grpc_error_handle error) {
  return iomgr_platform_vtable->add_closure_to_background_poller(closure,
                                                                 error);
}
