Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_SUPPORT_SYNC_H
#define GRPC_SUPPORT_SYNC_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#ifdef __cplusplus
extern "C" {
#endif

// Include generic synchronization primitives
#include <grpc/support/sync_generic.h>

// Platform-specific synchronization implementations
#if defined(GPR_CUSTOM_SYNC)
#include <grpc/support/sync_custom.h>  // Custom synchronization implementation
#elif defined(GPR_ABSEIL_SYNC)
#include <grpc/support/sync_abseil.h>  // Abseil-based synchronization
#elif defined(GPR_POSIX_SYNC)
#include <grpc/support/sync_posix.h>   // POSIX synchronization (pthreads)
#elif defined(GPR_WINDOWS)
#include <grpc/support/sync_windows.h> // Windows synchronization
#else
#error Unable to determine platform for sync
#endif

// Mutex operations
GPRAPI void gpr_mu_init(gpr_mu* mu);       // Initialize a mutex
GPRAPI void gpr_mu_destroy(gpr_mu* mu);    // Destroy a mutex
GPRAPI void gpr_mu_lock(gpr_mu* mu);       // Lock a mutex (blocking)
GPRAPI void gpr_mu_unlock(gpr_mu* mu);     // Unlock a mutex
GPRAPI int gpr_mu_trylock(gpr_mu* mu);     // Try to lock a mutex (non-blocking)

// Condition variable operations
GPRAPI void gpr_cv_init(gpr_cv* cv);       // Initialize a condition variable
GPRAPI void gpr_cv_destroy(gpr_cv* cv);    // Destroy a condition variable
GPRAPI int gpr_cv_wait(gpr_cv* cv, gpr_mu* mu, gpr_timespec abs_deadline); // Wait on condition variable
GPRAPI void gpr_cv_signal(gpr_cv* cv);     // Signal one waiting thread
GPRAPI void gpr_cv_broadcast(gpr_cv* cv);  // Signal all waiting threads

// One-time initialization
GPRAPI void gpr_once_init(gpr_once* once, void (*init_function)(void)); // Execute init_function exactly once

// Event operations
GPRAPI void gpr_event_init(gpr_event* ev); // Initialize an event
GPRAPI void gpr_event_set(gpr_event* ev, void* value); // Set event with value
GPRAPI void* gpr_event_get(gpr_event* ev); // Get current event value
GPRAPI void* gpr_event_wait(gpr_event* ev, gpr_timespec abs_deadline); // Wait for event to be set

// Reference counting operations
GPRAPI void gpr_ref_init(gpr_refcount* r, int n); // Initialize refcount to n
GPRAPI void gpr_ref(gpr_refcount* r);             // Increment refcount by 1
GPRAPI void gpr_ref_non_zero(gpr_refcount* r);    // Increment if not zero
GPRAPI void gpr_refn(gpr_refcount* r, int n);    // Increment refcount by n
GPRAPI int gpr_unref(gpr_refcount* r);           // Decrement refcount, return true if reached zero
GPRAPI int gpr_ref_is_unique(gpr_refcount* r);   // Check if refcount is 1

// Statistics counter operations
GPRAPI void gpr_stats_init(gpr_stats_counter* c, intptr_t n); // Initialize counter
GPRAPI void gpr_stats_inc(gpr_stats_counter* c, intptr_t inc); // Increment counter
GPRAPI intptr_t gpr_stats_read(const gpr_stats_counter* c);    // Read counter value

#if 0
// Example implementation of a thread-safe queue (currently disabled)
#define N 4

   typedef struct queue {
     gpr_cv non_empty;  // Signaled when queue is not empty
     gpr_cv non_full;   // Signaled when queue is not full
     gpr_mu mu;         // Mutex protecting queue operations

     int head;          // Index of first element
     int length;        // Current number of elements
     int elem[N];       // Circular buffer for elements
   } queue;

   // Initialize queue and synchronization primitives
   void queue_init(queue *q) {
     gpr_mu_init(&q->mu);
     gpr_cv_init(&q->non_empty);
     gpr_cv_init(&q->non_full);
     q->head = 0;
     q->length = 0;
   }

   // Clean up queue resources
   void queue_destroy(queue *q) {
     gpr_mu_destroy(&q->mu);
     gpr_cv_destroy(&q->non_empty);
     gpr_cv_destroy(&q->non_full);
   }

   // Add element to queue (blocking if full)
   void queue_append(queue *q, int x) {
     gpr_mu_lock(&q->mu);

     // Wait while queue is full
     while (q->length == N) {
       gpr_cv_wait(&q->non_full, &q->mu, gpr_inf_future);
     }
     // Signal if queue was empty
     if (q->length == 0) {
       gpr_cv_broadcast(&q->non_empty);
     }
     // Add element to circular buffer
     q->elem[(q->head + q->length) % N] = x;
     q->length++;
     gpr_mu_unlock(&q->mu);
   }

   // Try to add element to queue (non-blocking)
   int queue_try_append(queue *q, int x) {
     int result = 0;
     if (gpr_mu_trylock(&q->mu)) {
       if (q->length != N) {
         if (q->length == 0) {
           gpr_cv_broadcast(&q->non_empty);
         }
         q->elem[(q->head + q->length) % N] = x;
         q->length++;
         result = 1;
       }
       gpr_mu_unlock(&q->mu);
     }
     return result;
   }

   // Remove element from queue (blocking with timeout)
   int queue_remove(queue *q, int *head, gpr_timespec abs_deadline) {
     int result = 0;
     gpr_mu_lock(&q->mu);

     // Wait while queue is empty (with timeout)
     while (q->length == 0 &&
            !gpr_cv_wait(&q->non_empty, &q->mu, abs_deadline)) {
     }
     if (q->length != 0) {
       result = 1;
       // Signal if queue was full
       if (q->length == N) {
         gpr_cv_broadcast(&q->non_full);
       }
       *head = q->elem[q->head];
       q->head = (q->head + 1) % N;
       q->length--;
     }
     gpr_mu_unlock(&q->mu);
     return result;
   }
#endif

#ifdef __cplusplus
}
#endif

#endif
```

The comments explain:
1. The purpose of each include directive and platform-specific implementation
2. The functionality of each synchronization primitive (mutex, condition variable, etc.)
3. The reference counting operations
4. The statistics counter operations
5. The example queue implementation (currently disabled) with detailed comments for each operation

The comments are clear, concise, and provide enough context for future developers to understand the code's purpose and functionality.