// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/poll.h"

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {

static_assert(sizeof(Poll<Empty>) == sizeof(bool),
              "Poll<Empty> should be just a bool");

TEST(PollTest, IsItPoll) {
  EXPECT_EQ(PollTraits<Poll<int>>::is_poll(), true);
  EXPECT_EQ(PollTraits<Poll<bool>>::is_poll(), true);
  EXPECT_EQ(PollTraits<Poll<Empty>>::is_poll(), true);
  EXPECT_EQ(PollTraits<Poll<std::unique_ptr<int>>>::is_poll(), true);
  EXPECT_EQ(PollTraits<int>::is_poll(), false);
  EXPECT_EQ(PollTraits<bool>::is_poll(), false);
  EXPECT_EQ(PollTraits<Empty>::is_poll(), false);
  EXPECT_EQ(PollTraits<std::unique_ptr<int>>::is_poll(), false);
}

TEST(PollTest, Pending) {
  Poll<int> i = Pending();
  EXPECT_TRUE(i.pending());
  Poll<Empty> j = Pending();
  EXPECT_TRUE(j.pending());
}

TEST(PollTest, Ready) {
  Poll<int> i = 1;
  EXPECT_TRUE(i.ready());
  EXPECT_EQ(i.value(), 1);
  Poll<Empty> j = Empty();
  EXPECT_TRUE(j.ready());
}

TEST(PollTest, CanMove) {
  Poll<std::shared_ptr<int>> x = std::make_shared<int>(3);
  Poll<std::shared_ptr<int>> y = std::make_shared<int>(4);
  y = std::move(x);
  Poll<std::shared_ptr<int>> z = std::move(y);
  EXPECT_EQ(*z.value(), 3);
}

TEST(PollTest, ImplicitConstructor) {
  Poll<std::shared_ptr<int>> x(std::make_unique<int>(3));
  EXPECT_EQ(*x.value(), 3);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
