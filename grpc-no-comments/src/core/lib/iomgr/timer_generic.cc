
// Copyright 2015 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <inttypes.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/iomgr/timer_heap.h"
#include "src/core/util/crash.h"
#include "src/core/util/manual_constructor.h"
#include "src/core/util/spinlock.h"
#include "src/core/util/time.h"
#include "src/core/util/time_averaged_stats.h"
#include "src/core/util/useful.h"

#define INVALID_HEAP_INDEX 0xffffffffu

#define ADD_DEADLINE_SCALE 0.33
#define MIN_QUEUE_WINDOW_DURATION 0.01
#define MAX_QUEUE_WINDOW_DURATION 1.0

struct timer_shard {
  gpr_mu mu;
  grpc_core::ManualConstructor<grpc_core::TimeAveragedStats> stats;

  grpc_core::Timestamp queue_deadline_cap;

  grpc_core::Timestamp min_deadline;

  uint32_t shard_queue_index;

  grpc_timer_heap heap;

  grpc_timer list;
};
static size_t g_num_shards;

static timer_shard* g_shards;

static timer_shard** g_shard_queue;

#ifndef NDEBUG

#define NUM_HASH_BUCKETS 1009

static gpr_mu g_hash_mu[NUM_HASH_BUCKETS];
static grpc_timer* g_timer_ht[NUM_HASH_BUCKETS] = {nullptr};

static void init_timer_ht() {
  for (int i = 0; i < NUM_HASH_BUCKETS; i++) {
    gpr_mu_init(&g_hash_mu[i]);
  }
}

static void destroy_timer_ht() {
  for (int i = 0; i < NUM_HASH_BUCKETS; i++) {
    gpr_mu_destroy(&g_hash_mu[i]);
  }
}

static bool is_in_ht(grpc_timer* t) {
  size_t i = grpc_core::HashPointer(t, NUM_HASH_BUCKETS);

  gpr_mu_lock(&g_hash_mu[i]);
  grpc_timer* p = g_timer_ht[i];
  while (p != nullptr && p != t) {
    p = p->hash_table_next;
  }
  gpr_mu_unlock(&g_hash_mu[i]);

  return (p == t);
}

static void add_to_ht(grpc_timer* t) {
  CHECK(!t->hash_table_next);
  size_t i = grpc_core::HashPointer(t, NUM_HASH_BUCKETS);

  gpr_mu_lock(&g_hash_mu[i]);
  grpc_timer* p = g_timer_ht[i];
  while (p != nullptr && p != t) {
    p = p->hash_table_next;
  }

  if (p == t) {
    grpc_closure* c = t->closure;
    grpc_core::Crash(absl::StrFormat(
        "** Duplicate timer (%p) being added. Closure: (%p), created at: "
        "(%s:%d), scheduled at: (%s:%d) **",
        t, c, c->file_created, c->line_created, c->file_initiated,
        c->line_initiated));
  }

  t->hash_table_next = g_timer_ht[i];
  g_timer_ht[i] = t;
  gpr_mu_unlock(&g_hash_mu[i]);
}

static void remove_from_ht(grpc_timer* t) {
  size_t i = grpc_core::HashPointer(t, NUM_HASH_BUCKETS);
  bool removed = false;

  gpr_mu_lock(&g_hash_mu[i]);
  if (g_timer_ht[i] == t) {
    g_timer_ht[i] = g_timer_ht[i]->hash_table_next;
    removed = true;
  } else if (g_timer_ht[i] != nullptr) {
    grpc_timer* p = g_timer_ht[i];
    while (p->hash_table_next != nullptr && p->hash_table_next != t) {
      p = p->hash_table_next;
    }

    if (p->hash_table_next == t) {
      p->hash_table_next = t->hash_table_next;
      removed = true;
    }
  }
  gpr_mu_unlock(&g_hash_mu[i]);

  if (!removed) {
    grpc_closure* c = t->closure;
    grpc_core::Crash(absl::StrFormat(
        "** Removing timer (%p) that is not added to hash table. Closure "
        "(%p), created at: (%s:%d), scheduled at: (%s:%d) **",
        t, c, c->file_created, c->line_created, c->file_initiated,
        c->line_initiated));
  }

  t->hash_table_next = nullptr;
}

static void validate_non_pending_timer(grpc_timer* t) {
  if (!t->pending && is_in_ht(t)) {
    grpc_closure* c = t->closure;
    grpc_core::Crash(absl::StrFormat(
        "** gpr_timer_cancel() called on a non-pending timer (%p) which "
        "is in the hash table. Closure: (%p), created at: (%s:%d), "
        "scheduled at: (%s:%d) **",
        t, c, c->file_created, c->line_created, c->file_initiated,
        c->line_initiated));
  }
}

#define INIT_TIMER_HASH_TABLE() init_timer_ht()
#define DESTROY_TIMER_HASH_TABLE() destroy_timer_ht()
#define ADD_TO_HASH_TABLE(t) add_to_ht((t))
#define REMOVE_FROM_HASH_TABLE(t) remove_from_ht((t))
#define VALIDATE_NON_PENDING_TIMER(t) validate_non_pending_timer((t))

#else

#define INIT_TIMER_HASH_TABLE()
#define DESTROY_TIMER_HASH_TABLE()
#define ADD_TO_HASH_TABLE(t)
#define REMOVE_FROM_HASH_TABLE(t)
#define VALIDATE_NON_PENDING_TIMER(t)

#endif

static thread_local int64_t g_last_seen_min_timer;

struct shared_mutables {

  grpc_core::Timestamp min_timer;

  gpr_spinlock checker_mu;
  bool initialized;

  gpr_mu mu;
} GPR_ALIGN_STRUCT(GPR_CACHELINE_SIZE);

static struct shared_mutables g_shared_mutables;

static grpc_timer_check_result run_some_expired_timers(
    grpc_core::Timestamp now, grpc_core::Timestamp* next,
    grpc_error_handle error);

static grpc_core::Timestamp compute_min_deadline(timer_shard* shard) {
  return grpc_timer_heap_is_empty(&shard->heap)
             ? shard->queue_deadline_cap + grpc_core::Duration::Epsilon()
             : grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                   grpc_timer_heap_top(&shard->heap)->deadline);
}

static void timer_list_init() {
  uint32_t i;

  g_num_shards = grpc_core::Clamp(2 * gpr_cpu_num_cores(), 1u, 32u);
  g_shards =
      static_cast<timer_shard*>(gpr_zalloc(g_num_shards * sizeof(*g_shards)));
  g_shard_queue = static_cast<timer_shard**>(
      gpr_zalloc(g_num_shards * sizeof(*g_shard_queue)));

  g_shared_mutables.initialized = true;
  g_shared_mutables.checker_mu = GPR_SPINLOCK_INITIALIZER;
  gpr_mu_init(&g_shared_mutables.mu);
  g_shared_mutables.min_timer = grpc_core::Timestamp::Now();

  g_last_seen_min_timer = 0;

  for (i = 0; i < g_num_shards; i++) {
    timer_shard* shard = &g_shards[i];
    gpr_mu_init(&shard->mu);
    shard->stats.Init(1.0 / ADD_DEADLINE_SCALE, 0.1, 0.5);
    shard->queue_deadline_cap = g_shared_mutables.min_timer;
    shard->shard_queue_index = i;
    grpc_timer_heap_init(&shard->heap);
    shard->list.next = shard->list.prev = &shard->list;
    shard->min_deadline = compute_min_deadline(shard);
    g_shard_queue[i] = shard;
  }

  INIT_TIMER_HASH_TABLE();
}

static void timer_list_shutdown() {
  size_t i;
  run_some_expired_timers(grpc_core::Timestamp::InfFuture(), nullptr,
                          GRPC_ERROR_CREATE("Timer list shutdown"));
  for (i = 0; i < g_num_shards; i++) {
    timer_shard* shard = &g_shards[i];
    gpr_mu_destroy(&shard->mu);
    grpc_timer_heap_destroy(&shard->heap);
  }
  gpr_mu_destroy(&g_shared_mutables.mu);
  gpr_free(g_shards);
  gpr_free(g_shard_queue);
  g_shared_mutables.initialized = false;

  DESTROY_TIMER_HASH_TABLE();
}

static void list_join(grpc_timer* head, grpc_timer* timer) {
  timer->next = head;
  timer->prev = head->prev;
  timer->next->prev = timer->prev->next = timer;
}

static void list_remove(grpc_timer* timer) {
  timer->next->prev = timer->prev;
  timer->prev->next = timer->next;
}

static void swap_adjacent_shards_in_queue(uint32_t first_shard_queue_index) {
  timer_shard* temp;
  temp = g_shard_queue[first_shard_queue_index];
  g_shard_queue[first_shard_queue_index] =
      g_shard_queue[first_shard_queue_index + 1];
  g_shard_queue[first_shard_queue_index + 1] = temp;
  g_shard_queue[first_shard_queue_index]->shard_queue_index =
      first_shard_queue_index;
  g_shard_queue[first_shard_queue_index + 1]->shard_queue_index =
      first_shard_queue_index + 1;
}

static void note_deadline_change(timer_shard* shard) {
  while (shard->shard_queue_index > 0 &&
         shard->min_deadline <
             g_shard_queue[shard->shard_queue_index - 1]->min_deadline) {
    swap_adjacent_shards_in_queue(shard->shard_queue_index - 1);
  }
  while (shard->shard_queue_index < g_num_shards - 1 &&
         shard->min_deadline >
             g_shard_queue[shard->shard_queue_index + 1]->min_deadline) {
    swap_adjacent_shards_in_queue(shard->shard_queue_index);
  }
}

void grpc_timer_init_unset(grpc_timer* timer) { timer->pending = false; }

static void timer_init(grpc_timer* timer, grpc_core::Timestamp deadline,
                       grpc_closure* closure) {
  int is_first_timer = 0;
  timer_shard* shard = &g_shards[grpc_core::HashPointer(timer, g_num_shards)];
  timer->closure = closure;
  timer->deadline = deadline.milliseconds_after_process_epoch();

#ifndef NDEBUG
  timer->hash_table_next = nullptr;
#endif

  GRPC_TRACE_VLOG(timer, 2)
      << "TIMER " << timer << ": SET "
      << deadline.milliseconds_after_process_epoch() << " now "
      << grpc_core::Timestamp::Now().milliseconds_after_process_epoch()
      << " call " << closure << "[" << closure->cb << "]";

  if (!g_shared_mutables.initialized) {
    timer->pending = false;
    grpc_core::ExecCtx::Run(
        DEBUG_LOCATION, timer->closure,
        GRPC_ERROR_CREATE("Attempt to create timer before initialization"));
    return;
  }

  gpr_mu_lock(&shard->mu);
  timer->pending = true;
  grpc_core::Timestamp now = grpc_core::Timestamp::Now();
  if (deadline <= now) {
    timer->pending = false;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, timer->closure, absl::OkStatus());
    gpr_mu_unlock(&shard->mu);

    return;
  }

  shard->stats->AddSample((deadline - now).millis() / 1000.0);

  ADD_TO_HASH_TABLE(timer);

  if (deadline < shard->queue_deadline_cap) {
    is_first_timer = grpc_timer_heap_add(&shard->heap, timer);
  } else {
    timer->heap_index = INVALID_HEAP_INDEX;
    list_join(&shard->list, timer);
  }
  GRPC_TRACE_VLOG(timer, 2)
      << "  .. add to shard " << (shard - g_shards)
      << " with queue_deadline_cap="
      << shard->queue_deadline_cap.milliseconds_after_process_epoch()
      << " => is_first_timer=" << (is_first_timer ? "true" : "false");
  gpr_mu_unlock(&shard->mu);

  if (is_first_timer) {
    gpr_mu_lock(&g_shared_mutables.mu);
    GRPC_TRACE_VLOG(timer, 2)
        << "  .. old shard min_deadline="
        << shard->min_deadline.milliseconds_after_process_epoch();
    if (deadline < shard->min_deadline) {
      grpc_core::Timestamp old_min_deadline = g_shard_queue[0]->min_deadline;
      shard->min_deadline = deadline;
      note_deadline_change(shard);
      if (shard->shard_queue_index == 0 && deadline < old_min_deadline) {
#if GPR_ARCH_64

        gpr_atm_no_barrier_store((gpr_atm*)(&g_shared_mutables.min_timer),
                                 deadline.milliseconds_after_process_epoch());
#else

        g_shared_mutables.min_timer = deadline;
#endif
        grpc_kick_poller();
      }
    }
    gpr_mu_unlock(&g_shared_mutables.mu);
  }
}

static void timer_consume_kick(void) {

  g_last_seen_min_timer = 0;
}

static void timer_cancel(grpc_timer* timer) {
  if (!g_shared_mutables.initialized) {

    return;
  }

  timer_shard* shard = &g_shards[grpc_core::HashPointer(timer, g_num_shards)];
  gpr_mu_lock(&shard->mu);
  GRPC_TRACE_VLOG(timer, 2)
      << "TIMER " << timer
      << ": CANCEL pending=" << (timer->pending ? "true" : "false");

  if (timer->pending) {
    REMOVE_FROM_HASH_TABLE(timer);

    grpc_core::ExecCtx::Run(DEBUG_LOCATION, timer->closure,
                            absl::CancelledError());
    timer->pending = false;
    if (timer->heap_index == INVALID_HEAP_INDEX) {
      list_remove(timer);
    } else {
      grpc_timer_heap_remove(&shard->heap, timer);
    }
  } else {
    VALIDATE_NON_PENDING_TIMER(timer);
  }
  gpr_mu_unlock(&shard->mu);
}

static bool refill_heap(timer_shard* shard, grpc_core::Timestamp now) {

  double computed_deadline_delta =
      shard->stats->UpdateAverage() * ADD_DEADLINE_SCALE;
  double deadline_delta =
      grpc_core::Clamp(computed_deadline_delta, MIN_QUEUE_WINDOW_DURATION,
                       MAX_QUEUE_WINDOW_DURATION);
  grpc_timer *timer, *next;

  shard->queue_deadline_cap =
      std::max(now, shard->queue_deadline_cap) +
      grpc_core::Duration::FromSecondsAsDouble(deadline_delta);

  GRPC_TRACE_VLOG(timer_check, 2)
      << "  .. shard[" << (shard - g_shards) << "]->queue_deadline_cap --> "
      << shard->queue_deadline_cap.milliseconds_after_process_epoch();
  for (timer = shard->list.next; timer != &shard->list; timer = next) {
    next = timer->next;
    auto timer_deadline =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            timer->deadline);

    if (timer_deadline < shard->queue_deadline_cap) {
      GRPC_TRACE_VLOG(timer_check, 2)
          << "  .. add timer with deadline "
          << timer_deadline.milliseconds_after_process_epoch() << " to heap";
      list_remove(timer);
      grpc_timer_heap_add(&shard->heap, timer);
    }
  }
  return !grpc_timer_heap_is_empty(&shard->heap);
}

static grpc_timer* pop_one(timer_shard* shard, grpc_core::Timestamp now) {
  grpc_timer* timer;
  for (;;) {
    GRPC_TRACE_VLOG(timer_check, 2)
        << "  .. shard[" << (shard - g_shards) << "]: heap_empty="
        << (grpc_timer_heap_is_empty(&shard->heap) ? "true" : "false");
    if (grpc_timer_heap_is_empty(&shard->heap)) {
      if (now < shard->queue_deadline_cap) return nullptr;
      if (!refill_heap(shard, now)) return nullptr;
    }
    timer = grpc_timer_heap_top(&shard->heap);
    auto timer_deadline =
        grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
            timer->deadline);
    GRPC_TRACE_VLOG(timer_check, 2)
        << "  .. check top timer deadline="
        << timer_deadline.milliseconds_after_process_epoch()
        << " now=" << now.milliseconds_after_process_epoch();
    if (timer_deadline > now) return nullptr;
    GRPC_TRACE_VLOG(timer, 2) << "TIMER " << timer << ": FIRE "
                              << (now - timer_deadline).millis() << "ms late";
    timer->pending = false;
    grpc_timer_heap_pop(&shard->heap);
    return timer;
  }
}

static size_t pop_timers(timer_shard* shard, grpc_core::Timestamp now,
                         grpc_core::Timestamp* new_min_deadline,
                         grpc_error_handle error) {
  size_t n = 0;
  grpc_timer* timer;
  gpr_mu_lock(&shard->mu);
  while ((timer = pop_one(shard, now))) {
    REMOVE_FROM_HASH_TABLE(timer);
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, timer->closure, error);
    n++;
  }
  *new_min_deadline = compute_min_deadline(shard);
  gpr_mu_unlock(&shard->mu);
  GRPC_TRACE_VLOG(timer_check, 2)
      << "  .. shard[" << (shard - g_shards) << "] popped " << n;
  return n;
}

static grpc_timer_check_result run_some_expired_timers(
    grpc_core::Timestamp now, grpc_core::Timestamp* next,
    grpc_error_handle error) {
  grpc_timer_check_result result = GRPC_TIMERS_NOT_CHECKED;

#if GPR_ARCH_64

  grpc_core::Timestamp min_timer =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
          gpr_atm_no_barrier_load((gpr_atm*)(&g_shared_mutables.min_timer)));
#else

  gpr_mu_lock(&g_shared_mutables.mu);
  grpc_core::Timestamp min_timer = g_shared_mutables.min_timer;
  gpr_mu_unlock(&g_shared_mutables.mu);
#endif
  g_last_seen_min_timer = min_timer.milliseconds_after_process_epoch();

  if (now < min_timer) {
    if (next != nullptr) *next = std::min(*next, min_timer);
    return GRPC_TIMERS_CHECKED_AND_EMPTY;
  }

  if (gpr_spinlock_trylock(&g_shared_mutables.checker_mu)) {
    gpr_mu_lock(&g_shared_mutables.mu);
    result = GRPC_TIMERS_CHECKED_AND_EMPTY;

    GRPC_TRACE_VLOG(timer_check, 2)
        << "  .. shard[" << (g_shard_queue[0] - g_shards)
        << "]->min_deadline = "
        << g_shard_queue[0]->min_deadline.milliseconds_after_process_epoch();

    while (g_shard_queue[0]->min_deadline < now ||
           (now != grpc_core::Timestamp::InfFuture() &&
            g_shard_queue[0]->min_deadline == now)) {
      grpc_core::Timestamp new_min_deadline;

      if (pop_timers(g_shard_queue[0], now, &new_min_deadline, error) > 0) {
        result = GRPC_TIMERS_FIRED;
      }

      GRPC_TRACE_VLOG(timer_check, 2)
          << "  .. result --> " << result << ", shard["
          << (g_shard_queue[0] - g_shards) << "]->min_deadline "
          << g_shard_queue[0]->min_deadline.milliseconds_after_process_epoch()
          << " --> " << new_min_deadline.milliseconds_after_process_epoch()
          << ", now=" << now.milliseconds_after_process_epoch();

      g_shard_queue[0]->min_deadline = new_min_deadline;
      note_deadline_change(g_shard_queue[0]);
    }

    if (next) {
      *next = std::min(*next, g_shard_queue[0]->min_deadline);
    }

#if GPR_ARCH_64

    gpr_atm_no_barrier_store(
        (gpr_atm*)(&g_shared_mutables.min_timer),
        g_shard_queue[0]->min_deadline.milliseconds_after_process_epoch());
#else

    g_shared_mutables.min_timer = g_shard_queue[0]->min_deadline;
#endif
    gpr_mu_unlock(&g_shared_mutables.mu);
    gpr_spinlock_unlock(&g_shared_mutables.checker_mu);
  }

  return result;
}

static grpc_timer_check_result timer_check(grpc_core::Timestamp* next) {

  grpc_core::Timestamp now = grpc_core::Timestamp::Now();

  grpc_core::Timestamp min_timer =
      grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
          g_last_seen_min_timer);

  if (now < min_timer) {
    if (next != nullptr) {
      *next = std::min(*next, min_timer);
    }
    GRPC_TRACE_VLOG(timer_check, 2)
        << "TIMER CHECK SKIP: now=" << now.milliseconds_after_process_epoch()
        << " min_timer=" << min_timer.milliseconds_after_process_epoch();
    return GRPC_TIMERS_CHECKED_AND_EMPTY;
  }

  grpc_error_handle shutdown_error =
      now != grpc_core::Timestamp::InfFuture()
          ? absl::OkStatus()
          : GRPC_ERROR_CREATE("Shutting down timer system");

  if (GRPC_TRACE_FLAG_ENABLED(timer_check)) {
    std::string next_str;
    if (next == nullptr) {
      next_str = "NULL";
    } else {
      next_str = absl::StrCat(next->milliseconds_after_process_epoch());
    }
#if GPR_ARCH_64
    VLOG(2) << "TIMER CHECK BEGIN: now="
            << now.milliseconds_after_process_epoch() << " next=" << next_str
            << " tls_min=" << min_timer.milliseconds_after_process_epoch()
            << " glob_min="
            << grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                   gpr_atm_no_barrier_load(
                       (gpr_atm*)(&g_shared_mutables.min_timer)))
                   .milliseconds_after_process_epoch();
#else
    VLOG(2) << "TIMER CHECK BEGIN: now="
            << now.milliseconds_after_process_epoch() << " next=" << next_str
            << " min=" << min_timer.milliseconds_after_process_epoch();
#endif
  }

  grpc_timer_check_result r =
      run_some_expired_timers(now, next, shutdown_error);

  if (GRPC_TRACE_FLAG_ENABLED(timer_check)) {
    std::string next_str;
    if (next == nullptr) {
      next_str = "NULL";
    } else {
      next_str = absl::StrCat(next->milliseconds_after_process_epoch());
    }
    VLOG(2) << "TIMER CHECK END: r=" << r << "; next=" << next_str.c_str();
  }
  return r;
}

grpc_timer_vtable grpc_generic_timer_vtable = {
    timer_init,      timer_cancel,        timer_check,
    timer_list_init, timer_list_shutdown, timer_consume_kick};
