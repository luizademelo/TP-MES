
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

#include "src/core/lib/iomgr/pollset_set_windows.h"

static grpc_pollset_set* pollset_set_create(void) {
  return (grpc_pollset_set*)((intptr_t)0xdeafbeef);
}

static void pollset_set_destroy(grpc_pollset_set* ) {}

static void pollset_set_add_pollset(grpc_pollset_set* ,
                                    grpc_pollset* ) {}

static void pollset_set_del_pollset(grpc_pollset_set* ,
                                    grpc_pollset* ) {}

static void pollset_set_add_pollset_set(grpc_pollset_set* ,
                                        grpc_pollset_set* ) {}

static void pollset_set_del_pollset_set(grpc_pollset_set* ,
                                        grpc_pollset_set* ) {}

grpc_pollset_set_vtable grpc_windows_pollset_set_vtable = {
    pollset_set_create,          pollset_set_destroy,
    pollset_set_add_pollset,     pollset_set_del_pollset,
    pollset_set_add_pollset_set, pollset_set_del_pollset_set};

#endif
