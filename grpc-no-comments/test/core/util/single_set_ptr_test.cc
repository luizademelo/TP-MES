// Copyright 2022 gRPC authors.

#include "src/core/util/single_set_ptr.h"

#include <algorithm>
#include <thread>
#include <vector>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {
namespace {

TEST(SingleSetPtrTest, NoOp) { SingleSetPtr<int>(); }

TEST(SingleSetPtrTest, CanSet) {
  SingleSetPtr<int> p;
  EXPECT_FALSE(p.is_set());
  EXPECT_DEATH_IF_SUPPORTED({ LOG(ERROR) << *p; }, "");
  p.Set(new int(42));
  EXPECT_EQ(*p, 42);
}

TEST(SingleSetPtrTest, CanReset) {
  SingleSetPtr<int> p;
  EXPECT_FALSE(p.is_set());
  p.Set(new int(42));
  EXPECT_TRUE(p.is_set());
  p.Set(new int(43));
  EXPECT_EQ(*p, 42);
  p.Reset();
  EXPECT_FALSE(p.is_set());
}

TEST(SingleSetPtrTest, LotsOfSetters) {
  SingleSetPtr<int> p;
  std::vector<std::thread> threads;
  threads.reserve(100);
  Notification n;
  for (int i = 0; i < 100; i++) {
    threads.emplace_back([&p, i, &n]() {
      n.WaitForNotification();
      p.Set(new int(i));
    });
  }
  n.Notify();
  for (auto& t : threads) {
    t.join();
  }
}

class TestClass : public RefCounted<TestClass> {
 public:
  int i = 42;
};

TEST(SingleSetRefCountedPtrTest, NoOp) { SingleSetRefCountedPtr<TestClass>(); }

TEST(SingleSetRefCountedPtrTest, GetOrCreate) {
  SingleSetRefCountedPtr<TestClass> p;
  EXPECT_FALSE(p.is_set());
  auto x = p.GetOrCreate();
  EXPECT_TRUE(p.is_set());
  EXPECT_EQ(x->i, 42);
  auto y = p.GetOrCreate();
  EXPECT_EQ(x.get(), y.get());
  EXPECT_EQ(x->i, 42);
}

TEST(SingleSetRefCountedPtrTest, LotsOfGetOrCreators) {
  SingleSetRefCountedPtr<TestClass> p;
  std::vector<std::thread> threads;
  threads.reserve(100);
  Notification n;
  for (int i = 0; i < 100; i++) {
    threads.emplace_back([&p, &n]() {
      n.WaitForNotification();
      EXPECT_EQ(p.GetOrCreate()->i, 42);
    });
  }
  n.Notify();
  for (auto& t : threads) {
    t.join();
  }
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
