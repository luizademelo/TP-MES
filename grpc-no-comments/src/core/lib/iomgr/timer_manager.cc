
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

struct completed_thread {
  grpc_core::Thread thd;
  completed_thread* next;
};

static gpr_mu g_mu;

static bool g_threaded;

static bool g_start_threaded = true;

static gpr_cv g_cv_wait;

static gpr_cv g_cv_shutdown;

static int g_thread_count;

static int g_waiter_count;

static completed_thread* g_completed_threads;

static bool g_kicked;

static bool g_has_timed_waiter;

static grpc_core::Timestamp g_timed_waiter_deadline;

static uint64_t g_timed_waiter_generation;

static uint64_t g_wakeups;

static void timer_thread(void* completed_thread_ptr);

static void gc_completed_threads(void) {
  if (g_completed_threads != nullptr) {
    completed_thread* to_gc = g_completed_threads;
    g_completed_threads = nullptr;
    gpr_mu_unlock(&g_mu);
    while (to_gc != nullptr) {
      to_gc->thd.Join();
      completed_thread* next = to_gc->next;
      gpr_free(to_gc);
      to_gc = next;
    }
    gpr_mu_lock(&g_mu);
  }
}

static void start_timer_thread_and_unlock(void) {
  CHECK(g_threaded);
  ++g_waiter_count;
  ++g_thread_count;
  gpr_mu_unlock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO) << "Spawn timer thread";
  completed_thread* ct =
      static_cast<completed_thread*>(gpr_malloc(sizeof(*ct)));
  ct->thd = grpc_core::Thread("grpc_global_timer", timer_thread, ct);
  ct->thd.Start();
}

void grpc_timer_manager_tick() {
  grpc_core::ExecCtx exec_ctx;
  grpc_timer_check(nullptr);
}

static void run_some_timers() {

  gpr_mu_lock(&g_mu);

  --g_waiter_count;
  if (g_waiter_count == 0 && g_threaded) {

    start_timer_thread_and_unlock();
  } else {

    if (!g_has_timed_waiter) {
      GRPC_TRACE_LOG(timer_check, INFO) << "kick untimed waiter";
      gpr_cv_signal(&g_cv_wait);
    }
    gpr_mu_unlock(&g_mu);
  }

  GRPC_TRACE_LOG(timer_check, INFO) << "flush exec_ctx";
  grpc_core::ExecCtx::Get()->Flush();
  gpr_mu_lock(&g_mu);

  gc_completed_threads();

  ++g_waiter_count;
  gpr_mu_unlock(&g_mu);
}

static bool wait_until(grpc_core::Timestamp next) {
  gpr_mu_lock(&g_mu);

  if (!g_threaded) {
    gpr_mu_unlock(&g_mu);
    return false;
  }

  if (!g_kicked) {

    uint64_t my_timed_waiter_generation = g_timed_waiter_generation - 1;

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

    gpr_cv_wait(&g_cv_wait, &g_mu, next.as_timespec(GPR_CLOCK_MONOTONIC));

    GRPC_TRACE_LOG(timer_check, INFO)
        << "wait ended: was_timed:"
        << (my_timed_waiter_generation == g_timed_waiter_generation)
        << " kicked:" << g_kicked;

    if (my_timed_waiter_generation == g_timed_waiter_generation) {
      ++g_wakeups;
      g_has_timed_waiter = false;
      g_timed_waiter_deadline = grpc_core::Timestamp::InfFuture();
    }
  }

  if (g_kicked) {
    grpc_timer_consume_kick();
    g_kicked = false;
  }

  gpr_mu_unlock(&g_mu);
  return true;
}

static void timer_main_loop() {
  for (;;) {
    grpc_core::Timestamp next = grpc_core::Timestamp::InfFuture();
    grpc_core::ExecCtx::Get()->InvalidateNow();

    switch (grpc_timer_check(&next)) {
      case GRPC_TIMERS_FIRED:
        run_some_timers();
        break;
      case GRPC_TIMERS_NOT_CHECKED:

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

static void timer_thread_cleanup(completed_thread* ct) {
  gpr_mu_lock(&g_mu);

  --g_waiter_count;
  --g_thread_count;
  if (0 == g_thread_count) {
    gpr_cv_signal(&g_cv_shutdown);
  }
  ct->next = g_completed_threads;
  g_completed_threads = ct;
  gpr_mu_unlock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO) << "End timer thread";
}

static void timer_thread(void* completed_thread_ptr) {

  grpc_core::ExecCtx exec_ctx(GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD);
  timer_main_loop();

  timer_thread_cleanup(static_cast<completed_thread*>(completed_thread_ptr));
}

static void start_threads(void) {
  gpr_mu_lock(&g_mu);
  if (!g_threaded) {
    g_threaded = true;
    start_timer_thread_and_unlock();
  } else {
    gpr_mu_unlock(&g_mu);
  }
}

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

static void stop_threads(void) {
  gpr_mu_lock(&g_mu);
  GRPC_TRACE_LOG(timer_check, INFO)
      << "stop timer threads: threaded=" << g_threaded;
  if (g_threaded) {
    g_threaded = false;
    gpr_cv_broadcast(&g_cv_wait);
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

void grpc_timer_manager_shutdown(void) {
  stop_threads();

  gpr_mu_destroy(&g_mu);
  gpr_cv_destroy(&g_cv_wait);
  gpr_cv_destroy(&g_cv_shutdown);
}

void grpc_timer_manager_set_threading(bool enabled) {
  if (enabled) {
    start_threads();
  } else {
    stop_threads();
  }
}

void grpc_timer_manager_set_start_threaded(bool enabled) {
  g_start_threaded = enabled;
}

void grpc_kick_poller(void) {
  gpr_mu_lock(&g_mu);
  g_kicked = true;
  g_has_timed_waiter = false;
  g_timed_waiter_deadline = grpc_core::Timestamp::InfFuture();
  ++g_timed_waiter_generation;
  gpr_cv_signal(&g_cv_wait);
  gpr_mu_unlock(&g_mu);
}

uint64_t grpc_timer_manager_get_wakeups_testonly(void) { return g_wakeups; }
