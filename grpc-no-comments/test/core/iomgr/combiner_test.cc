
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/combiner.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>

#include <thread>

#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "src/core/util/notification.h"
#include "src/core/util/thd.h"
#include "src/core/util/useful.h"
#include "test/core/test_util/test_config.h"

TEST(CombinerTest, TestNoOp) {
  grpc_core::ExecCtx exec_ctx;
  GRPC_COMBINER_UNREF(grpc_combiner_create(
                          grpc_event_engine::experimental::CreateEventEngine()),
                      "test_no_op");
}

static void set_event_to_true(void* value, grpc_error_handle ) {
  gpr_event_set(static_cast<gpr_event*>(value), reinterpret_cast<void*>(1));
}

TEST(CombinerTest, TestExecuteOne) {
  grpc_core::Combiner* lock = grpc_combiner_create(
      grpc_event_engine::experimental::CreateEventEngine());
  gpr_event done;
  gpr_event_init(&done);
  grpc_core::ExecCtx exec_ctx;
  lock->Run(GRPC_CLOSURE_CREATE(set_event_to_true, &done, nullptr),
            absl::OkStatus());
  grpc_core::ExecCtx::Get()->Flush();
  ASSERT_NE(gpr_event_wait(&done, grpc_timeout_seconds_to_deadline(5)),
            nullptr);
  GRPC_COMBINER_UNREF(lock, "test_execute_one");
}

typedef struct {
  size_t ctr;
  grpc_core::Combiner* lock;
  gpr_event done;
} thd_args;

typedef struct {
  size_t* ctr;
  size_t value;
} ex_args;

static void check_one(void* a, grpc_error_handle ) {
  ex_args* args = static_cast<ex_args*>(a);
  ASSERT_EQ(*args->ctr, args->value - 1);
  *args->ctr = args->value;
  gpr_free(a);
}

static void execute_many_loop(void* a) {
  thd_args* args = static_cast<thd_args*>(a);
  grpc_core::ExecCtx exec_ctx;
  size_t n = 1;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10000; j++) {
      ex_args* c = static_cast<ex_args*>(gpr_malloc(sizeof(*c)));
      c->ctr = &args->ctr;
      c->value = n++;
      args->lock->Run(GRPC_CLOSURE_CREATE(check_one, c, nullptr),
                      absl::OkStatus());
      grpc_core::ExecCtx::Get()->Flush();
    }

    gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(100));
  }
  args->lock->Run(GRPC_CLOSURE_CREATE(set_event_to_true, &args->done, nullptr),
                  absl::OkStatus());
}

TEST(CombinerTest, TestExecuteMany) {
  grpc_core::Combiner* lock = grpc_combiner_create(
      grpc_event_engine::experimental::CreateEventEngine());
  grpc_core::Thread thds[10];
  thd_args ta[GPR_ARRAY_SIZE(thds)];
  for (size_t i = 0; i < GPR_ARRAY_SIZE(thds); i++) {
    ta[i].ctr = 0;
    ta[i].lock = lock;
    gpr_event_init(&ta[i].done);
    thds[i] = grpc_core::Thread("grpc_execute_many", execute_many_loop, &ta[i]);
    thds[i].Start();
  }
  for (size_t i = 0; i < GPR_ARRAY_SIZE(thds); i++) {
    ASSERT_NE(gpr_event_wait(&ta[i].done, gpr_inf_future(GPR_CLOCK_REALTIME)),
              nullptr);
    thds[i].Join();
  }
  grpc_core::ExecCtx exec_ctx;
  GRPC_COMBINER_UNREF(lock, "test_execute_many");
}

static gpr_event got_in_finally;

static void in_finally(void* , grpc_error_handle ) {
  gpr_event_set(&got_in_finally, reinterpret_cast<void*>(1));
}

static void add_finally(void* arg, grpc_error_handle ) {
  static_cast<grpc_core::Combiner*>(arg)->FinallyRun(
      GRPC_CLOSURE_CREATE(in_finally, arg, nullptr), absl::OkStatus());
}

TEST(CombinerTest, TestExecuteFinally) {
  grpc_core::Combiner* lock = grpc_combiner_create(
      grpc_event_engine::experimental::CreateEventEngine());
  grpc_core::ExecCtx exec_ctx;
  gpr_event_init(&got_in_finally);
  lock->Run(GRPC_CLOSURE_CREATE(add_finally, lock, nullptr), absl::OkStatus());
  grpc_core::ExecCtx::Get()->Flush();
  ASSERT_NE(
      gpr_event_wait(&got_in_finally, grpc_timeout_seconds_to_deadline(5)),
      nullptr);
  GRPC_COMBINER_UNREF(lock, "test_execute_finally");
}

TEST(CombinerTest, TestForceOffload) {
  grpc_core::Combiner* lock = grpc_combiner_create(
      grpc_event_engine::experimental::CreateEventEngine());
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Notification done;
  const auto start_thread = std::this_thread::get_id();
  lock->Run(grpc_core::NewClosure([&](grpc_error_handle) {

              EXPECT_EQ(start_thread, std::this_thread::get_id());
              lock->Run(grpc_core::NewClosure([&](grpc_error_handle) {

                          EXPECT_EQ(start_thread, std::this_thread::get_id());

                          lock->ForceOffload();
                          lock->Run(
                              grpc_core::NewClosure([&](grpc_error_handle) {

                                EXPECT_NE(start_thread,
                                          std::this_thread::get_id());
                                done.Notify();
                              }),
                              absl::OkStatus());
                        }),
                        absl::OkStatus());
            }),
            absl::OkStatus());
  exec_ctx.Flush();
  done.WaitForNotification();
  GRPC_COMBINER_UNREF(lock, "test_force_offload");
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
