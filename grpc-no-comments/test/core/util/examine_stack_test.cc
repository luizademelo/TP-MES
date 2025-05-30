
// Copyright 2020 gRPC authors.

#include "src/core/util/examine_stack.h"

#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "absl/log/log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

std::string SimpleCurrentStackTraceProvider() { return "stacktrace"; }

std::string AbseilCurrentStackTraceProvider() {
  std::string result = "Stack trace:\n";
  constexpr int kNumStackFrames = 10;
  void* stack[kNumStackFrames];
  int frame_sizes[kNumStackFrames];
  int depth = absl::GetStackFrames(stack, frame_sizes, kNumStackFrames, 1);
  for (int i = 0; i < depth; i++) {
    char tmp[1024];
    const char* symbol = "(unknown)";
    if (absl::Symbolize(stack[i], tmp, sizeof(tmp))) {
      symbol = tmp;
    }
    result += symbol;
    result += +"\n";
  }
  return result;
}

}

TEST(ExamineStackTest, NullStackProvider) {
  grpc_core::SetCurrentStackTraceProvider(nullptr);
  EXPECT_EQ(grpc_core::GetCurrentStackTraceProvider(), nullptr);
  EXPECT_EQ(grpc_core::GetCurrentStackTrace(), std::nullopt);
}

TEST(ExamineStackTest, SimpleStackProvider) {
  grpc_core::SetCurrentStackTraceProvider(&SimpleCurrentStackTraceProvider);
  EXPECT_NE(grpc_core::GetCurrentStackTraceProvider(), nullptr);
  EXPECT_EQ(grpc_core::GetCurrentStackTrace(), "stacktrace");
}

TEST(ExamineStackTest, AbseilStackProvider) {
  grpc_core::SetCurrentStackTraceProvider(&AbseilCurrentStackTraceProvider);
  EXPECT_NE(grpc_core::GetCurrentStackTraceProvider(), nullptr);
  const std::optional<std::string> stack_trace =
      grpc_core::GetCurrentStackTrace();
  EXPECT_NE(stack_trace, std::nullopt);
  LOG(INFO) << "stack_trace=" << *stack_trace;
#if !defined(NDEBUG) && !defined(GPR_MUSL_LIBC_COMPAT)

  EXPECT_THAT(*stack_trace, ::testing::HasSubstr("testing::"));
#endif
}

int main(int argc, char** argv) {
  absl::InitializeSymbolizer(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
