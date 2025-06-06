// Copyright 2022 gRPC authors.

#include "src/core/lib/promise/interceptor_list.h"

#include <grpc/event_engine/memory_allocator.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/promise/test_context.h"

namespace grpc_core {
namespace {

class InterceptorListTest : public ::testing::Test {
 protected:
  RefCountedPtr<Arena> arena_ = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> arena_ctx_{arena_.get()};
};

TEST_F(InterceptorListTest, NoOp) { InterceptorList<std::string>(); }

TEST_F(InterceptorListTest, CanRunOne) {
  InterceptorList<std::string> list;
  list.AppendMap([](std::string s) { return s + "a"; }, DEBUG_LOCATION);
  EXPECT_EQ(list.Run("hello")(), Poll<std::optional<std::string>>("helloa"));
}

TEST_F(InterceptorListTest, CanRunTwo) {
  InterceptorList<std::string> list;
  list.AppendMap([](std::string s) { return s + "a"; }, DEBUG_LOCATION);
  list.AppendMap([](std::string s) { return s + "b"; }, DEBUG_LOCATION);
  EXPECT_EQ(list.Run("hello")(), Poll<std::optional<std::string>>("helloab"));
}

TEST_F(InterceptorListTest, CanRunTwoTwice) {
  InterceptorList<std::string> list;
  list.AppendMap([](std::string s) { return s + s; }, DEBUG_LOCATION);
  list.AppendMap([](std::string s) { return s + s + s; }, DEBUG_LOCATION);
  EXPECT_EQ(list.Run(std::string(10, 'a'))().value().value(),
            std::string(60, 'a'));
  EXPECT_EQ(list.Run(std::string(100, 'b'))().value().value(),
            std::string(600, 'b'));
}

TEST_F(InterceptorListTest, CanRunManyWithCaptures) {
  InterceptorList<std::string> list;
  for (size_t i = 0; i < 26 * 1000; i++) {
    list.AppendMap(
        [i = std::make_shared<size_t>(i)](std::string s) {
          return s + static_cast<char>((*i % 26) + 'a');
        },
        DEBUG_LOCATION);
  }
  std::string expected;
  for (size_t i = 0; i < 1000; i++) {
    expected += "abcdefghijklmnopqrstuvwxyz";
  }
  EXPECT_EQ(list.Run("")().value().value(), expected);
}

TEST_F(InterceptorListTest, CanRunOnePrepended) {
  InterceptorList<std::string> list;
  list.PrependMap([](std::string s) { return s + "a"; }, DEBUG_LOCATION);
  EXPECT_EQ(list.Run("hello")(), Poll<std::optional<std::string>>("helloa"));
}

TEST_F(InterceptorListTest, CanRunTwoPrepended) {
  InterceptorList<std::string> list;
  list.PrependMap([](std::string s) { return s + "a"; }, DEBUG_LOCATION);
  list.PrependMap([](std::string s) { return s + "b"; }, DEBUG_LOCATION);
  EXPECT_EQ(list.Run("hello")(), Poll<std::optional<std::string>>("helloba"));
}

TEST_F(InterceptorListTest, CanRunManyWithCapturesPrepended) {
  InterceptorList<std::string> list;
  for (size_t i = 0; i < 26 * 1000; i++) {
    list.PrependMap(
        [i = std::make_shared<size_t>(i)](std::string s) {
          return s + static_cast<char>((*i % 26) + 'a');
        },
        DEBUG_LOCATION);
  }
  std::string expected;
  for (size_t i = 0; i < 1000; i++) {
    expected += "zyxwvutsrqponmlkjihgfedcba";
  }
  EXPECT_EQ(list.Run("")().value().value(), expected);
}

TEST_F(InterceptorListTest, CanRunManyWithCapturesThatDelay) {
  InterceptorList<std::string> list;
  for (size_t i = 0; i < 26 * 1000; i++) {
    list.AppendMap(
        [i = std::make_shared<size_t>(i)](std::string s) {
          return
              [x = false, i, s]() mutable -> Poll<std::optional<std::string>> {
                if (!x) {
                  x = true;
                  return Pending{};
                }
                return s + static_cast<char>((*i % 26) + 'a');
              };
        },
        DEBUG_LOCATION);
  }
  auto promise = list.Run("");
  for (size_t i = 0; i < 26 * 1000; i++) {
    EXPECT_TRUE(promise().pending()) << i;
  }
  std::string expected;
  for (size_t i = 0; i < 1000; i++) {
    expected += "abcdefghijklmnopqrstuvwxyz";
  }
  EXPECT_EQ(promise().value().value(), expected);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
