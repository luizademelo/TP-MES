
// Copyright 2016 gRPC authors.

#include "src/cpp/thread_manager/thread_manager.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/grpcpp.h>

#include <atomic>
#include <chrono>
#include <climits>
#include <memory>
#include <thread>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

struct TestThreadManagerSettings {

  int min_pollers;

  int max_pollers;

  int poll_duration_ms;

  int work_duration_ms;

  int max_poll_calls;

  int thread_limit;

  int thread_manager_count;
};

class TestThreadManager final : public grpc::ThreadManager {
 public:
  TestThreadManager(const char* name, grpc_resource_quota* rq,
                    const TestThreadManagerSettings& settings)
      : ThreadManager(name, rq, settings.min_pollers, settings.max_pollers),
        settings_(settings),
        num_do_work_(0),
        num_poll_for_work_(0),
        num_work_found_(0) {}

  grpc::ThreadManager::WorkStatus PollForWork(void** tag, bool* ok) override;
  void DoWork(void* , bool , bool ) override {
    num_do_work_.fetch_add(1, std::memory_order_relaxed);

    std::this_thread::sleep_for(
        std::chrono::milliseconds(settings_.work_duration_ms));
  }

  int num_poll_for_work() const {
    return num_poll_for_work_.load(std::memory_order_relaxed);
  }

  int num_work_found() const {
    return num_work_found_.load(std::memory_order_relaxed);
  }

  int num_do_work() const {
    return num_do_work_.load(std::memory_order_relaxed);
  }

 private:
  TestThreadManagerSettings settings_;

  std::atomic_int num_do_work_;
  std::atomic_int num_poll_for_work_;
  std::atomic_int num_work_found_;
};

grpc::ThreadManager::WorkStatus TestThreadManager::PollForWork(void** tag,
                                                               bool* ok) {
  int call_num = num_poll_for_work_.fetch_add(1, std::memory_order_relaxed);
  if (call_num >= settings_.max_poll_calls) {
    Shutdown();
    return SHUTDOWN;
  }

  std::this_thread::sleep_for(
      std::chrono::milliseconds(settings_.poll_duration_ms));
  *tag = nullptr;
  *ok = true;

  if (call_num % 3 == 0) {
    return TIMEOUT;
  }

  num_work_found_.fetch_add(1, std::memory_order_relaxed);
  return WORK_FOUND;
}

class ThreadManagerTest
    : public ::testing::TestWithParam<TestThreadManagerSettings> {
 protected:
  void SetUp() override {
    grpc_resource_quota* rq = grpc_resource_quota_create("Thread manager test");
    if (GetParam().thread_limit > 0) {
      grpc_resource_quota_set_max_threads(rq, GetParam().thread_limit);
    }
    for (int i = 0; i < GetParam().thread_manager_count; i++) {
      thread_manager_.emplace_back(
          new TestThreadManager("TestThreadManager", rq, GetParam()));
    }
    grpc_resource_quota_unref(rq);
    for (auto& tm : thread_manager_) {
      tm->Initialize();
    }
    for (auto& tm : thread_manager_) {
      tm->Wait();
    }
  }

  std::vector<std::unique_ptr<TestThreadManager>> thread_manager_;
};

TestThreadManagerSettings scenarios[] = {
    {2 , 10 , 10 ,
     1 , 50 ,
     INT_MAX , 1 },
    {1 , 1 , 1 ,
     10 , 50 , 3 ,
     2 }};

INSTANTIATE_TEST_SUITE_P(ThreadManagerTest, ThreadManagerTest,
                         ::testing::ValuesIn(scenarios));

TEST_P(ThreadManagerTest, TestPollAndWork) {
  for (auto& tm : thread_manager_) {

    VLOG(2) << "DoWork() called " << tm->num_do_work() << " times";
    EXPECT_GE(tm->num_poll_for_work(), GetParam().max_poll_calls);
    EXPECT_EQ(tm->num_do_work(), tm->num_work_found());
  }
}

TEST_P(ThreadManagerTest, TestThreadQuota) {
  if (GetParam().thread_limit > 0) {
    for (auto& tm : thread_manager_) {
      EXPECT_GE(tm->num_poll_for_work(), GetParam().max_poll_calls);
      EXPECT_LE(tm->GetMaxActiveThreadsSoFar(), GetParam().thread_limit);
    }
  }
}

}
}

int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  grpc_init();
  auto ret = RUN_ALL_TESTS();
  grpc_shutdown();

  return ret;
}
