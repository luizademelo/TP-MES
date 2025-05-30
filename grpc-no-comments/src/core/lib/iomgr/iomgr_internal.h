
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_IOMGR_INTERNAL_H
#define GRPC_SRC_CORE_LIB_IOMGR_IOMGR_INTERNAL_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"

typedef struct grpc_iomgr_object {
  char* name;
  struct grpc_iomgr_object* next;
  struct grpc_iomgr_object* prev;
} grpc_iomgr_object;

typedef struct grpc_iomgr_platform_vtable {
  void (*init)(void);
  void (*flush)(void);
  void (*shutdown)(void);
  void (*shutdown_background_closure)(void);
  bool (*is_any_background_poller_thread)(void);
  bool (*add_closure_to_background_poller)(grpc_closure* closure,
                                           grpc_error_handle error);
} grpc_iomgr_platform_vtable;

void grpc_iomgr_register_object(grpc_iomgr_object* obj, const char* name);
void grpc_iomgr_unregister_object(grpc_iomgr_object* obj);

bool grpc_have_determined_iomgr_platform();

void grpc_set_iomgr_platform_vtable(grpc_iomgr_platform_vtable* vtable);

void grpc_set_default_iomgr_platform();

void grpc_iomgr_platform_init(void);

void grpc_iomgr_platform_flush(void);

void grpc_iomgr_platform_shutdown(void);

void grpc_iomgr_platform_shutdown_background_closure(void);

bool grpc_iomgr_platform_is_any_background_poller_thread(void);

bool grpc_iomgr_platform_add_closure_to_background_poller(
    grpc_closure* closure, grpc_error_handle error);

bool grpc_iomgr_abort_on_leaks(void);

#endif
