
// Copyright 2016 gRPC authors.

#include <memory>

#include "gtest/gtest.h"
#include "test/core/handshake/server_ssl_common.h"
#include "test/core/test_util/test_config.h"

TEST(ServerSslTest, MainTest) {

  const char* h2_only_alpn_list[] = {"h2"};
  ASSERT_TRUE(server_ssl_test(h2_only_alpn_list, 1, "h2"));

  const char* extra_alpn_list[] = {"foo", "h2", "bar"};
  ASSERT_TRUE(server_ssl_test(extra_alpn_list, 3, "h2"));

  const char* fake_alpn_list[] = {"foo"};
  ASSERT_FALSE(server_ssl_test(fake_alpn_list, 1, "foo"));
  CleanupSslLibrary();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
