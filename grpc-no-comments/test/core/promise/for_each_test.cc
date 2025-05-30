// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/for_each.h"

#include <grpc/event_engine/memory_allocator.h>

#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/inter_activity_pipe.h"
#include "src/core/lib/promise/join.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/promise/test_wakeup_schedulers.h"

using testing::Mock;
using testing::MockFunction;
using testing::StrictMock;

namespace grpc_core {

TEST(ForEachTest, SendThriceWithPipe) {
  int num_received = 0;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&num_received] {
        Pipe<int> pipe;
        auto sender = std::make_shared<std::unique_ptr<PipeSender<int>>>(
            std::make_unique<PipeSender<int>>(std::move(pipe.sender)));
        return Map(
            Join(

                Seq((*sender)->Push(1), [sender] { return (*sender)->Push(2); },
                    [sender] { return (*sender)->Push(3); },
                    [sender] {
                      sender->reset();
                      return absl::OkStatus();
                    }),

                ForEach(std::move(pipe.receiver),
                        [&num_received](int i) {
                          num_received++;
                          EXPECT_EQ(num_received, i);
                          return absl::OkStatus();
                        })),
            JustElem<1>());
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); },
      SimpleArenaAllocator()->MakeArena());
  Mock::VerifyAndClearExpectations(&on_done);
  EXPECT_EQ(num_received, 3);
}

TEST(ForEachTest, SendThriceWithInterActivityPipe) {
  int num_received = 0;
  StrictMock<MockFunction<void(absl::Status)>> on_done_sender;
  StrictMock<MockFunction<void(absl::Status)>> on_done_receiver;
  EXPECT_CALL(on_done_sender, Call(absl::OkStatus()));
  EXPECT_CALL(on_done_receiver, Call(absl::OkStatus()));
  InterActivityPipe<int, 1> pipe;
  auto send_activity = MakeActivity(
      Seq(

          pipe.sender.Push(1), [&pipe] { return pipe.sender.Push(2); },
          [&pipe] { return pipe.sender.Push(3); },
          [&pipe] {
            auto x = std::move(pipe.sender);
            return absl::OkStatus();
          }),
      InlineWakeupScheduler{}, [&on_done_sender](absl::Status status) {
        on_done_sender.Call(std::move(status));
      });
  MakeActivity(
      [&num_received, &pipe] {

        return ForEach(std::move(pipe.receiver), [&num_received](int i) {
          num_received++;
          EXPECT_EQ(num_received, i);
          return absl::OkStatus();
        });
      },
      NoWakeupScheduler(),
      [&on_done_receiver](absl::Status status) {
        on_done_receiver.Call(std::move(status));
      });
  Mock::VerifyAndClearExpectations(&on_done_sender);
  Mock::VerifyAndClearExpectations(&on_done_receiver);
  EXPECT_EQ(num_received, 3);
}

class MoveableUntilPolled {
 public:
  MoveableUntilPolled() = default;
  MoveableUntilPolled(const MoveableUntilPolled&) = delete;
  MoveableUntilPolled& operator=(const MoveableUntilPolled&) = delete;
  MoveableUntilPolled(MoveableUntilPolled&& other) noexcept : polls_(0) {
    EXPECT_EQ(other.polls_, 0);
  }
  MoveableUntilPolled& operator=(MoveableUntilPolled&& other) noexcept {
    EXPECT_EQ(other.polls_, 0);
    polls_ = 0;
    return *this;
  }

  Poll<absl::Status> operator()() {
    GetContext<Activity>()->ForceImmediateRepoll();
    ++polls_;
    if (polls_ == 10) return absl::OkStatus();
    return Pending();
  }

 private:
  int polls_ = 0;
};

TEST(ForEachTest, NoMoveAfterPoll) {
  int num_received = 0;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&num_received] {
        Pipe<int> pipe;
        auto sender = std::make_shared<std::unique_ptr<PipeSender<int>>>(
            std::make_unique<PipeSender<int>>(std::move(pipe.sender)));
        return Map(
            Join(

                Seq((*sender)->Push(1),
                    [sender] {
                      sender->reset();
                      return absl::OkStatus();
                    }),

                ForEach(std::move(pipe.receiver),
                        [&num_received](int i) {
                          num_received++;
                          EXPECT_EQ(num_received, i);
                          return MoveableUntilPolled();
                        })),
            JustElem<1>());
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); },
      SimpleArenaAllocator()->MakeArena());
  Mock::VerifyAndClearExpectations(&on_done);
  EXPECT_EQ(num_received, 1);
}

TEST(ForEachTest, NextResultHeldThroughCallback) {
  int num_received = 0;
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  MakeActivity(
      [&num_received] {
        Pipe<int> pipe;
        auto sender = std::make_shared<std::unique_ptr<PipeSender<int>>>(
            std::make_unique<PipeSender<int>>(std::move(pipe.sender)));
        return Map(
            Join(

                Seq((*sender)->Push(1),
                    [sender] {
                      sender->reset();
                      return absl::OkStatus();
                    }),

                ForEach(std::move(pipe.receiver),
                        [&num_received, sender](int i) {

                          EXPECT_TRUE((*sender)->Push(2)().pending());
                          num_received++;
                          EXPECT_EQ(num_received, i);
                          return TrySeq(

                              MoveableUntilPolled(), [sender] {

                                EXPECT_TRUE((*sender)->Push(2)().pending());
                                return absl::OkStatus();
                              });
                        })),
            JustElem<1>());
      },
      NoWakeupScheduler(),
      [&on_done](absl::Status status) { on_done.Call(std::move(status)); },
      SimpleArenaAllocator()->MakeArena());
  Mock::VerifyAndClearExpectations(&on_done);
  EXPECT_EQ(num_received, 1);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
