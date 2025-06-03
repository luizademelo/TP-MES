Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <assert.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "absl/log/check.h"

// Number of partitions for synchronization array to reduce contention
enum { event_sync_partitions = 31 };

// Structure containing synchronization primitives for each partition
static struct sync_array_s {
  gpr_mu mu;       // Mutex for synchronization
  gpr_cv cv;       // Condition variable for signaling
} sync_array[event_sync_partitions];

// One-time initialization control for sync_array
static gpr_once event_once = GPR_ONCE_INIT;

// Initializes all synchronization primitives in sync_array
static void event_initialize(void) {
  int i;
  for (i = 0; i != event_sync_partitions; i++) {
    gpr_mu_init(&sync_array[i].mu);
    gpr_cv_init(&sync_array[i].cv);
  }
}

// Returns the sync_array partition for a given event using pointer hashing
static struct sync_array_s* hash(gpr_event* ev) {
  return &sync_array[reinterpret_cast<uintptr_t>(ev) % event_sync_partitions];
}

// Initializes an event with state 0 (not set)
void gpr_event_init(gpr_event* ev) {
  gpr_once_init(&event_once, &event_initialize);
  ev->state = 0;
}

// Sets an event's state to the given value and broadcasts to waiters
// Can only be called once per event (state must be 0)
void gpr_event_set(gpr_event* ev, void* value) {
  struct sync_array_s* s = hash(ev);
  gpr_mu_lock(&s->mu);
  CHECK_EQ(gpr_atm_acq_load(&ev->state), 0);  // Verify event wasn't already set
  gpr_atm_rel_store(&ev->state, (gpr_atm)value);
  gpr_cv_broadcast(&s->cv);  // Notify all waiting threads
  gpr_mu_unlock(&s->mu);
  CHECK_NE(value, nullptr);  // Ensure non-null value is set
}

// Returns the current value of the event without waiting
void* gpr_event_get(gpr_event* ev) {
  return reinterpret_cast<void*>(gpr_atm_acq_load(&ev->state));
}

// Waits until the event is set or deadline expires, returns event value
void* gpr_event_wait(gpr_event* ev, gpr_timespec abs_deadline) {
  void* result = reinterpret_cast<void*>(gpr_atm_acq_load(&ev->state));
  if (result == nullptr) {
    struct sync_array_s* s = hash(ev);
    gpr_mu_lock(&s->mu);
    // Wait in loop to handle spurious wakeups
    do {
      result = reinterpret_cast<void*>(gpr_atm_acq_load(&ev->state));
    } while (result == nullptr && !gpr_cv_wait(&s->cv, &s->mu, abs_deadline));
    gpr_mu_unlock(&s->mu);
  }
  return result;
}

// Reference counting utilities

// Initializes a reference counter with initial value n
void gpr_ref_init(gpr_refcount* r, int n) { gpr_atm_rel_store(&r->count, n); }

// Increments reference count (no memory barrier)
void gpr_ref(gpr_refcount* r) { gpr_atm_no_barrier_fetch_add(&r->count, 1); }

// Increments reference count and verifies it wasn't zero (debug mode only)
void gpr_ref_non_zero(gpr_refcount* r) {
#ifndef NDEBUG
  gpr_atm prior = gpr_atm_no_barrier_fetch_add(&r->count, 1);
  assert(prior > 0);
#else
  gpr_ref(r);
#endif
}

// Increments reference count by n (no memory barrier)
void gpr_refn(gpr_refcount* r, int n) {
  gpr_atm_no_barrier_fetch_add(&r->count, n);
}

// Decrements reference count (with full barrier)
// Returns true if count reached zero
int gpr_unref(gpr_refcount* r) {
  gpr_atm prior = gpr_atm_full_fetch_add(&r->count, -1);
  CHECK_GT(prior, 0);  // Ensure we don't underflow
  return prior == 1;    // Return if this was the last reference
}

// Checks if reference count is exactly 1 (with acquire barrier)
int gpr_ref_is_unique(gpr_refcount* r) {
  return gpr_atm_acq_load(&r->count) == 1;
}

// Statistics counter utilities

// Initializes a stats counter with value n
void gpr_stats_init(gpr_stats_counter* c, intptr_t n) {
  gpr_atm_rel_store(&c->value, n);
}

// Increments a stats counter by inc (no memory barrier)
void gpr_stats_inc(gpr_stats_counter* c, intptr_t inc) {
  gpr_atm_no_barrier_fetch_add(&c->value, inc);
}

// Reads current value of stats counter (with acquire barrier)
intptr_t gpr_stats_read(const gpr_stats_counter* c) {
  return gpr_atm_acq_load(&c->value);
}
```