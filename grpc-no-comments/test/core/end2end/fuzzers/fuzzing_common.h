
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FUZZERS_FUZZING_COMMON_H
#define GRPC_TEST_CORE_END2END_FUZZERS_FUZZING_COMMON_H

#include <grpc/grpc.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/types/span.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "test/core/end2end/fuzzers/api_fuzzer.pb.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"

namespace grpc_core {
namespace testing {

class Validator {
 public:
  explicit Validator(std::function<void(bool)> impl) : impl_(std::move(impl)) {}

  virtual ~Validator() {}
  void Run(bool success) {
    impl_(success);
    delete this;
  }

 private:
  std::function<void(bool)> impl_;
};

inline Validator* MakeValidator(std::function<void(bool)> impl) {
  return new Validator(std::move(impl));
}

inline Validator* AssertSuccessAndDecrement(int* counter) {
  return MakeValidator([counter](bool success) {
    CHECK(success);
    --*counter;
  });
}

inline Validator* Decrement(int* counter) {
  return MakeValidator([counter](bool) { --*counter; });
}

class Call;

class BasicFuzzer {
 public:
  explicit BasicFuzzer(const fuzzing_event_engine::Actions& actions);

  enum Result { kPending = 0, kComplete = 1, kFailed = 2, kNotSupported = 3 };
  virtual Result ExecuteAction(const api_fuzzer::Action& action);
  Call* ActiveCall();

  bool Continue();
  virtual void Tick();

  void Run(absl::Span<const api_fuzzer::Action* const> actions);

 protected:
  ~BasicFuzzer();

  bool server_finished_shutting_down() {
    return server() != nullptr && server_shutdown_ &&
           pending_server_shutdowns_ == 0;
  }
  bool server_shutdown_called() { return server_shutdown_; }

  void ShutdownCalls();
  void ResetServerState() {
    server_shutdown_ = false;
    CHECK_EQ(pending_server_shutdowns_, 0);
  }

  Result PollCq();

  Result ShutdownServer();

  RefCountedPtr<ResourceQuota> resource_quota() { return resource_quota_; }

  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
  engine() {
    return engine_;
  }

  grpc_completion_queue* cq() { return cq_; }

  void UpdateMinimumRunTime(Duration minimum_run_time) {
    minimum_run_time_ = std::max(minimum_run_time, minimum_run_time_);
  }

 private:

  virtual Result CreateChannel(
      const api_fuzzer::CreateChannel& create_channel) = 0;

  Result CloseChannel();

  Result CheckConnectivity(bool try_to_connect);

  Result WatchConnectivity(uint32_t duration_us);

  Result ValidateChannelTarget();

  virtual Result CreateServer(
      const api_fuzzer::CreateServer& create_server) = 0;

  Result DestroyServerIfReady();

  Result ServerRequestCall();

  Result CancelAllCallsIfShutdown();

  Result CreateCall(const api_fuzzer::CreateCall& create_call);

  Result ChangeActiveCall();

  Result QueueBatchForActiveCall(const api_fuzzer::Batch& queue_batch);

  Result CancelActiveCall();

  Result ValidatePeerForActiveCall();

  Result DestroyActiveCall();

  Result Pause(Duration duration);

  Result ResizeResourceQuota(uint32_t resize_resource_quota);

  void TryShutdown();

  virtual grpc_server* server() = 0;
  virtual grpc_channel* channel() = 0;
  virtual void DestroyServer() = 0;
  virtual void DestroyChannel() = 0;

  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine> engine_;
  grpc_completion_queue* cq_;
  bool server_shutdown_ = false;
  int pending_server_shutdowns_ = 0;
  int pending_channel_watches_ = 0;
  int paused_ = 0;
  std::vector<std::shared_ptr<Call>> calls_;
  RefCountedPtr<ResourceQuota> resource_quota_;
  size_t active_call_ = 0;
  Duration minimum_run_time_ = Duration::Zero();
};

}
}

#endif
