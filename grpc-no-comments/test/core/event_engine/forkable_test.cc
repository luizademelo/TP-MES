// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/forkable.h"

#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_SUBPROCESS
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#include <memory>
#include <optional>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/util/no_destruct.h"

namespace {
using ::grpc_event_engine::experimental::Forkable;
using ::grpc_event_engine::experimental::ObjectGroupForkHandler;

grpc_core::NoDestruct<ObjectGroupForkHandler> g_forkable_manager;

class ForkCallbackMethods {
 public:
  static void Prefork() { g_forkable_manager->Prefork(); }
  static void PostforkParent() { g_forkable_manager->PostforkParent(); }
  static void PostforkChild() { g_forkable_manager->PostforkChild(); }
};
}

class ForkableTest : public testing::Test {};

#ifdef GPR_POSIX_SUBPROCESS
TEST_F(ForkableTest, BasicPthreadAtForkOperations) {
  class SomeForkable : public Forkable {
   public:
    void PrepareFork() override { prepare_called_ = true; }
    void PostforkParent() override { parent_called_ = true; }
    void PostforkChild() override { child_called_ = true; }

    void CheckParent() {
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
      EXPECT_TRUE(prepare_called_);
      EXPECT_TRUE(parent_called_);
      EXPECT_FALSE(child_called_);
#else
      EXPECT_FALSE(prepare_called_);
      EXPECT_FALSE(parent_called_);
      EXPECT_FALSE(child_called_);
#endif
    }

    void CheckChild() {
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
      EXPECT_TRUE(prepare_called_);
      EXPECT_FALSE(parent_called_);
      EXPECT_TRUE(child_called_);
#else
      EXPECT_FALSE(prepare_called_);
      EXPECT_FALSE(parent_called_);
      EXPECT_FALSE(child_called_);
#endif
    }

   private:
    bool prepare_called_ = false;
    bool parent_called_ = false;
    bool child_called_ = false;
  };

  auto forkable = std::make_shared<SomeForkable>();
  g_forkable_manager->RegisterForkable(forkable, ForkCallbackMethods::Prefork,
                                       ForkCallbackMethods::PostforkParent,
                                       ForkCallbackMethods::PostforkChild);
  int child_pid = fork();
  ASSERT_NE(child_pid, -1);
  if (child_pid == 0) {
    VLOG(2) << "I am child pid: " << getpid();
    forkable->CheckChild();
    exit(testing::Test::HasFailure());
  } else {
    VLOG(2) << "I am parent pid: " << getpid();
    forkable->CheckParent();
    int status;
    VLOG(2) << "Waiting for child pid: " << child_pid;
    do {

      if (waitpid(child_pid, &status, 0) != -1) break;
      ASSERT_EQ(errno, EINTR);
    } while (true);
    if (WIFEXITED(status)) {
      ASSERT_EQ(WEXITSTATUS(status), 0);
    } else {

      ASSERT_EQ(-99, status);
    }
  }
}
#endif

TEST_F(ForkableTest, NonPthreadManualForkOperations) {

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK

  GTEST_SKIP() << "Unnecessary test, this platform supports pthreads.";
#endif

  class SomeForkable : public Forkable {
   public:
    void PrepareFork() override { prepare_called_ = true; }
    void PostforkParent() override { parent_called_ = true; }
    void PostforkChild() override { child_called_ = true; }

    void AssertStates(bool prepare, bool parent, bool child) {
      EXPECT_EQ(prepare_called_, prepare);
      EXPECT_EQ(parent_called_, parent);
      EXPECT_EQ(child_called_, child);
    }

   private:
    bool prepare_called_ = false;
    bool parent_called_ = false;
    bool child_called_ = false;
  };

  ObjectGroupForkHandler forkable_manager;
  class NoopForkCallbackMethods {
   public:
    static void Prefork() {}
    static void PostforkParent() {}
    static void PostforkChild() {}
  };
  auto forkable = std::make_shared<SomeForkable>();
  forkable_manager.RegisterForkable(forkable, NoopForkCallbackMethods::Prefork,
                                    NoopForkCallbackMethods::PostforkParent,
                                    NoopForkCallbackMethods::PostforkChild);
  forkable->AssertStates(false, false, false);
  forkable_manager.Prefork();
  forkable->AssertStates(true, false, false);
  forkable_manager.PostforkParent();
  forkable->AssertStates(true, true, false);
  forkable_manager.Prefork();
  forkable_manager.PostforkChild();
  forkable->AssertStates(true, true, true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  grpc_core::ConfigVars::Overrides config_overrides;
  config_overrides.enable_fork_support = true;
  grpc_core::ConfigVars::SetOverrides(config_overrides);
  auto result = RUN_ALL_TESTS();
  return result;
}
