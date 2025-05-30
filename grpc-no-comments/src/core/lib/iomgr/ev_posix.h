
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EV_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_EV_POSIX_H

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_EV

#include <grpc/support/port_platform.h>
#include <poll.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/wakeup_fd_posix.h"

typedef struct grpc_fd grpc_fd;

typedef struct grpc_event_engine_vtable {
  size_t pollset_size;
  bool can_track_err;
  bool run_in_background;

  grpc_fd* (*fd_create)(int fd, const char* name, bool track_err);
  int (*fd_wrapped_fd)(grpc_fd* fd);
  void (*fd_orphan)(grpc_fd* fd, grpc_closure* on_done, int* release_fd,
                    const char* reason);
  void (*fd_shutdown)(grpc_fd* fd, grpc_error_handle why);
  void (*fd_notify_on_read)(grpc_fd* fd, grpc_closure* closure);
  void (*fd_notify_on_write)(grpc_fd* fd, grpc_closure* closure);
  void (*fd_notify_on_error)(grpc_fd* fd, grpc_closure* closure);
  void (*fd_set_readable)(grpc_fd* fd);
  void (*fd_set_writable)(grpc_fd* fd);
  void (*fd_set_error)(grpc_fd* fd);
  bool (*fd_is_shutdown)(grpc_fd* fd);

  void (*pollset_init)(grpc_pollset* pollset, gpr_mu** mu);
  void (*pollset_shutdown)(grpc_pollset* pollset, grpc_closure* closure);
  void (*pollset_destroy)(grpc_pollset* pollset);
  grpc_error_handle (*pollset_work)(grpc_pollset* pollset,
                                    grpc_pollset_worker** worker,
                                    grpc_core::Timestamp deadline);
  grpc_error_handle (*pollset_kick)(grpc_pollset* pollset,
                                    grpc_pollset_worker* specific_worker);
  void (*pollset_add_fd)(grpc_pollset* pollset, struct grpc_fd* fd);

  grpc_pollset_set* (*pollset_set_create)(void);
  void (*pollset_set_destroy)(grpc_pollset_set* pollset_set);
  void (*pollset_set_add_pollset)(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset);
  void (*pollset_set_del_pollset)(grpc_pollset_set* pollset_set,
                                  grpc_pollset* pollset);
  void (*pollset_set_add_pollset_set)(grpc_pollset_set* bag,
                                      grpc_pollset_set* item);
  void (*pollset_set_del_pollset_set)(grpc_pollset_set* bag,
                                      grpc_pollset_set* item);
  void (*pollset_set_add_fd)(grpc_pollset_set* pollset_set, grpc_fd* fd);
  void (*pollset_set_del_fd)(grpc_pollset_set* pollset_set, grpc_fd* fd);

  bool (*is_any_background_poller_thread)(void);
  const char* name;
  bool (*check_engine_available)(bool explicit_request);
  void (*init_engine)();
  void (*shutdown_background_closure)(void);
  void (*shutdown_engine)(void);
  bool (*add_closure_to_background_poller)(grpc_closure* closure,
                                           grpc_error_handle error);

  void (*fd_set_pre_allocated)(grpc_fd* fd);
} grpc_event_engine_vtable;

void grpc_register_event_engine_factory(const grpc_event_engine_vtable* vtable,
                                        bool add_at_head);

void grpc_event_engine_init(void);
void grpc_event_engine_shutdown(void);

bool grpc_event_engine_can_track_errors();

bool grpc_event_engine_run_in_background();

grpc_fd* grpc_fd_create(int fd, const char* name, bool track_err);

int grpc_fd_wrapped_fd(grpc_fd* fd);

void grpc_fd_orphan(grpc_fd* fd, grpc_closure* on_done, int* release_fd,
                    const char* reason);

bool grpc_fd_is_shutdown(grpc_fd* fd);

void grpc_fd_shutdown(grpc_fd* fd, grpc_error_handle why);

void grpc_fd_notify_on_read(grpc_fd* fd, grpc_closure* closure);

void grpc_fd_notify_on_write(grpc_fd* fd, grpc_closure* closure);

void grpc_fd_notify_on_error(grpc_fd* fd, grpc_closure* closure);

void grpc_fd_set_readable(grpc_fd* fd);

void grpc_fd_set_writable(grpc_fd* fd);

void grpc_fd_set_error(grpc_fd* fd);

void grpc_fd_set_pre_allocated(grpc_fd* fd);

void grpc_pollset_add_fd(grpc_pollset* pollset, struct grpc_fd* fd);

void grpc_pollset_set_add_fd(grpc_pollset_set* pollset_set, grpc_fd* fd);
void grpc_pollset_set_del_fd(grpc_pollset_set* pollset_set, grpc_fd* fd);

bool grpc_is_any_background_poller_thread();

bool grpc_add_closure_to_background_poller(grpc_closure* closure,
                                           grpc_error_handle error);

void grpc_shutdown_background_closure();

typedef int (*grpc_poll_function_type)(struct pollfd*, nfds_t, int);
extern grpc_poll_function_type grpc_poll_function;

#endif

const char* grpc_get_poll_strategy_name();

#endif
