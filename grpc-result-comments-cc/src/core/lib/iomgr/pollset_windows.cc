Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/util/crash.h"
#include "src/core/util/thd.h"

// Special value used to indicate a broadcast kick to all workers
#define GRPC_POLLSET_KICK_BROADCAST ((grpc_pollset_worker*)1)

// Global synchronization mutex for pollset operations
gpr_mu grpc_polling_mu;
// Currently active poller worker
static grpc_pollset_worker* g_active_poller;
// Root worker for global worker list
static grpc_pollset_worker g_global_root_worker;

// Initializes global pollset structures
static void pollset_global_init(void) {
  gpr_mu_init(&grpc_polling_mu);
  g_active_poller = NULL;
  // Initialize circular linked list for global workers
  g_global_root_worker.links[GRPC_POLLSET_WORKER_LINK_GLOBAL].next =
      g_global_root_worker.links[GRPC_POLLSET_WORKER_LINK_GLOBAL].prev =
          &g_global_root_worker;
}

// Cleans up global pollset structures
static void pollset_global_shutdown(void) {
  gpr_mu_destroy(&grpc_polling_mu);
}

// Removes a worker from a specified linked list
static void remove_worker(grpc_pollset_worker* worker,
                         grpc_pollset_worker_link_type type) {
  // Update next and prev pointers to bypass the worker
  worker->links[type].prev->links[type].next = worker->links[type].next;
  worker->links[type].next->links[type].prev = worker->links[type].prev;
  // Set worker's links to point to itself
  worker->links[type].next = worker->links[type].prev = worker;
}

// Checks if there are any workers in the specified list
static int has_workers(grpc_pollset_worker* root,
                      grpc_pollset_worker_link_type type) {
  return root->links[type].next != root;
}

// Removes and returns the first worker from the specified list
static grpc_pollset_worker* pop_front_worker(
    grpc_pollset_worker* root, grpc_pollset_worker_link_type type) {
  if (has_workers(root, type)) {
    grpc_pollset_worker* w = root->links[type].next;
    remove_worker(w, type);
    return w;
  } else {
    return NULL;
  }
}

// Adds a worker to the front of the specified list
static void push_front_worker(grpc_pollset_worker* root,
                             grpc_pollset_worker_link_type type,
                             grpc_pollset_worker* worker) {
  worker->links[type].prev = root;
  worker->links[type].next = worker->links[type].prev->links[type].next;
  worker->links[type].prev->links[type].next =
      worker->links[type].next->links[type].prev = worker;
}

// Returns the size of a pollset structure
static size_t pollset_size(void) {
  return sizeof(grpc_pollset);
}

// Initializes a pollset structure
static void pollset_init(grpc_pollset* pollset, gpr_mu** mu) {
  *mu = &grpc_polling_mu;
  // Initialize circular linked list for pollset workers
  pollset->root_worker.links[GRPC_POLLSET_WORKER_LINK_POLLSET].next =
      pollset->root_worker.links[GRPC_POLLSET_WORKER_LINK_POLLSET].prev =
          &pollset->root_worker;
}

// Shuts down a pollset and runs the shutdown closure
static void pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  pollset->shutting_down = 1;
  // Kick all workers to wake them up during shutdown
  std::ignore = grpc_pollset_kick(pollset, GRPC_POLLSET_KICK_BROADCAST);
  if (!pollset->is_iocp_worker) {
    // If not an IOCP worker, run the closure immediately
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
  } else {
    // Otherwise store the closure to run later
    pollset->on_shutdown = closure;
  }
}

// Destroys a pollset (no-op in this implementation)
static void pollset_destroy(grpc_pollset* ) {}

// Main pollset work function - waits for events or deadline
static grpc_error_handle pollset_work(grpc_pollset* pollset,
                                     grpc_pollset_worker** worker_hdl,
                                     grpc_core::Timestamp deadline) {
  grpc_pollset_worker worker;
  if (worker_hdl) *worker_hdl = &worker;

  int added_worker = 0;
  // Initialize worker links
  worker.links[GRPC_POLLSET_WORKER_LINK_POLLSET].next =
      worker.links[GRPC_POLLSET_WORKER_LINK_POLLSET].prev =
          worker.links[GRPC_POLLSET_WORKER_LINK_GLOBAL].next =
              worker.links[GRPC_POLLSET_WORKER_LINK_GLOBAL].prev = NULL;
  worker.kicked = 0;
  worker.pollset = pollset;
  gpr_cv_init(&worker.cv);

  if (!pollset->kicked_without_pollers && !pollset->shutting_down) {
    if (g_active_poller == NULL) {
      // Become the active poller
      grpc_pollset_worker* next_worker;

      pollset->is_iocp_worker = 1;
      g_active_poller = &worker;
      gpr_mu_unlock(&grpc_polling_mu);
      // Do IOCP work until deadline
      grpc_iocp_work(deadline);
      grpc_core::ExecCtx::Get()->Flush();
      gpr_mu_lock(&grpc_polling_mu);
      pollset->is_iocp_worker = 0;
      g_active_poller = NULL;

      // Find and wake next worker
      next_worker = pop_front_worker(&pollset->root_worker,
                                    GRPC_POLLSET_WORKER_LINK_POLLSET);
      if (next_worker == NULL) {
        next_worker = pop_front_worker(&g_global_root_worker,
                                      GRPC_POLLSET_WORKER_LINK_GLOBAL);
      }
      if (next_worker != NULL) {
        next_worker->kicked = 1;
        gpr_cv_signal(&next_worker->cv);
      }

      // Handle shutdown if needed
      if (pollset->shutting_down && pollset->on_shutdown != NULL) {
        grpc_core::ExecCtx::Run(DEBUG_LOCATION, pollset->on_shutdown,
                               absl::OkStatus());
        pollset->on_shutdown = NULL;
      }
      goto done;
    }
    // Add worker to global and pollset lists
    push_front_worker(&g_global_root_worker, GRPC_POLLSET_WORKER_LINK_GLOBAL,
                     &worker);
    push_front_worker(&pollset->root_worker, GRPC_POLLSET_WORKER_LINK_POLLSET,
                     &worker);
    added_worker = 1;
    // Wait until kicked or deadline
    while (!worker.kicked) {
      if (gpr_cv_wait(&worker.cv, &grpc_polling_mu,
                     deadline.as_timespec(GPR_CLOCK_REALTIME))) {
        grpc_core::ExecCtx::Get()->InvalidateNow();
        break;
      }
      grpc_core::ExecCtx::Get()->InvalidateNow();
    }
  } else {
    pollset->kicked_without_pollers = 0;
  }
done:
  // Flush any pending closures
  if (!grpc_closure_list_empty(*grpc_core::ExecCtx::Get()->closure_list())) {
    gpr_mu_unlock(&grpc_polling_mu);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_mu_lock(&grpc_polling_mu);
  }
  // Clean up worker if it was added to lists
  if (added_worker) {
    remove_worker(&worker, GRPC_POLLSET_WORKER_LINK_GLOBAL);
    remove_worker(&worker, GRPC_POLLSET_WORKER_LINK_POLLSET);
  }
  gpr_cv_destroy(&worker.cv);
  if (worker_hdl) *worker_hdl = NULL;
  return absl::OkStatus();
}

// Kicks a specific worker or all workers in a pollset
static grpc_error_handle pollset_kick(grpc_pollset* p,
                                     grpc_pollset_worker* specific_worker) {
  bool should_kick_global = false;
  if (specific_worker != NULL) {
    if (specific_worker == GRPC_POLLSET_KICK_BROADCAST) {
      // Broadcast kick to all workers in the pollset
      should_kick_global = true;
      for (specific_worker =
               p->root_worker.links[GRPC_POLLSET_WORKER_LINK_POLLSET].next;
           specific_worker != &p->root_worker;
           specific_worker =
               specific_worker->links[GRPC_POLLSET_WORKER_LINK_POLLSET].next) {
        specific_worker->kicked = 1;
        should_kick_global = false;
        gpr_cv_signal(&specific_worker->cv);
      }
      p->kicked_without_pollers = 1;
      if (p->is_iocp_worker) {
        grpc_iocp_kick();
        should_kick_global = false;
      }
    } else {
      // Kick specific worker
      if (p->is_iocp_worker && g_active_poller == specific_worker) {
        grpc_iocp_kick();
      } else {
        specific_worker->kicked = 1;
        gpr_cv_signal(&specific_worker->cv);
      }
    }
  } else {
    // Kick next available worker
    specific_worker =
        pop_front_worker(&p->root_worker, GRPC_POLLSET_WORKER_LINK_POLLSET);
    if (specific_worker != NULL) {
      std::ignore = grpc_pollset_kick(p, specific_worker);
    } else if (p->is_iocp_worker) {
      grpc_iocp_kick();
    } else {
      p->kicked_without_pollers = 1;
      should_kick_global = true;
    }
  }
  // Kick global worker if needed
  if (should_kick_global && g_active_poller == NULL) {
    grpc_pollset_worker* next_global_worker = pop_front_worker(
        &g_global_root_worker, GRPC_POLLSET_WORKER_LINK_GLOBAL);
    if (next_global_worker != NULL) {
      next_global_worker->kicked = 1;
      gpr_cv_signal(&next_global_worker->cv);
    }
  }
  return absl::OkStatus();
}

// Pollset vtable for Windows implementation
grpc_pollset_vtable grpc_windows_pollset_vtable = {
    pollset_global_init, pollset_global_shutdown,
    pollset_init,        pollset_shutdown,
    pollset_destroy,     pollset_work,
    pollset_kick,        pollset_size};

#endif
```