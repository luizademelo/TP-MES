// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/promise.h"

#include <memory>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/json/json_writer.h"

namespace grpc_core {

TEST(PromiseTest, Works) {
  Promise<int> x = []() { return 42; };
  EXPECT_EQ(x(), Poll<int>(42));
}

TEST(PromiseTest, Immediate) { EXPECT_EQ(Immediate(42)(), Poll<int>(42)); }

TEST(PromiseTest, AssertResultType) {
  EXPECT_EQ(AssertResultType<int>(Immediate(42))(), Poll<int>(42));

}

TEST(PromiseTest, NowOrNever) {
  EXPECT_EQ(NowOrNever(Immediate(42)), std::optional<int>(42));
}

TEST(PromiseTest, CanConvertToJson) {
  auto x = []() { return 42; };
  EXPECT_FALSE(promise_detail::kHasToJsonMethod<decltype(x)>);
}

TEST(PromiseTest, CanCustomizeJsonConversion) {
  class FooPromise {
   public:
    Json ToJson() const { return Json::FromObject(Json::Object()); }
  };
  EXPECT_TRUE(promise_detail::kHasToJsonMethod<FooPromise>);
  EXPECT_EQ(JsonDump(PromiseAsJson(FooPromise())), "{}");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
