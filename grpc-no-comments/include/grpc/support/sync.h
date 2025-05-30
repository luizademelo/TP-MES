
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

#include <grpc/support/sync_generic.h>

#if defined(GPR_CUSTOM_SYNC)
#include <grpc/support/sync_custom.h>
#elif defined(GPR_ABSEIL_SYNC)
#include <grpc/support/sync_abseil.h>
#elif defined(GPR_POSIX_SYNC)
#include <grpc/support/sync_posix.h>
#elif defined(GPR_WINDOWS)
#include <grpc/support/sync_windows.h>
#else
#error Unable to determine platform for sync
#endif

GPRAPI void gpr_mu_init(gpr_mu* mu);

GPRAPI void gpr_mu_destroy(gpr_mu* mu);

GPRAPI void gpr_mu_lock(gpr_mu* mu);

GPRAPI void gpr_mu_unlock(gpr_mu* mu);

GPRAPI int gpr_mu_trylock(gpr_mu* mu);

GPRAPI void gpr_cv_init(gpr_cv* cv);

GPRAPI void gpr_cv_destroy(gpr_cv* cv);

GPRAPI int gpr_cv_wait(gpr_cv* cv, gpr_mu* mu, gpr_timespec abs_deadline);

GPRAPI void gpr_cv_signal(gpr_cv* cv);

GPRAPI void gpr_cv_broadcast(gpr_cv* cv);

GPRAPI void gpr_once_init(gpr_once* once, void (*init_function)(void));

GPRAPI void gpr_event_init(gpr_event* ev);

GPRAPI void gpr_event_set(gpr_event* ev, void* value);

GPRAPI void* gpr_event_get(gpr_event* ev);

GPRAPI void* gpr_event_wait(gpr_event* ev, gpr_timespec abs_deadline);

GPRAPI void gpr_ref_init(gpr_refcount* r, int n);

GPRAPI void gpr_ref(gpr_refcount* r);

GPRAPI void gpr_ref_non_zero(gpr_refcount* r);

GPRAPI void gpr_refn(gpr_refcount* r, int n);

GPRAPI int gpr_unref(gpr_refcount* r);

GPRAPI int gpr_ref_is_unique(gpr_refcount* r);

GPRAPI void gpr_stats_init(gpr_stats_counter* c, intptr_t n);

GPRAPI void gpr_stats_inc(gpr_stats_counter* c, intptr_t inc);

GPRAPI intptr_t gpr_stats_read(const gpr_stats_counter* c);

#if 0

#define N 4

   typedef struct queue {
     gpr_cv non_empty;
     gpr_cv non_full;
     gpr_mu mu;

     int head;
     int length;
     int elem[N];
   } queue;

   void queue_init(queue *q) {
     gpr_mu_init(&q->mu);
     gpr_cv_init(&q->non_empty);
     gpr_cv_init(&q->non_full);
     q->head = 0;
     q->length = 0;
   }

   void queue_destroy(queue *q) {
     gpr_mu_destroy(&q->mu);
     gpr_cv_destroy(&q->non_empty);
     gpr_cv_destroy(&q->non_full);
   }

   void queue_append(queue *q, int x) {
     gpr_mu_lock(&q->mu);

     while (q->length == N) {
       gpr_cv_wait(&q->non_full, &q->mu, gpr_inf_future);
     }
     if (q->length == 0) {

       gpr_cv_broadcast(&q->non_empty);
     }
     q->elem[(q->head + q->length) % N] = x;
     q->length++;
     gpr_mu_unlock(&q->mu);
   }

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

   int queue_remove(queue *q, int *head, gpr_timespec abs_deadline) {
     int result = 0;
     gpr_mu_lock(&q->mu);

     while (q->length == 0 &&
            !gpr_cv_wait(&q->non_empty, &q->mu, abs_deadline)) {
     }
     if (q->length != 0) {
       result = 1;
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
