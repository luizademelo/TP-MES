
// Copyright 2017 gRPC authors.

#include "src/core/util/spinlock.h"

#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <stdio.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/thd.h"
#include "test/core/test_util/test_config.h"

struct test {
  int thread_count;
  grpc_core::Thread* threads;

  int64_t iterations;
  int64_t counter;
  int incr_step;

  gpr_spinlock mu;
};

static struct test* test_new(int threads, int64_t iterations, int incr_step) {
  struct test* m = static_cast<struct test*>(gpr_malloc(sizeof(*m)));
  m->thread_count = threads;
  m->threads = static_cast<grpc_core::Thread*>(
      gpr_malloc(sizeof(*m->threads) * static_cast<size_t>(threads)));
  m->iterations = iterations;
  m->counter = 0;
  m->thread_count = 0;
  m->incr_step = incr_step;
  m->mu = GPR_SPINLOCK_INITIALIZER;
  return m;
}

static void test_destroy(struct test* m) {
  gpr_free(m->threads);
  gpr_free(m);
}

static void test_create_threads(struct test* m, void (*body)(void* arg)) {
  int i;
  for (i = 0; i != m->thread_count; i++) {
    m->threads[i] = grpc_core::Thread("grpc_create_threads", body, m);
    m->threads[i].Start();
  }
}

static void test_wait(struct test* m) {
  int i;
  for (i = 0; i != m->thread_count; i++) {
    m->threads[i].Join();
  }
}

static void test(void (*body)(void* m), int timeout_s, int incr_step) {
  int64_t iterations = 1024;
  struct test* m;
  gpr_timespec start = gpr_now(GPR_CLOCK_REALTIME);
  gpr_timespec time_taken;
  gpr_timespec deadline = gpr_time_add(
      start, gpr_time_from_micros(static_cast<int64_t>(timeout_s) * 1000000,
                                  GPR_TIMESPAN));
  while (gpr_time_cmp(gpr_now(GPR_CLOCK_REALTIME), deadline) < 0) {
    if (iterations < INT64_MAX / 2) iterations <<= 1;
    fprintf(stderr, " %ld", static_cast<long>(iterations));
    fflush(stderr);
    m = test_new(10, iterations, incr_step);
    test_create_threads(m, body);
    test_wait(m);
    if (m->counter != m->thread_count * m->iterations * m->incr_step) {
      fprintf(stderr, "counter %ld  threads %d  iterations %ld\n",
              static_cast<long>(m->counter), m->thread_count,
              static_cast<long>(m->iterations));
      fflush(stderr);
      FAIL();
    }
    test_destroy(m);
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
    gpr_spinlock_lock(&m->mu);
    m->counter++;
    gpr_spinlock_unlock(&m->mu);
  }
}

static void inctry(void* v ) {
  struct test* m = static_cast<struct test*>(v);
  int64_t i;
  for (i = 0; i != m->iterations;) {
    if (gpr_spinlock_trylock(&m->mu)) {
      m->counter++;
      gpr_spinlock_unlock(&m->mu);
      i++;
    }
  }
}

TEST(SpinlockTest, Spinlock) { test(&inc, 1, 1); }

TEST(SpinlockTest, SpinlockTry) { test(&inctry, 1, 1); }

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
