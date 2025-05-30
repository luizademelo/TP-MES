// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/periodic_update.h"

#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include <stddef.h>

#include <memory>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"

namespace grpc_core {
namespace testing {

TEST(PeriodicUpdateTest, SimpleTest) {
  std::unique_ptr<PeriodicUpdate> upd;
  Timestamp start;
  Timestamp reset_start;

  {
    ExecCtx exec_ctx;
    upd = std::make_unique<PeriodicUpdate>(Duration::Seconds(1));
    start = Timestamp::Now();
  }

  bool done = false;
  while (!done) {
    ExecCtx exec_ctx;
    upd->Tick([&](Duration elapsed) {
      reset_start = Timestamp::Now();
      EXPECT_GE(elapsed, Duration::Seconds(1));
      done = true;
    });
  }

  {
    ExecCtx exec_ctx;
    EXPECT_GE(Timestamp::Now() - start, Duration::Seconds(1));
    start = reset_start;
  }

  for (int i = 0; i < 10; i++) {
    done = false;
    while (!done) {
      ExecCtx exec_ctx;
      upd->Tick([&](Duration) {
        reset_start = Timestamp::Now();
        EXPECT_GE(Timestamp::Now() - start, Duration::Seconds(1));
        done = true;
      });
    }

    {
      ExecCtx exec_ctx;
      EXPECT_GE(Timestamp::Now() - start, Duration::Seconds(1));
      EXPECT_LE(Timestamp::Now() - start, Duration::Seconds(3));
      start = reset_start;
    }
  }
}

TEST(PeriodicUpdate, ThreadTest) {
  std::unique_ptr<PeriodicUpdate> upd;
  std::atomic<int> count(0);
  Timestamp start;

  {
    ExecCtx exec_ctx;
    upd = std::make_unique<PeriodicUpdate>(Duration::Seconds(1));
    start = Timestamp::Now();
  }

  std::vector<std::thread> threads;
  for (size_t i = 0; i < 10; i++) {
    threads.push_back(std::thread([&]() {
      while (count.load() < 10) {
        ExecCtx exec_ctx;
        upd->Tick([&](Duration d) {
          EXPECT_GE(d, Duration::Seconds(1));
          count.fetch_add(1);
        });
      }
    }));
  }

  for (auto& th : threads) {
    th.join();
  }

  {
    ExecCtx exec_ctx;
    EXPECT_GE(Timestamp::Now() - start, Duration::Seconds(10));
    EXPECT_LE(Timestamp::Now() - start, Duration::Seconds(30));
  }
}

}
}

void grpc_set_default_iomgr_platform() {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  gpr_log_verbosity_init();
  gpr_time_init();
  return RUN_ALL_TESTS();
}
