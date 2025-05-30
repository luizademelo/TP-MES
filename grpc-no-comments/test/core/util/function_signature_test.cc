// Copyright 2025 gRPC authors.

#include "src/core/util/function_signature.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace grpc_core {

namespace {
class Foo {};
}

TEST(FunctionSignatureTest, Works) {
  EXPECT_EQ(TypeName<int>(), "int");
  EXPECT_THAT(TypeName<Foo>(), ::testing::HasSubstr("Foo"));
  auto x = []() {};
  EXPECT_THAT(TypeName<decltype(x)>(), ::testing::HasSubstr("lambda"));
}

}
