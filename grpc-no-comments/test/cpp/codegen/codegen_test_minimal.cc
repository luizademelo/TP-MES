
// Copyright 2016 gRPC authors.

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

class CodegenTestMinimal : public ::testing::Test {};

TEST_F(CodegenTestMinimal, Build) {}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
