
// Copyright 2015 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <stdio.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/thd.h"
#include "test/core/test_util/test_config.h"

#define N 4

typedef struct queue {
  gpr_cv non_empty;
  gpr_cv non_full;
  gpr_mu mu;

  int head;
  int length;
  int elem[N];
} queue;

void queue_init(queue* q) {
  gpr_mu_init(&q->mu);
  gpr_cv_init(&q->non_empty);
  gpr_cv_init(&q->non_full);
  q->head = 0;
  q->length = 0;
}

void queue_destroy(queue* q) {
  gpr_mu_destroy(&q->mu);
  gpr_cv_destroy(&q->non_empty);
  gpr_cv_destroy(&q->non_full);
}

void queue_append(queue* q, int x) {
  gpr_mu_lock(&q->mu);

  while (q->length == N) {
    gpr_cv_wait(&q->non_full, &q->mu, gpr_inf_future(GPR_CLOCK_MONOTONIC));
  }
  if (q->length == 0) {

    gpr_cv_broadcast(&q->non_empty);
  }
  q->elem[(q->head + q->length) % N] = x;
  q->length++;
  gpr_mu_unlock(&q->mu);
}

int queue_try_append(queue* q, int x) {
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

int queue_remove(queue* q, int* head, gpr_timespec abs_deadline) {
  int result = 0;
  gpr_mu_lock(&q->mu);

  while (q->length == 0 && !gpr_cv_wait(&q->non_empty, &q->mu, abs_deadline)) {
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

struct test {
  int nthreads;
  grpc_core::Thread* threads;

  int64_t iterations;
  int64_t counter;
  int thread_count;
  int done;
  int incr_step;

  gpr_mu mu;

  gpr_cv cv;

  gpr_cv done_cv;

  queue q;

  gpr_stats_counter stats_counter;

  gpr_refcount refcount;
  gpr_refcount thread_refcount;
  gpr_event event;
};

static struct test* test_new(int nthreads, int64_t iterations, int incr_step) {
  struct test* m = static_cast<struct test*>(gpr_malloc(sizeof(*m)));
  m->nthreads = nthreads;
  m->threads = static_cast<grpc_core::Thread*>(
      gpr_malloc(sizeof(*m->threads) * nthreads));
  m->iterations = iterations;
  m->counter = 0;
  m->thread_count = 0;
  m->done = nthreads;
  m->incr_step = incr_step;
  gpr_mu_init(&m->mu);
  gpr_cv_init(&m->cv);
  gpr_cv_init(&m->done_cv);
  queue_init(&m->q);
  gpr_stats_init(&m->stats_counter, 0);
  gpr_ref_init(&m->refcount, 0);
  gpr_ref_init(&m->thread_refcount, nthreads);
  gpr_event_init(&m->event);
  return m;
}

static void test_destroy(struct test* m) {
  gpr_mu_destroy(&m->mu);
  gpr_cv_destroy(&m->cv);
  gpr_cv_destroy(&m->done_cv);
  queue_destroy(&m->q);
  gpr_free(m->threads);
  gpr_free(m);
}

static void test_create_threads(struct test* m, void (*body)(void* arg)) {
  int i;
  for (i = 0; i != m->nthreads; i++) {
    m->threads[i] = grpc_core::Thread("grpc_create_threads", body, m);
    m->threads[i].Start();
  }
}

static void test_wait(struct test* m) {
  gpr_mu_lock(&m->mu);
  while (m->done != 0) {
    gpr_cv_wait(&m->done_cv, &m->mu, gpr_inf_future(GPR_CLOCK_MONOTONIC));
  }
  gpr_mu_unlock(&m->mu);
  for (int i = 0; i != m->nthreads; i++) {
    m->threads[i].Join();
  }
}

static int thread_id(struct test* m) {
  int id;
  gpr_mu_lock(&m->mu);
  id = m->thread_count++;
  gpr_mu_unlock(&m->mu);
  return id;
}

static void mark_thread_done(struct test* m) {
  gpr_mu_lock(&m->mu);
  ASSERT_NE(m->done, 0);
  m->done--;
  if (m->done == 0) {
    gpr_cv_signal(&m->done_cv);
  }
  gpr_mu_unlock(&m->mu);
}

static void test(const char* name, void (*body)(void* m),
                 void (*extra)(void* m), int timeout_s, int incr_step) {
  int64_t iterations = 8;
  struct test* m;
  gpr_timespec start = gpr_now(GPR_CLOCK_REALTIME);
  gpr_timespec time_taken;
  gpr_timespec deadline = gpr_time_add(
      start, gpr_time_from_micros(static_cast<int64_t>(timeout_s) * 1000000,
                                  GPR_TIMESPAN));
  fprintf(stderr, "%s-", name);
  fflush(stderr);
  while (gpr_time_cmp(gpr_now(GPR_CLOCK_REALTIME), deadline) < 0) {
    fprintf(stderr, " %ld", static_cast<long>(iterations));
    fflush(stderr);
    m = test_new(10, iterations, incr_step);
    grpc_core::Thread extra_thd;
    if (extra != nullptr) {
      extra_thd = grpc_core::Thread(name, extra, m);
      extra_thd.Start();
      m->done++;
    }
    test_create_threads(m, body);
    test_wait(m);
    if (extra != nullptr) {
      extra_thd.Join();
    }
    if (m->counter != m->nthreads * m->iterations * m->incr_step) {
      fprintf(stderr, "counter %ld  threads %d  iterations %ld\n",
              static_cast<long>(m->counter), m->nthreads,
              static_cast<long>(m->iterations));
      fflush(stderr);
      ASSERT_TRUE(0);
    }
    test_destroy(m);
    iterations <<= 1;
  }
  time_taken = gpr_time_sub(gpr_now(GPR_CLOCK_REALTIME), start);
  fprintf(stderr, " done %lld.%09d s\n",
          static_cast<long long>(time_taken.tv_sec),
          static_cast<int>(time_taken.tv_nsec));
  fflush(stderr);
}

static void inc(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations; i++) {
    gpr_mu_lock(&m->mu);
    m->counter++;
    gpr_mu_unlock(&m->mu);
  }
  mark_thread_done(m);
}

static void inctry(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations;) {
    if (gpr_mu_trylock(&m->mu)) {
      m->counter++;
      gpr_mu_unlock(&m->mu);
      i++;
    }
  }
  mark_thread_done(m);
}

static void inc_by_turns(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  int id = thread_id(m);
  for (i = 0; i != m->iterations; i++) {
    gpr_mu_lock(&m->mu);
    while ((m->counter % m->nthreads) != id) {
      gpr_cv_wait(&m->cv, &m->mu, gpr_inf_future(GPR_CLOCK_MONOTONIC));
    }
    m->counter++;
    gpr_cv_broadcast(&m->cv);
    gpr_mu_unlock(&m->mu);
  }
  mark_thread_done(m);
}

static void inc_with_1ms_delay(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations; i++) {
    gpr_timespec deadline;
    gpr_mu_lock(&m->mu);
    deadline = gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                            gpr_time_from_micros(1000, GPR_TIMESPAN));
    while (!gpr_cv_wait(&m->cv, &m->mu, deadline)) {
    }
    m->counter++;
    gpr_mu_unlock(&m->mu);
  }
  mark_thread_done(m);
}

static void inc_with_1ms_delay_event(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations; i++) {
    gpr_timespec deadline;
    deadline = gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                            gpr_time_from_micros(1000, GPR_TIMESPAN));
    ASSERT_EQ(gpr_event_wait(&m->event, deadline), nullptr);
    gpr_mu_lock(&m->mu);
    m->counter++;
    gpr_mu_unlock(&m->mu);
  }
  mark_thread_done(m);
}

static void many_producers(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  int x = thread_id(m);
  if ((x & 1) == 0) {
    for (i = 0; i != m->iterations; i++) {
      queue_append(&m->q, 1);
    }
  } else {
    for (i = 0; i != m->iterations; i++) {
      while (!queue_try_append(&m->q, 1)) {
      }
    }
  }
  mark_thread_done(m);
}

static void consumer(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t n = m->iterations * m->nthreads;
  int64_t i;
  int value;
  for (i = 0; i != n; i++) {
    queue_remove(&m->q, &value, gpr_inf_future(GPR_CLOCK_MONOTONIC));
  }
  gpr_mu_lock(&m->mu);
  m->counter = n;
  gpr_mu_unlock(&m->mu);
  ASSERT_TRUE(
      !queue_remove(&m->q, &value,
                    gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                                 gpr_time_from_micros(1000000, GPR_TIMESPAN))));
  mark_thread_done(m);
}

static void statsinc(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations; i++) {
    gpr_stats_inc(&m->stats_counter, 1);
  }
  gpr_mu_lock(&m->mu);
  m->counter = gpr_stats_read(&m->stats_counter);
  gpr_mu_unlock(&m->mu);
  mark_thread_done(m);
}

static void refinc(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations; i++) {
    if (m->incr_step == 1) {
      gpr_ref(&m->refcount);
    } else {
      gpr_refn(&m->refcount, m->incr_step);
    }
  }
  if (gpr_unref(&m->thread_refcount)) {
    gpr_event_set(&m->event, reinterpret_cast<void*>(1));
  }
  mark_thread_done(m);
}

static void refcheck(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t n = m->iterations * m->nthreads * m->incr_step;
  int64_t i;
  ASSERT_EQ(gpr_event_wait(&m->event, gpr_inf_future(GPR_CLOCK_REALTIME)),
            (void*)1);
  ASSERT_EQ(gpr_event_get(&m->event), (void*)1);
  for (i = 1; i != n; i++) {
    ASSERT_FALSE(gpr_unref(&m->refcount));
    m->counter++;
  }
  ASSERT_TRUE(gpr_unref(&m->refcount));
  m->counter++;
  mark_thread_done(m);
}

TEST(SyncTest, MainTest) {
  test("mutex", &inc, nullptr, 1, 1);
  test("mutex try", &inctry, nullptr, 1, 1);
  test("cv", &inc_by_turns, nullptr, 1, 1);
  test("timedcv", &inc_with_1ms_delay, nullptr, 1, 1);
  test("queue", &many_producers, &consumer, 10, 1);
  test("stats_counter", &statsinc, nullptr, 1, 1);
  test("refcount-by-1", &refinc, &refcheck, 1, 1);
  test("refcount-by-3", &refinc, &refcheck, 1, 3);

  test("timedevent", &inc_with_1ms_delay_event, nullptr, 1, 1);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
