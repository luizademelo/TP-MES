
// Copyright 2020 the gRPC authors.

#include "test/core/test_util/stack_tracer.h"

#include <string>

#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

TEST(StackTracerTest, Basic) {
  std::string stack_trace = grpc_core::testing::GetCurrentStackTrace();
  LOG(INFO) << "stack_trace=" << stack_trace;
#if !defined(NDEBUG) && !defined(GPR_MUSL_LIBC_COMPAT)
  EXPECT_TRUE(absl::StrContains(stack_trace, "Basic"));
#endif
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
