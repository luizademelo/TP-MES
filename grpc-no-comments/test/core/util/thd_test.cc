
// Copyright 2015 gRPC authors.

#include "src/core/util/thd.h"

#include <grpc/support/sync.h>
#include <grpc/support/time.h>

#include <atomic>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

#define NUM_THREADS 100

struct test {
  gpr_mu mu;
  int n;
  int is_done;
  gpr_cv done_cv;
};

static void thd_body1(void* v) {
  struct test* t = static_cast<struct test*>(v);
  gpr_mu_lock(&t->mu);
  t->n--;
  if (t->n == 0) {
    t->is_done = 1;
    gpr_cv_signal(&t->done_cv);
  }
  gpr_mu_unlock(&t->mu);
}

TEST(ThreadTest, CanCreateWaitAndJoin) {
  grpc_core::Thread thds[NUM_THREADS];
  struct test t;
  gpr_mu_init(&t.mu);
  gpr_cv_init(&t.done_cv);
  t.n = NUM_THREADS;
  t.is_done = 0;
  for (auto& th : thds) {
    th = grpc_core::Thread("grpc_thread_body1_test", &thd_body1, &t);
    th.Start();
  }
  gpr_mu_lock(&t.mu);
  while (!t.is_done) {
    gpr_cv_wait(&t.done_cv, &t.mu, gpr_inf_future(GPR_CLOCK_REALTIME));
  }
  gpr_mu_unlock(&t.mu);
  for (auto& th : thds) {
    th.Join();
  }
  ASSERT_EQ(t.n, 0);
  gpr_mu_destroy(&t.mu);
  gpr_cv_destroy(&t.done_cv);
}

static void thd_body2(void* ) {}

TEST(ThreadTest, CanCreateSomeAndJoinThem) {
  grpc_core::Thread thds[NUM_THREADS];
  for (auto& th : thds) {
    bool ok;
    th = grpc_core::Thread("grpc_thread_body2_test", &thd_body2, nullptr, &ok);
    ASSERT_TRUE(ok);
    th.Start();
  }
  for (auto& th : thds) {
    th.Join();
  }
}

TEST(ThreadTest, CanCreateWithAnyInvocable) {
  grpc_core::Thread thds[NUM_THREADS];
  std::atomic<int> count_run{0};
  for (auto& th : thds) {
    bool ok;
    th = grpc_core::Thread(
        "grpc_thread_body2_test",
        [&count_run]() { count_run.fetch_add(1, std::memory_order_relaxed); },
        &ok);
    ASSERT_TRUE(ok);
    th.Start();
  }
  for (auto& th : thds) {
    th.Join();
  }
  EXPECT_EQ(count_run.load(std::memory_order_relaxed), NUM_THREADS);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
