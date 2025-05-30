// Copyright 2024 gRPC authors.

#include "src/core/filter/blackboard.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace grpc_core {
namespace {

class FooEntry : public Blackboard::Entry {
 public:
  static UniqueTypeName Type() {
    static UniqueTypeName::Factory kFactory("FooEntry");
    return kFactory.Create();
  }
};

class BarEntry : public Blackboard::Entry {
 public:
  static UniqueTypeName Type() {
    static UniqueTypeName::Factory kFactory("BarEntry");
    return kFactory.Create();
  }
};

TEST(Blackboard, Basic) {
  Blackboard blackboard;

  EXPECT_EQ(blackboard.Get<FooEntry>("a"), nullptr);

  auto foo_entry = MakeRefCounted<FooEntry>();
  blackboard.Set("a", foo_entry);

  EXPECT_EQ(blackboard.Get<FooEntry>("a"), foo_entry);

  EXPECT_EQ(blackboard.Get<FooEntry>("b"), nullptr);

  EXPECT_EQ(blackboard.Get<BarEntry>("a"), nullptr);

  auto bar_entry = MakeRefCounted<BarEntry>();
  blackboard.Set("a", bar_entry);
  EXPECT_EQ(blackboard.Get<BarEntry>("a"), bar_entry);

  EXPECT_EQ(blackboard.Get<FooEntry>("a"), foo_entry);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
