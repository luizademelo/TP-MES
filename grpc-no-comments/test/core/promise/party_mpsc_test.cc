// Copyright 2025 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <stdio.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/mpsc.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

class PartyMpscTest : public ::testing::Test {
 protected:
  RefCountedPtr<Party> MakeParty() {
    auto arena = SimpleArenaAllocator()->MakeArena();
    arena->SetContext<grpc_event_engine::experimental::EventEngine>(
        event_engine_.get());
    return Party::Make(std::move(arena));
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_ =
      grpc_event_engine::experimental::GetDefaultEventEngine();
};

struct Payload {
  std::unique_ptr<int> x;
  bool operator==(const Payload& other) const {
    return (x == nullptr && other.x == nullptr) ||
           (x != nullptr && other.x != nullptr && *x == *other.x);
  }
  bool operator!=(const Payload& other) const { return !(*this == other); }
  explicit Payload(std::unique_ptr<int> x) : x(std::move(x)) {}
  Payload(const Payload& other)
      : x(other.x ? std::make_unique<int>(*other.x) : nullptr) {}

  friend std::ostream& operator<<(std::ostream& os, const Payload& payload) {
    if (payload.x == nullptr) return os << "Payload{nullptr}";
    return os << "Payload{" << *payload.x << "}";
  }
};

Payload MakePayload(int value) { return Payload{std::make_unique<int>(value)}; }

auto OnCompleteNoop() {
  return [](Empty) {};
}

constexpr int kMpscNumPayloads = 20;
constexpr int kMpscNumThreads = 8;

TEST_F(PartyMpscTest, MpscManySendersManyPartyIntegrationStressTest) {

  std::vector<std::string> execution_order(kMpscNumThreads);
  MpscReceiver<Payload> receiver((kMpscNumThreads - 1) * kMpscNumPayloads);
  std::vector<MpscSender<Payload>> senders;
  std::vector<RefCountedPtr<Party>> parties;
  for (int i = 0; i < kMpscNumThreads; i++) {
    if (i < kMpscNumThreads - 1) {
      senders.emplace_back(receiver.MakeSender());
    }
    parties.emplace_back(MakeParty());
  }
  std::vector<std::thread> threads;
  threads.reserve(kMpscNumThreads);

  for (int i = 0; i < kMpscNumThreads - 1; i++) {
    MpscSender<Payload>& sender = senders[i];
    std::string& order = execution_order[i];
    RefCountedPtr<Party>& party = parties[i];
    threads.emplace_back([&order, &party, &sender]() {
      for (int j = 0; j < kMpscNumPayloads; j++) {
        party->Spawn(
            "send",
            [&sender, &order, value = j]() {
              auto send_promise = sender.Send(MakePayload(value));
              Poll<StatusFlag> send_result = send_promise();
              absl::StrAppend(&order, "S", value);
            },
            OnCompleteNoop());
      }
    });
  }

  int num_messages_sent = (kMpscNumThreads - 1) * kMpscNumPayloads;
  std::string& receive_order = execution_order[kMpscNumThreads - 1];
  RefCountedPtr<Party>& receive_party = parties[kMpscNumThreads - 1];
  threads.emplace_back([&receive_order, &receive_party, &receiver,
                        &num_messages_sent]() {
    for (int j = 0; j < num_messages_sent; j++) {
      receive_party->Spawn(
          "receive",
          [&receiver, &receive_order]() {
            auto receive_promise = receiver.Next();
            Poll<ValueOrFailure<Payload>> receive_result = receive_promise();
            absl::StrAppend(&receive_order, "R");
          },
          OnCompleteNoop());
    }
  });

  for (auto& thread : threads) {
    thread.join();
  }

  for (int i = 0; i < kMpscNumThreads - 1; i++) {
    for (int j = 0; j < kMpscNumPayloads; j++) {

      EXPECT_TRUE(
          absl::StrContains(execution_order[i], absl::StrFormat("S%d", j)));
    }
  }

  EXPECT_EQ(receive_order.length(), num_messages_sent);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int r = RUN_ALL_TESTS();
  grpc_shutdown();
  return r;
}
