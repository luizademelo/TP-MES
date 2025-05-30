
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"

#ifdef GPR_WINDOWS
#include "src/core/lib/iomgr/socket_windows.h"
#else
#include "src/core/lib/iomgr/socket_utils_posix.h"
#endif

TEST(GrpcIpv6LoopbackAvailableTest, MainTest) {

  ASSERT_TRUE(grpc_ipv6_loopback_available());
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
