// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/detail/promise_factory.h"

#include "absl/functional/bind_front.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/poll.h"

namespace grpc_core {
namespace promise_detail {
namespace testing {

template <typename Arg, typename F>
auto MakeOnceFactory(F f) {
  return OncePromiseFactory<Arg, F>(std::move(f));
}
template <typename Arg, typename F>
auto MakeRepeatedFactory(F f) {
  return RepeatedPromiseFactory<Arg, F>(std::move(f));
}

TEST(AdaptorTest, FactoryFromPromise) {
  EXPECT_EQ(
      MakeOnceFactory<void>([]() { return Poll<int>(Poll<int>(42)); }).Make()(),
      Poll<int>(42));
  EXPECT_EQ(
      MakeOnceFactory<void>([]() { return Poll<int>(Poll<int>(42)); }).Make()(),
      Poll<int>(42));
  EXPECT_EQ(
      MakeOnceFactory<void>([]() { return Poll<int>(Poll<int>(42)); }).Make()(),
      Poll<int>(42));
  EXPECT_EQ(
      MakeOnceFactory<void>([]() { return Poll<int>(Poll<int>(42)); }).Make()(),
      Poll<int>(42));
}

TEST(AdaptorTest, FactoryFromBindFrontPromise) {
  EXPECT_EQ(MakeOnceFactory<void>(
                absl::bind_front([](int i) { return Poll<int>(i); }, 42))
                .Make()(),
            Poll<int>(42));
}

}
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
