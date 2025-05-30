
// Copyright 2017 gRPC authors.

#include <grpc/support/time.h>
#include <grpcpp/completion_queue.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

class CodegenTestFull : public ::testing::Test {};

TEST_F(CodegenTestFull, Init) {
  grpc::CompletionQueue cq;
  void* tag = nullptr;
  bool ok = false;
  cq.AsyncNext(&tag, &ok, gpr_time_0(GPR_CLOCK_REALTIME));
  ASSERT_FALSE(ok);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
