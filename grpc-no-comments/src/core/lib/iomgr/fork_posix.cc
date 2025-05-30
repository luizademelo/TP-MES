
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_FORK

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
#include <pthread.h>
#endif

#include <grpc/fork.h>
#include <grpc/grpc.h>
#include <string.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/lib/surface/init_internally.h"
#include "src/core/util/fork.h"

// NOTE: FORKING IS NOT GENERALLY SUPPORTED, THIS IS ONLY INTENDED TO WORK

namespace {
bool skipped_handler = true;
bool registered_handlers = false;
}

void grpc_prefork() {
  skipped_handler = true;

  if (!grpc_core::IsInitializedInternally()) {
    return;
  }
  grpc_core::ExecCtx exec_ctx;
  if (!grpc_core::Fork::Enabled()) {
    LOG(ERROR) << "Fork support not enabled; try running with the "
                  "environment variable GRPC_ENABLE_FORK_SUPPORT=1";
    return;
  }
  const char* poll_strategy_name = grpc_get_poll_strategy_name();
  if (poll_strategy_name == nullptr ||
      (strcmp(poll_strategy_name, "epoll1") != 0 &&
       strcmp(poll_strategy_name, "poll") != 0)) {
    LOG(INFO) << "Fork support is only compatible with the epoll1 and poll "
                 "polling strategies";
    return;
  }
  if (!grpc_core::Fork::BlockExecCtx()) {
    LOG(INFO) << "Other threads are currently calling into gRPC, skipping "
                 "fork() handlers";
    return;
  }
  grpc_timer_manager_set_threading(false);
  grpc_core::ExecCtx::Get()->Flush();
  grpc_core::Fork::AwaitThreads();
  skipped_handler = false;
}

void grpc_postfork_parent() {
  if (!skipped_handler) {
    grpc_core::Fork::AllowExecCtx();
    grpc_core::ExecCtx exec_ctx;
    grpc_timer_manager_set_threading(true);
  }
}

void grpc_postfork_child() {
  if (!skipped_handler) {
    grpc_core::Fork::AllowExecCtx();
    grpc_core::ExecCtx exec_ctx;
    for (auto* reset_polling_engine :
         grpc_core::Fork::GetResetChildPollingEngineFunc()) {
      if (reset_polling_engine != nullptr) {
        reset_polling_engine();
      }
    }
    grpc_timer_manager_set_threading(true);
  }
}

void grpc_fork_handlers_auto_register() {
  if (grpc_core::Fork::Enabled() & !registered_handlers) {
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
    pthread_atfork(grpc_prefork, grpc_postfork_parent, grpc_postfork_child);
    registered_handlers = true;
#endif
  }
}

#endif
