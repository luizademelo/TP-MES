
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_WAKEUP_FD_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_WAKEUP_FD_POSIX_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/error.h"

void grpc_wakeup_fd_global_init(void);
void grpc_wakeup_fd_global_destroy(void);

void grpc_wakeup_fd_global_init_force_fallback(void);

int grpc_has_wakeup_fd(void);

typedef struct grpc_wakeup_fd grpc_wakeup_fd;

typedef struct grpc_wakeup_fd_vtable {
  grpc_error_handle (*init)(grpc_wakeup_fd* fd_info);
  grpc_error_handle (*consume)(grpc_wakeup_fd* fd_info);
  grpc_error_handle (*wakeup)(grpc_wakeup_fd* fd_info);
  void (*destroy)(grpc_wakeup_fd* fd_info);

  int (*check_availability)(void);
} grpc_wakeup_fd_vtable;

struct grpc_wakeup_fd {
  int read_fd;
  int write_fd;
};

extern int grpc_allow_specialized_wakeup_fd;
extern int grpc_allow_pipe_wakeup_fd;

#define GRPC_WAKEUP_FD_GET_READ_FD(fd_info) ((fd_info)->read_fd)

grpc_error_handle grpc_wakeup_fd_init(grpc_wakeup_fd* fd_info);
grpc_error_handle grpc_wakeup_fd_consume_wakeup(grpc_wakeup_fd* fd_info);
grpc_error_handle grpc_wakeup_fd_wakeup(grpc_wakeup_fd* fd_info);
void grpc_wakeup_fd_destroy(grpc_wakeup_fd* fd_info);

extern const grpc_wakeup_fd_vtable grpc_specialized_wakeup_fd_vtable;

#endif
