// Copyright 2025 The gRPC Authors

#include "gtest/gtest.h"
#include "src/core/lib/event_engine/posix_engine/internal_errqueue.h"

namespace grpc_event_engine {
namespace experimental {
namespace {

#ifdef GRPC_POSIX_SOCKET_TCP
TEST(KernelSupportsErrqueueTest, Basic) {
#ifdef GRPC_LINUX_ERRQUEUE
  int expected_value = true;
#else
  int expected_value = false;
#endif
  EXPECT_EQ(KernelSupportsErrqueue(), expected_value);
}
#endif

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int r = RUN_ALL_TESTS();
  return r;
}
