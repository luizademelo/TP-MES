Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

// Only compile this code if POSIX fork support is enabled
#ifdef GRPC_POSIX_FORK

// Optional pthread_atfork support if enabled
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
// IN VERY SPECIFIC USE CASES

namespace {
// Flag to track if fork handlers were skipped
bool skipped_handler = true;
// Flag to track if fork handlers have been registered
bool registered_handlers = false;
}

// Prepares gRPC for a fork() operation
void grpc_prefork() {
  skipped_handler = true;

  // Skip if gRPC is not initialized
  if (!grpc_core::IsInitializedInternally()) {
    return;
  }
  
  // Create execution context for the current thread
  grpc_core::ExecCtx exec_ctx;
  
  // Check if fork support is enabled
  if (!grpc_core::Fork::Enabled()) {
    LOG(ERROR) << "Fork support not enabled; try running with the "
                  "environment variable GRPC_ENABLE_FORK_SUPPORT=1";
    return;
  }
  
  // Verify we're using a compatible polling strategy
  const char* poll_strategy_name = grpc_get_poll_strategy_name();
  if (poll_strategy_name == nullptr ||
      (strcmp(poll_strategy_name, "epoll1") != 0 &&
       strcmp(poll_strategy_name, "poll") != 0)) {
    LOG(INFO) << "Fork support is only compatible with the epoll1 and poll "
                 "polling strategies";
    return;
  }
  
  // Block new execution contexts from being created
  if (!grpc_core::Fork::BlockExecCtx()) {
    LOG(INFO) << "Other threads are currently calling into gRPC, skipping "
                 "fork() handlers";
    return;
  }
  
  // Stop timer manager thread and flush any pending operations
  grpc_timer_manager_set_threading(false);
  grpc_core::ExecCtx::Get()->Flush();
  
  // Wait for all threads to complete
  grpc_core::Fork::AwaitThreads();
  
  // Mark that handlers were executed
  skipped_handler = false;
}

// Called in parent process after fork() completes
void grpc_postfork_parent() {
  if (!skipped_handler) {
    // Re-enable execution contexts
    grpc_core::Fork::AllowExecCtx();
    grpc_core::ExecCtx exec_ctx;
    // Restart timer manager thread
    grpc_timer_manager_set_threading(true);
  }
}

// Called in child process after fork() completes
void grpc_postfork_child() {
  if (!skipped_handler) {
    // Re-enable execution contexts
    grpc_core::Fork::AllowExecCtx();
    grpc_core::ExecCtx exec_ctx;
    // Reset all polling engines in child process
    for (auto* reset_polling_engine :
         grpc_core::Fork::GetResetChildPollingEngineFunc()) {
      if (reset_polling_engine != nullptr) {
        reset_polling_engine();
      }
    }
    // Restart timer manager thread
    grpc_timer_manager_set_threading(true);
  }
}

// Automatically registers fork handlers if fork support is enabled
void grpc_fork_handlers_auto_register() {
  if (grpc_core::Fork::Enabled() & !registered_handlers) {
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
    // Register pre-fork, post-fork parent, and post-fork child handlers
    pthread_atfork(grpc_prefork, grpc_postfork_parent, grpc_postfork_child);
    registered_handlers = true;
#endif
  }
}

#endif  // GRPC_POSIX_FORK
```

The comments explain:
1. The overall purpose of the file (fork support for gRPC)
2. The main functions and their roles in the fork process
3. The various checks and conditions that must be met
4. The state management between parent and child processes
5. The automatic registration mechanism for fork handlers
6. Important safety notes about limited fork support

The comments are placed to help future maintainers understand:
- When and why certain operations are performed
- The flow of control during fork operations
- The important state transitions
- The conditions under which operations are skipped