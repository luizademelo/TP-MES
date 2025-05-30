
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/alpn/alpn.h"

#include <memory>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

TEST(AlpnTest, TestAlpnSuccess) {
  ASSERT_TRUE(grpc_chttp2_is_alpn_version_supported("h2", 2));
}

TEST(AlpnTest, TestAlpnFailure) {
  ASSERT_FALSE(grpc_chttp2_is_alpn_version_supported("h2-155", 6));
  ASSERT_FALSE(grpc_chttp2_is_alpn_version_supported("h1-15", 5));
  ASSERT_FALSE(grpc_chttp2_is_alpn_version_supported("grpc-exp", 8));
  ASSERT_FALSE(grpc_chttp2_is_alpn_version_supported("h", 1));
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
