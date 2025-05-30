
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <spawn.h>

#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "test/core/test_util/test_config.h"

extern char** environ;

#ifdef GPR_ANDROID

void run_cmd(const char* cmd) { std::system(cmd); }
#else
void run_cmd(const char* cmd) {
  pid_t pid;
  const char* argv[] = {const_cast<const char*>("sh"),
                        const_cast<const char*>("-c"), cmd, nullptr};
  int status;

  status = posix_spawn(&pid, const_cast<const char*>("/bin/sh"), nullptr,
                       nullptr, const_cast<char**>(argv), environ);
  if (status == 0) {
    if (waitpid(pid, &status, 0) == -1) {
      perror("waitpid");
    }
  }
}
#endif

class TimeJumpTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override {

    if (grpc_test_slowdown_factor() != 1) {
      GTEST_SKIP();
    } else {
      grpc_init();
    }
  }
  void TearDown() override {

    if (grpc_test_slowdown_factor() == 1) {
      run_cmd("sudo sntp -sS pool.ntp.org");
      grpc_shutdown();
    }
  }

  const int kWaitTimeMs = 1500;
};

std::vector<std::string> CreateTestScenarios() {
  return {"-1M", "+1M", "-1H", "+1H", "-1d", "+1d", "-1y", "+1y"};
}
INSTANTIATE_TEST_SUITE_P(TimeJump, TimeJumpTest,
                         ::testing::ValuesIn(CreateTestScenarios()));

TEST_P(TimeJumpTest, TimerRunning) {
  grpc_core::ExecCtx exec_ctx;
  grpc_timer timer;
  grpc_timer_init(&timer,
                  grpc_core::Timestamp::Now() + grpc_core::Duration::Seconds(3),
                  GRPC_CLOSURE_CREATE(
                      [](void*, grpc_error_handle error) {
                        CHECK(error == absl::CancelledError());
                      },
                      nullptr, grpc_schedule_on_exec_ctx));
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(100));
  std::ostringstream cmd;
  cmd << "sudo date `date -v" << GetParam() << " \"+%m%d%H%M%y\"`";
  run_cmd(cmd.str().c_str());
  gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(kWaitTimeMs));

  int64_t wakeups = grpc_timer_manager_get_wakeups_testonly();
  VLOG(2) << "wakeups: " << wakeups;
  CHECK_LE(wakeups, 3);
  grpc_timer_cancel(&timer);
}

TEST_P(TimeJumpTest, TimedWait) {
  grpc_core::CondVar cond;
  grpc_core::Mutex mu;
  {
    grpc_core::MutexLock lock(&mu);
    std::thread thd = std::thread([]() {
      gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(100));
      std::ostringstream cmd;
      cmd << "sudo date `date -v" << GetParam() << " \"+%m%d%H%M%y\"`";
      run_cmd(cmd.str().c_str());
    });
    gpr_timespec before = gpr_now(GPR_CLOCK_MONOTONIC);
    bool timedout = cond.WaitWithTimeout(&mu, absl::Milliseconds(kWaitTimeMs));
    gpr_timespec after = gpr_now(GPR_CLOCK_MONOTONIC);
    int32_t elapsed_ms = gpr_time_to_millis(gpr_time_sub(after, before));
    VLOG(2) << "After wait, timedout = " << timedout
            << " elapsed_ms = " << elapsed_ms;
    CHECK_EQ(timedout, 1);
    CHECK(1 == gpr_time_similar(gpr_time_sub(after, before),
                                gpr_time_from_millis(kWaitTimeMs, GPR_TIMESPAN),
                                gpr_time_from_millis(50, GPR_TIMESPAN)));

    thd.join();
  }

  int64_t wakeups = grpc_timer_manager_get_wakeups_testonly();
  VLOG(2) << "wakeups: " << wakeups;
  CHECK_LE(wakeups, 3);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
