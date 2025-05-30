// Copyright 2022 gRPC authors.

#include "src/core/util/no_destruct.h"

#include <stdlib.h>

#include <memory>

#include "gtest/gtest.h"

namespace grpc_core {
namespace testing {
namespace {

class CrashOnDestruction {
 public:
  void Exists() {}

 private:
  ~CrashOnDestruction() { abort(); }
};

NoDestruct<std::unique_ptr<int>> g_test_int(new int(42));
NoDestruct<CrashOnDestruction> g_test_crash_on_destruction;

TEST(NoDestruct, Works) { EXPECT_EQ(42, **g_test_int); }

TEST(NoDestruct, CrashOnDestructionIsAccessible) {
  g_test_crash_on_destruction->Exists();
}

bool g_thing_constructed = false;

class Thing {
 public:
  Thing() {
    EXPECT_FALSE(g_thing_constructed);
    g_thing_constructed = true;
  }

  int Add(int i, int j) { return i + j; }

 private:
  ~Thing() = delete;
};

TEST(GlobalSingleton, Works) {

  EXPECT_TRUE(g_thing_constructed);

  EXPECT_EQ(NoDestructSingleton<Thing>::Get()->Add(1, 2), 3);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
