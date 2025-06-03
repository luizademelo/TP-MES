Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/lib/iomgr/timer_manager.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/util/crash.h"
#include "src/core/util/thd.h"

// Structure to hold completed timer threads for cleanup
struct completed_thread {
  grpc_core::Thread thd;  // The thread object
  completed_thread* next; // Pointer to next completed thread in list
};

// Mutex for thread synchronization
static gpr_mu g_mu;

// Flag indicating if timer manager is running in threaded mode
static bool g_threaded;

// Flag to control if threads should start automatically
static bool g_start_threaded = true;

// Condition variable for thread waiting
static gpr_cv g_cv_wait;

// Condition variable for shutdown signaling
static gpr_cv g_cv_shutdown;

// Count of active timer threads
static int g_thread_count;

// Count of threads waiting for work
static int g_waiter_count;

// List of completed threads waiting to be garbage collected
static completed_thread* g_completed_threads;

// Flag indicating if a thread was kicked (woken up explicitly)
static bool g_kicked;

// Flag indicating if there's a thread waiting with a timeout
static bool g_has_timed_waiter;

// Deadline for the current timed waiter
static grpc_core::Timestamp g_timed_waiter_deadline;

// Generation counter for timed waiters
static uint64_t g_timed_waiter_generation;

// Counter for wakeup events
static uint64_t g_wakeups;

// Forward declaration of timer thread function
static void timer_thread(void* completed_thread_ptr);

// Garbage collect completed threads
static void gc_completed_threads(void) {
  if (g_completed_threads != nullptr) {
    completed_thread* to_gc = g_completed_threads;
    g_completed_threads = nullptr;
    gpr_mu_unlock(&g_mu);
    while (to_gc != nullptr) {
      to_gc->thd.Join();  // Wait for thread to complete
      completed_thread* next = to_gc->next;
      gpr_free(to_gc);    // Free thread memory
      to_gc = next;
    }
    gpr_mu_lock(&g_mu);  // Reacquire lock
  }
}

// Start a new timer thread and release the lock
static void start_timer_thread_and_unlock(void) {
  CHECK(g_threaded);
  ++g_waiter_count;
  ++g_thread_count;
  gpr_mu_unlock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO) << "Spawn timer thread";
  completed_thread* ct =
      static_cast<completed_thread*>(gpr_malloc(sizeof(*ct)));
  ct->thd = grpc_core::Thread("grpc_global_timer", timer_thread, ct);
  ct->thd.Start();  // Start the new thread
}

// Process one timer tick
void grpc_timer_manager_tick() {
  grpc_core::ExecCtx exec_ctx;
  grpc_timer_check(nullptr);  // Check for expired timers
}

// Run pending timers and manage thread pool
static void run_some_timers() {
  gpr_mu_lock(&g_mu);

  --g_waiter_count;
  if (g_waiter_count == 0 && g_threaded) {
    // If no waiters left and in threaded mode, start a new thread
    start_timer_thread_and_unlock();
  } else {
    // Otherwise wake up an existing waiter
    if (!g_has_timed_waiter) {
      GRPC_TRACE_LOG(timer_check, INFO) << "kick untimed waiter";
      gpr_cv_signal(&g_cv_wait);
    }
    gpr_mu_unlock(&g_mu);
  }

  // Process any pending callbacks
  GRPC_TRACE_LOG(timer_check, INFO) << "flush exec_ctx";
  grpc_core::ExecCtx::Get()->Flush();
  gpr_mu_lock(&g_mu);

  // Clean up completed threads
  gc_completed_threads();

  ++g_waiter_count;
  gpr_mu_unlock(&g_mu);
}

// Wait until specified deadline or until kicked
static bool wait_until(grpc_core::Timestamp next) {
  gpr_mu_lock(&g_mu);

  if (!g_threaded) {
    gpr_mu_unlock(&g_mu);
    return false;
  }

  if (!g_kicked) {
    uint64_t my_timed_waiter_generation = g_timed_waiter_generation - 1;

    // Handle timed wait if needed
    if (next != grpc_core::Timestamp::InfFuture()) {
      if (!g_has_timed_waiter || (next < g_timed_waiter_deadline)) {
        my_timed_waiter_generation = ++g_timed_waiter_generation;
        g_has_timed_waiter = true;
        g_timed_waiter_deadline = next;

        if (GRPC_TRACE_FLAG_ENABLED(timer_check)) {
          grpc_core::Duration wait_time = next - grpc_core::Timestamp::Now();
          LOG(INFO) << "sleep for a " << wait_time.millis() << " milliseconds";
        }
      } else {
        next = grpc_core::Timestamp::InfFuture();
      }
    }

    if (GRPC_TRACE_FLAG_ENABLED(timer_check) &&
        next == grpc_core::Timestamp::InfFuture()) {
      LOG(INFO) << "sleep until kicked";
    }

    // Wait on condition variable
    gpr_cv_wait(&g_cv_wait, &g_mu, next.as_timespec(GPR_CLOCK_MONOTONIC));

    GRPC_TRACE_LOG(timer_check, INFO)
        << "wait ended: was_timed:"
        << (my_timed_waiter_generation == g_timed_waiter_generation)
        << " kicked:" << g_kicked;

    // Handle timed waiter cleanup if this was the timed waiter
    if (my_timed_waiter_generation == g_timed_waiter_generation) {
      ++g_wakeups;
      g_has_timed_waiter = false;
      g_timed_waiter_deadline = grpc_core::Timestamp::InfFuture();
    }
  }

  // Handle kick if received
  if (g_kicked) {
    grpc_timer_consume_kick();
    g_kicked = false;
  }

  gpr_mu_unlock(&g_mu);
  return true;
}

// Main loop for timer threads
static void timer_main_loop() {
  for (;;) {
    grpc_core::Timestamp next = grpc_core::Timestamp::InfFuture();
    grpc_core::ExecCtx::Get()->InvalidateNow();

    // Check for timer events
    switch (grpc_timer_check(&next)) {
      case GRPC_TIMERS_FIRED:
        run_some_timers();
        break;
      case GRPC_TIMERS_NOT_CHECKED:
        // Another thread is handling timers
        GRPC_TRACE_LOG(timer_check, INFO)
            << "timers not checked: expect another thread to";
        next = grpc_core::Timestamp::InfFuture();
        [[fallthrough]];
      case GRPC_TIMERS_CHECKED_AND_EMPTY:
        if (!wait_until(next)) {
          return;
        }
        break;
    }
  }
}

// Cleanup for a timer thread that's exiting
static void timer_thread_cleanup(completed_thread* ct) {
  gpr_mu_lock(&g_mu);

  --g_waiter_count;
  --g_thread_count;
  if (0 == g_thread_count) {
    gpr_cv_signal(&g_cv_shutdown);  // Signal shutdown if last thread
  }
  // Add to completed threads list
  ct->next = g_completed_threads;
  g_completed_threads = ct;
  gpr_mu_unlock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO) << "End timer thread";
}

// Entry point for timer threads
static void timer_thread(void* completed_thread_ptr) {
  grpc_core::ExecCtx exec_ctx(GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD);
  timer_main_loop();

  timer_thread_cleanup(static_cast<completed_thread*>(completed_thread_ptr));
}

// Start timer threads if not already running
static void start_threads(void) {
  gpr_mu_lock(&g_mu);
  if (!g_threaded) {
    g_threaded = true;
    start_timer_thread_and_unlock();
  } else {
    gpr_mu_unlock(&g_mu);
  }
}

// Initialize timer manager
void grpc_timer_manager_init(void) {
  gpr_mu_init(&g_mu);
  gpr_cv_init(&g_cv_wait);
  gpr_cv_init(&g_cv_shutdown);
  g_threaded = false;
  g_thread_count = 0;
  g_waiter_count = 0;
  g_completed_threads = nullptr;

  g_has_timed_waiter = false;
  g_timed_waiter_deadline = grpc_core::Timestamp::InfFuture();

  if (g_start_threaded) start_threads();
}

// Stop all timer threads
static void stop_threads(void) {
  gpr_mu_lock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO)
      << "stop timer threads: threaded=" << g_threaded;
  if (g_threaded) {
    g_threaded = false;
    gpr_cv_broadcast(&g_cv_wait);  // Wake all threads
    GRPC_TRACE_LOG(timer_check, INFO)
        << "num timer threads: " << g_thread_count;
    while (g_thread_count > 0) {
      gpr_cv_wait(&g_cv_shutdown, &g_mu, gpr_inf_future(GPR_CLOCK_MONOTONIC));
      GRPC_TRACE_LOG(timer_check, INFO)
          << "num timer threads: " << g_thread_count;
      gc_completed_threads();
    }
  }
  g_wakeups = 0;
  gpr_mu_unlock(&g_mu);
}

// Shutdown timer manager
void grpc_timer_manager_shutdown(void) {
  stop_threads();

  gpr_mu_destroy(&g_mu);
  gpr_cv_destroy(&g_cv_wait);
  gpr_cv_destroy(&g_cv_shutdown);
}

// Enable/disable threading mode
void grpc_timer_manager_set_threading(bool enabled) {
  if (enabled) {
    start_threads();
  } else {
    stop_threads();
  }
}

// Set whether threads should start automatically on init
void grpc_timer_manager_set_start_threaded(bool enabled) {
  g_start_threaded = enabled;
}

// Wake up the timer manager
void grpc_kick_poller(void) {
  gpr_mu_lock(&g_mu);
  g_kicked = true;
  g_has_timed_waiter = false;
  g_timed_waiter_deadline = grpc_core::Timestamp::InfFuture();
  ++g_timed_waiter_generation;
  gpr_cv_signal(&g_cv_wait);
  gpr_mu_unlock(&g_mu);
}

// Get wakeup count (for testing)
uint64_t grpc_timer_manager_get_wakeups_testonly(void) { return g_wakeups; }
```