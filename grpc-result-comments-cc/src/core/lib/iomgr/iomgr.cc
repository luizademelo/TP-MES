Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for I/O manager functionality
#include "src/core/lib/iomgr/iomgr.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/sync.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/log.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/iomgr/buffer_list.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/internal_errqueue.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "src/core/util/thd.h"
#include "src/core/util/useful.h"

// Static global variables for I/O manager state management
static gpr_mu g_mu;                     // Mutex for thread synchronization
static gpr_cv g_rcv;                    // Condition variable for signaling
static int g_shutdown;                  // Shutdown flag
static grpc_iomgr_object g_root_object; // Root object for tracking I/O manager objects

// Initializes the I/O manager system
void grpc_iomgr_init() {
  grpc_core::ExecCtx exec_ctx;
  // Set default platform if not already determined
  if (!grpc_have_determined_iomgr_platform()) {
    grpc_set_default_iomgr_platform();
  }
  g_shutdown = 0; // Initialize shutdown flag
  gpr_mu_init(&g_mu); // Initialize mutex
  gpr_cv_init(&g_rcv); // Initialize condition variable
  // Initialize root object as circular linked list
  g_root_object.next = g_root_object.prev = &g_root_object;
  g_root_object.name = const_cast<char*>("root");
  grpc_iomgr_platform_init(); // Platform-specific initialization
  grpc_timer_list_init(); // Initialize timer list
}

// Starts the I/O manager components
void grpc_iomgr_start() { grpc_timer_manager_init(); }

// Helper function to count active I/O manager objects
static size_t count_objects(void) {
  grpc_iomgr_object* obj;
  size_t n = 0;
  // Iterate through the circular linked list of objects
  for (obj = g_root_object.next; obj != &g_root_object; obj = obj->next) {
    n++;
  }
  return n;
}

// Returns count of I/O manager objects (for testing purposes)
size_t grpc_iomgr_count_objects_for_testing(void) {
  gpr_mu_lock(&g_mu);
  size_t ret = count_objects();
  gpr_mu_unlock(&g_mu);
  return ret;
}

// Helper function to log information about I/O manager objects
static void dump_objects(const char* kind) {
  grpc_iomgr_object* obj;
  for (obj = g_root_object.next; obj != &g_root_object; obj = obj->next) {
    VLOG(2) << kind << " OBJECT: " << obj->name << " " << obj;
  }
}

// Shuts down the I/O manager system
void grpc_iomgr_shutdown() {
  // Set shutdown deadline to 10 seconds from now
  gpr_timespec shutdown_deadline = gpr_time_add(
      gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN));
  gpr_timespec last_warning_time = gpr_now(GPR_CLOCK_REALTIME);

  {
    // Shutdown timer manager and flush platform operations
    grpc_timer_manager_shutdown();
    grpc_iomgr_platform_flush();

    gpr_mu_lock(&g_mu);
    g_shutdown = 1; // Set shutdown flag
    
    // Wait for all objects to be destroyed
    while (g_root_object.next != &g_root_object) {
      // Log warning every second if objects remain
      if (gpr_time_cmp(
              gpr_time_sub(gpr_now(GPR_CLOCK_REALTIME), last_warning_time),
              gpr_time_from_seconds(1, GPR_TIMESPAN)) >= 0) {
        if (g_root_object.next != &g_root_object) {
          VLOG(2) << "Waiting for " << count_objects()
                  << " iomgr objects to be destroyed";
        }
        last_warning_time = gpr_now(GPR_CLOCK_REALTIME);
      }
      
      // Set shutdown state and check timers
      grpc_core::ExecCtx::Get()->SetNowIomgrShutdown();
      if (grpc_timer_check(nullptr) == GRPC_TIMERS_FIRED) {
        gpr_mu_unlock(&g_mu);
        grpc_core::ExecCtx::Get()->Flush();
        grpc_iomgr_platform_flush();
        gpr_mu_lock(&g_mu);
        continue;
      }
      
      // Handle remaining objects
      if (g_root_object.next != &g_root_object) {
        if (grpc_iomgr_abort_on_leaks()) {
          // Abort if configured to do so on leaks
          VLOG(2) << "Failed to free " << count_objects()
                  << " iomgr objects before shutdown deadline: "
                  << "memory leaks are likely";
          dump_objects("LEAKED");
          abort();
        }
        // Wait with short timeout
        gpr_timespec short_deadline =
            gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                         gpr_time_from_millis(100, GPR_TIMESPAN));
        if (gpr_cv_wait(&g_rcv, &g_mu, short_deadline)) {
          // Check if shutdown deadline exceeded
          if (gpr_time_cmp(gpr_now(GPR_CLOCK_REALTIME), shutdown_deadline) >
              0) {
            if (g_root_object.next != &g_root_object) {
              VLOG(2) << "Failed to free " << count_objects()
                      << " iomgr objects before shutdown deadline: "
                      << "memory leaks are likely";
              dump_objects("LEAKED");
            }
            break;
          }
        }
      }
    }
    gpr_mu_unlock(&g_mu);
    
    // Final cleanup
    grpc_timer_list_shutdown();
    grpc_core::ExecCtx::Get()->Flush();
  }

  // Lock/unlock sequence to ensure all operations complete
  gpr_mu_lock(&g_mu);
  gpr_mu_unlock(&g_mu);

  // Platform-specific shutdown and cleanup
  grpc_iomgr_platform_shutdown();
  gpr_mu_destroy(&g_mu);
  gpr_cv_destroy(&g_rcv);
}

// Shuts down background closures
void grpc_iomgr_shutdown_background_closure() {
  grpc_iomgr_platform_shutdown_background_closure();
}

// Checks if current thread is a background poller thread
bool grpc_iomgr_is_any_background_poller_thread() {
  return grpc_iomgr_platform_is_any_background_poller_thread();
}

// Adds closure to background poller
bool grpc_iomgr_add_closure_to_background_poller(grpc_closure* closure,
                                                 grpc_error_handle error) {
  return grpc_iomgr_platform_add_closure_to_background_poller(closure, error);
}

// Registers an I/O manager object for tracking
void grpc_iomgr_register_object(grpc_iomgr_object* obj, const char* name) {
  obj->name = gpr_strdup(name);
  gpr_mu_lock(&g_mu);
  // Add to circular linked list
  obj->next = &g_root_object;
  obj->prev = g_root_object.prev;
  obj->next->prev = obj->prev->next = obj;
  gpr_mu_unlock(&g_mu);
}

// Unregisters an I/O manager object
void grpc_iomgr_unregister_object(grpc_iomgr_object* obj) {
  gpr_mu_lock(&g_mu);
  // Remove from circular linked list
  obj->next->prev = obj->prev;
  obj->prev->next = obj->next;
  gpr_cv_signal(&g_rcv); // Signal waiting threads
  gpr_mu_unlock(&g_mu);
  gpr_free(obj->name); // Free allocated name
}

// Returns whether to abort on memory leaks
bool grpc_iomgr_abort_on_leaks(void) {
  return grpc_core::ConfigVars::Get().AbortOnLeaks();
}
```