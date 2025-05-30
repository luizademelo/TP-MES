
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_POLLSET_WINDOWS_H
#define GRPC_SRC_CORE_LIB_IOMGR_POLLSET_WINDOWS_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET
#include "src/core/lib/iomgr/socket_windows.h"

typedef enum {
  GRPC_POLLSET_WORKER_LINK_POLLSET = 0,
  GRPC_POLLSET_WORKER_LINK_GLOBAL,
  GRPC_POLLSET_WORKER_LINK_TYPES
} grpc_pollset_worker_link_type;

typedef struct grpc_pollset_worker_link {
  struct grpc_pollset_worker* next;
  struct grpc_pollset_worker* prev;
} grpc_pollset_worker_link;

struct grpc_pollset;
typedef struct grpc_pollset grpc_pollset;

typedef struct grpc_pollset_worker {
  gpr_cv cv;
  int kicked;
  struct grpc_pollset* pollset;
  grpc_pollset_worker_link links[GRPC_POLLSET_WORKER_LINK_TYPES];
} grpc_pollset_worker;

struct grpc_pollset {
  int shutting_down;
  int kicked_without_pollers;
  int is_iocp_worker;
  grpc_pollset_worker root_worker;
  grpc_closure* on_shutdown;
};

void grpc_pollset_global_init(void);
void grpc_pollset_global_shutdown(void);

#endif

#endif
