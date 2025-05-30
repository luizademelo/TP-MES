// Copyright 2023 The gRPC Authors

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"

using ::grpc_event_engine::experimental::EventEngine;

template <typename T>
class TaskHandleTest : public testing::Test {};

using HandleTypes =
    ::testing::Types<EventEngine::TaskHandle, EventEngine::ConnectionHandle>;
TYPED_TEST_SUITE(TaskHandleTest, HandleTypes);

TYPED_TEST(TaskHandleTest, Identity) {
  TypeParam t{42, 43};
  ASSERT_EQ(t, t);
}

TYPED_TEST(TaskHandleTest, CommutativeEquality) {
  TypeParam t1{42, 43};
  TypeParam t2 = t1;
  ASSERT_EQ(t1, t2);
  ASSERT_EQ(t2, t1);
}

TYPED_TEST(TaskHandleTest, Validity) {
  TypeParam t{42, 43};
  ASSERT_NE(t, TypeParam::kInvalid);
  ASSERT_NE(TypeParam::kInvalid, t);
  ASSERT_EQ(TypeParam::kInvalid, TypeParam::kInvalid);
}

TYPED_TEST(TaskHandleTest, AbslStringify) {
  TypeParam t{42, 43};
  ASSERT_EQ(absl::StrCat(t), "{000000000000002a,000000000000002b}");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
