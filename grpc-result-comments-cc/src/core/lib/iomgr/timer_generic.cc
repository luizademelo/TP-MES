Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for gRPC support, platform-specific functionality,
// synchronization primitives, and utility functions
#include <grpc/support/alloc.h>
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <inttypes.h>

#include <string>

// Include ABSL (Abseil) libraries for logging, string operations, and checks
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"

// Include gRPC core internal headers
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

// Constants for timer management
#define INVALID_HEAP_INDEX 0xffffffffu  // Marker for timers not in heap
#define ADD_DEADLINE_SCALE 0.33         // Scaling factor for deadline calculation
#define MIN_QUEUE_WINDOW_DURATION 0.01  // Minimum queue window duration (seconds)
#define MAX_QUEUE_WINDOW_DURATION 1.0   // Maximum queue window duration (seconds)

// Structure representing a shard of timers
struct timer_shard {
  gpr_mu mu;  // Mutex for thread safety
  grpc_core::ManualConstructor<grpc_core::TimeAveragedStats> stats;  // Stats for deadline calculation

  grpc_core::Timestamp queue_deadline_cap;  // Deadline cap for this shard's queue
  grpc_core::Timestamp min_deadline;       // Minimum deadline in this shard
  uint32_t shard_queue_index;              // Index in the global shard queue

  grpc_timer_heap heap;  // Heap structure for managing timers
  grpc_timer list;       // Linked list of timers
};

// Global variables for timer management
static size_t g_num_shards;       // Number of timer shards
static timer_shard* g_shards;     // Array of timer shards
static timer_shard** g_shard_queue;  // Priority queue of shards based on deadlines

#ifndef NDEBUG  // Debug-only code for timer validation

// Hash table configuration for timer validation
#define NUM_HASH_BUCKETS 1009
static gpr_mu g_hash_mu[NUM_HASH_BUCKETS];  // Mutexes for hash buckets
static grpc_timer* g_timer_ht[NUM_HASH_BUCKETS] = {nullptr};  // Hash table for timers

// Initialize the timer hash table
static void init_timer_ht() {
  for (int i = 0; i < NUM_HASH_BUCKETS; i++) {
    gpr_mu_init(&g_hash_mu[i]);
  }
}

// Destroy the timer hash table
static void destroy_timer_ht() {
  for (int i = 0; i < NUM_HASH_BUCKETS; i++) {
    gpr_mu_destroy(&g_hash_mu[i]);
  }
}

// Check if a timer is in the hash table
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

// Add a timer to the hash table
static void add_to_ht(grpc_timer* t) {
  CHECK(!t->hash_table_next);
  size_t i = grpc_core::HashPointer(t, NUM_HASH_BUCKETS);

  gpr_mu_lock(&g_hash_mu[i]);
  grpc_timer* p = g_timer_ht[i];
  while (p != nullptr && p != t) {
    p = p->hash_table_next;
  }

  if (p == t) {
    // Crash if trying to add a duplicate timer
    grpc_closure* c = t->closure;
    grpc_core::Crash(absl::StrFormat(
        "** Duplicate timer (%p) being added. Closure: (%p), created at: "
        "(%s:%d), scheduled at: (%s:%d) **",
        t, c, c->file_created, c->line_created, c->file_initiated,
        c->line_initiated));
  }

  // Add to head of the bucket's linked list
  t->hash_table_next = g_timer_ht[i];
  g_timer_ht[i] = t;
  gpr_mu_unlock(&g_hash_mu[i]);
}

// Remove a timer from the hash table
static void remove_from_ht(grpc_timer* t) {
  size_t i = grpc_core::HashPointer(t, NUM_HASH_BUCKETS);
  bool removed = false;

  gpr_mu_lock(&g_hash_mu[i]);
  if (g_timer_ht[i] == t) {
    // Remove from head of the bucket
    g_timer_ht[i] = g_timer_ht[i]->hash_table_next;
    removed = true;
  } else if (g_timer_ht[i] != nullptr) {
    // Search through the bucket's linked list
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
    // Crash if trying to remove a timer not in the hash table
    grpc_closure* c = t->closure;
    grpc_core::Crash(absl::StrFormat(
        "** Removing timer (%p) that is not added to hash table. Closure "
        "(%p), created at: (%s:%d), scheduled at: (%s:%d) **",
        t, c, c->file_created, c->line_created, c->file_initiated,
        c->line_initiated));
  }

  t->hash_table_next = nullptr;
}

// Validate that a non-pending timer is not in the hash table
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

// Macros for timer hash table operations in debug mode
#define INIT_TIMER_HASH_TABLE() init_timer_ht()
#define DESTROY_TIMER_HASH_TABLE() destroy_timer_ht()
#define ADD_TO_HASH_TABLE(t) add_to_ht((t))
#define REMOVE_FROM_HASH_TABLE(t) remove_from_ht((t))
#define VALIDATE_NON_PENDING_TIMER(t) validate_non_pending_timer((t))

#else  // Non-debug mode - hash table operations are no-ops

#define INIT_TIMER_HASH_TABLE()
#define DESTROY_TIMER_HASH_TABLE()
#define ADD_TO_HASH_TABLE(t)
#define REMOVE_FROM_HASH_TABLE(t)
#define VALIDATE_NON_PENDING_TIMER(t)

#endif

// Thread-local variable to track the last seen minimum timer
static thread_local int64_t g_last_seen_min_timer;

// Structure for shared mutable state across threads
struct shared_mutables {
  grpc_core::Timestamp min_timer;  // Minimum timer deadline across all shards
  gpr_spinlock checker_mu;         // Spinlock for timer checking
  bool initialized;                // Flag indicating if timer system is initialized
  gpr_mu mu;                      // Mutex for shared state
} GPR_ALIGN_STRUCT(GPR_CACHELINE_SIZE);  // Align to cache line to prevent false sharing

// Global instance of shared mutables
static struct shared_mutables g_shared_mutables;

// Forward declaration
static grpc_timer_check_result run_some_expired_timers(
    grpc_core::Timestamp now, grpc_core::Timestamp* next,
    grpc_error_handle error);

// Compute the minimum deadline for a shard
static grpc_core::Timestamp compute_min_deadline(timer_shard* shard) {
  return grpc_timer_heap_is_empty(&shard->heap)
             ? shard->queue_deadline_cap + grpc_core::Duration::Epsilon()
             : grpc_core::Timestamp::FromMillisecondsAfterProcessEpoch(
                   grpc_timer_heap_top(&shard->heap)->deadline);
}

// Initialize the timer list and shards
static void timer_list_init() {
  uint32_t i;

  // Determine number of shards (2x number of CPU cores, clamped between 1 and 32)
  g_num_shards = grpc_core::Clamp(2 * gpr_cpu_num_cores(), 1u, 32u);
  g_shards =
      static_cast<timer_shard*>(gpr_zalloc(g_num_shards * sizeof(*g_shards)));
  g_shard_queue = static_cast<timer_shard**>(
      gpr_zalloc(g_num_shards * sizeof(*g_shard_queue)));

  // Initialize shared mutables
  g_shared_mutables.initialized = true;
  g_shared_mutables.checker_mu = GPR_SPINLOCK_INITIALIZER;
  gpr_mu_init(&g_shared_mutables.mu);
  g_shared_mutables.min_timer = grpc_core::Timestamp::Now();

  g_last_seen_min_timer = 0;

  // Initialize each shard
  for (i = 0; i < g_num_shards; i++) {
    timer_shard* shard = &g_shards[i];
    gpr_mu_init(&shard->mu);
    shard->stats.Init(1.0 / ADD_DEADLINE_SCALE, 0.1, 0.5);  // Initialize stats
    shard->queue_deadline_cap = g_shared_mutables.min_timer;
    shard->shard_queue_index = i;
    grpc_timer_heap_init(&shard->heap);
    shard->list.next = shard->list.prev = &shard->list;  // Initialize empty list
    shard->min_deadline = compute_min_deadline(shard);
    g_shard_queue[i] = shard;
  }

  INIT_TIMER_HASH_TABLE();  // Initialize debug hash table if in debug mode
}

// Shutdown the timer list and clean up resources
static void timer_list_shutdown() {
  size_t i;
  // Run any remaining expired timers with shutdown error
  run_some_expired_timers(grpc_core::Timestamp::InfFuture(), nullptr,
                          GRPC_ERROR_CREATE("Timer list shutdown"));
  // Clean up each shard
  for (i = 0; i < g_num_shards; i++) {
    timer_shard* shard = &g_shards[i];
    gpr_mu_destroy(&shard->mu);
    grpc_timer_heap_destroy(&shard->heap);
  }
  // Clean up shared state
  gpr_mu_destroy(&g_shared_mutables.mu);
  gpr_free(g_shards);
  gpr_free(g_shard_queue);
  g_shared_mutables.initialized = false;

  DESTROY_TIMER_HASH_TABLE();  // Clean up debug hash table if in debug mode
}

// Join a timer to a list
static void list_join(grpc_timer* head, grpc_timer* timer) {
  timer->next = head;
  timer->prev = head->prev;
  timer->next->prev = timer->prev->next = timer;
}

// Remove a timer from a list
static void list_remove(grpc_timer* timer) {
  timer->next->prev = timer->prev;
  timer->prev->next = timer->next;
}

// Swap two adjacent shards in the queue
static void swap_adjacent_shards_in_queue(uint32_t first_shard_queue_index) {
  timer_shard* temp;
  temp = g_shard_queue[first_shard_queue_index];
  g_shard_queue[first_shard_queue_index] =
      g_shard_queue[first_shard_queue_index + 1];
  g_shard_queue[first_shard_queue_index + 1] = temp;
  // Update indices after swap
  g_shard_queue[first_shard_queue_index]->shard_queue_index =
      first_shard_queue_index;
  g_shard_queue[first_shard_queue_index + 1]->shard_queue_index =
      first_shard_queue_index + 1;
}

// Adjust shard queue position when a shard's deadline changes
static void note_deadline_change(timer_shard* shard) {
  // Move shard up in queue if its deadline is smaller than previous shard
  while (shard->shard_queue_index > 0 &&
         shard->min_deadline <
             g_shard_queue[shard->shard_queue_index - 1]->min_deadline) {
    swap_adjacent_shards_in_queue(shard->shard_queue_index - 1);
  }
  // Move shard down in queue if its deadline is larger than next shard
  while (shard->shard_queue_index < g_num_shards - 1 &&
         shard->min_deadline >
             g_shard_queue[shard->shard_queue_index + 1]->min_deadline) {
    swap_adjacent_shards_in_queue(shard->shard_queue_index);
  }
}

// Initialize a timer as unset
void grpc_timer_init_unset(grpc_timer* timer) { timer->pending = false; }

// Initialize and set a timer
static void timer_init(grpc_timer* timer, grpc_core::Timestamp deadline,
                       grpc_closure* closure) {
  int is_first_timer = 0;
  // Select shard based on timer pointer hash
  timer_shard* shard = &g_shards[grpc_core::HashPointer(timer, g_num_shards)];
  timer->closure = closure;
  timer->deadline = deadline.milliseconds_after_process_epoch();

#ifndef NDEBUG
  timer->hash_table_next = nullptr;  // Initialize debug pointer
#endif

  GRPC_TRACE_VLOG(timer, 2)
      << "TIMER " << timer << ": SET "
      << deadline.milliseconds_after_process_epoch() << " now "
      << grpc_core::Timestamp::Now().milliseconds_after_process_epoch()
      << " call " << closure << "[" << closure->cb << "]";

  // Handle case where timer system isn't initialized
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
  
  // Handle immediate expiration case
  if (deadline <= now) {
    timer->pending = false;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, timer->closure, absl::OkStatus());
    gpr_mu_unlock(&shard->mu);
    return;
  }

  // Update statistics with new timer's deadline
  shard->stats->AddSample((deadline - now).millis() / 1000.0);

  ADD_TO_HASH_TABLE(timer);  // Add to debug hash table if in debug mode

  // Add timer to either heap or list based on deadline
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

  // If this is the earliest timer in the shard, update shared state
  if (is_first_timer) {
    gpr_mu_lock(&g_shared_mutables.mu);
    GRPC_TRACE_VLOG(timer, 2)
        << "  .. old shard min_deadline="
        << shard->min_deadline.milliseconds_after_process_epoch();
    if (deadline < shard->min_deadline) {
      grpc_core::Timestamp old_min_deadline = g_shard_queue[0]->min