
// Copyright 2015 gRPC authors.

#include "src/core/util/env.h"

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

TEST(EnvTest, SetenvGetenv) {
  const char* name = "FOO";
  const char* value = "BAR";

  LOG(INFO) << "test_setenv_getenv";

  grpc_core::SetEnv(name, value);
  auto retrieved_value = grpc_core::GetEnv(name);
  ASSERT_EQ(value, retrieved_value);
}

TEST(EnvTest, Unsetenv) {
  const char* name = "FOO";
  const char* value = "BAR";

  LOG(INFO) << "test_unsetenv";

  grpc_core::SetEnv(name, value);
  grpc_core::UnsetEnv(name);
  auto retrieved_value = grpc_core::GetEnv(name);
  ASSERT_FALSE(retrieved_value.has_value());
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
