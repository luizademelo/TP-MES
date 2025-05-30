// Copyright 2022 The gRPC Authors

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <deque>
#include <optional>
#include <type_traits>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/work_queue/basic_work_queue.h"
#include "test/core/event_engine/work_queue/work_queue_fuzzer.pb.h"

namespace grpc_event_engine {
namespace experimental {

class WorkQueueFuzzer {
 public:
  WorkQueueFuzzer() { CheckEqual(); }
  ~WorkQueueFuzzer() { CheckEqual(); }

  void Run(const work_queue_fuzzer::Action& action) {
    switch (action.action_type_case()) {
      case work_queue_fuzzer::Action::kAdd: {
        if (action.add().type() == work_queue_fuzzer::CALLBACK_TYPE_CLOSURE) {
          work_queue_.Add(CreateClosure(action.add().key()));
          deque_.push_back(CreateClosure(action.add().key()));
        } else {
          work_queue_.Add(CreateInvocable(action.add().key()));
          deque_.push_back(CreateClosureWrappedInvocable(action.add().key()));
        }
      } break;
      case work_queue_fuzzer::Action::kPopMostRecent: {

        auto* wq_c = work_queue_.PopMostRecent();
        if (wq_c == nullptr) {
          if (!work_queue_.Empty() || !deque_.empty()) abort();
        } else {
          auto* dq_c = deque_.front();
          deque_.pop_front();
          wq_c->Run();
          dq_c->Run();
        }
      } break;
      case work_queue_fuzzer::Action::kPopOldest: {

        auto* wq_c = work_queue_.PopOldest();
        if (wq_c == nullptr) {
          if (!work_queue_.Empty() || !deque_.empty()) abort();
        } else {
          auto* dq_c = deque_.back();
          deque_.pop_back();
          wq_c->Run();
          dq_c->Run();
        }
      } break;
      case work_queue_fuzzer::Action::kEmpty: {
        if (work_queue_.Empty() != deque_.empty()) abort();
      } break;
      case work_queue_fuzzer::Action::ACTION_TYPE_NOT_SET:
        break;
    }
  }

 private:
  EventEngine::Closure* CreateClosure(int key) {
    return SelfDeletingClosure::Create([key, this] {
      if (last_executed_key_.has_value()) {
        if (*last_executed_key_ != key) abort();
        last_executed_key_.reset();
      } else {
        last_executed_key_ = key;
      }
    });
  }

  absl::AnyInvocable<void()> CreateInvocable(int key) {
    return absl::AnyInvocable<void()>([key, this] {
      if (last_executed_key_.has_value()) {
        if (*last_executed_key_ != key) abort();
        last_executed_key_.reset();
      } else {
        last_executed_key_ = key;
      }
    });
  }

  EventEngine::Closure* CreateClosureWrappedInvocable(int key) {
    auto invocable = CreateInvocable(key);
    return SelfDeletingClosure::Create(
        [invocable = std::move(invocable)]() mutable { invocable(); });
  }

  void CheckEqual() {
    while (auto* wq_c = work_queue_.PopOldest()) {
      if (deque_.empty()) abort();
      auto* dq_c = deque_.back();
      deque_.pop_back();
      wq_c->Run();
      dq_c->Run();
    }
  }

  BasicWorkQueue work_queue_;
  std::deque<EventEngine::Closure*> deque_;

  std::optional<int> last_executed_key_;
};

void Fuzz(const work_queue_fuzzer::Msg& msg) {
  for (const auto& action : msg.actions()) {
    grpc_event_engine::experimental::WorkQueueFuzzer().Run(action);
  }
}
FUZZ_TEST(WorkQueueFuzzer, Fuzz);

}
}
