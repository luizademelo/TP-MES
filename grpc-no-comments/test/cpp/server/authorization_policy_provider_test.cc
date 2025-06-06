// Copyright 2021 gRPC authors.

#include <grpcpp/security/authorization_policy_provider.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

#define VALID_POLICY_PATH_1 \
  "test/core/security/authorization/test_policies/valid_policy_1.json"
#define VALID_POLICY_PATH_2 \
  "test/core/security/authorization/test_policies/valid_policy_2.json"
#define INVALID_POLICY_PATH \
  "test/core/security/authorization/test_policies/invalid_policy.json"

namespace grpc {

TEST(AuthorizationPolicyProviderTest, StaticDataCreateReturnsProvider) {
  grpc::Status status;
  auto provider = experimental::StaticDataAuthorizationPolicyProvider::Create(
      grpc_core::testing::GetFileContents(VALID_POLICY_PATH_1), &status);
  ASSERT_NE(provider, nullptr);
  EXPECT_NE(provider->c_provider(), nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(status.error_message().empty());
}

TEST(AuthorizationPolicyProviderTest, StaticDataCreateReturnsErrorStatus) {
  grpc::Status status;
  auto provider = experimental::StaticDataAuthorizationPolicyProvider::Create(
      grpc_core::testing::GetFileContents(INVALID_POLICY_PATH), &status);
  ASSERT_EQ(provider, nullptr);
  EXPECT_EQ(status.error_code(), grpc::StatusCode::INVALID_ARGUMENT);
  EXPECT_EQ(status.error_message(), "\"name\" field is not present.");
}

TEST(AuthorizationPolicyProviderTest, FileWatcherCreateReturnsProvider) {
  auto tmp_authz_policy = std::make_unique<grpc_core::testing::TmpFile>(
      grpc_core::testing::GetFileContents(VALID_POLICY_PATH_1));
  grpc::Status status;
  auto provider = experimental::FileWatcherAuthorizationPolicyProvider::Create(
      tmp_authz_policy->name(), 1, &status);
  ASSERT_NE(provider, nullptr);
  EXPECT_NE(provider->c_provider(), nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(status.error_message().empty());
}

TEST(AuthorizationPolicyProviderTest, FileWatcherCreateReturnsErrorStatus) {
  auto tmp_authz_policy = std::make_unique<grpc_core::testing::TmpFile>(
      grpc_core::testing::GetFileContents(INVALID_POLICY_PATH));
  grpc::Status status;
  auto provider = experimental::FileWatcherAuthorizationPolicyProvider::Create(
      tmp_authz_policy->name(), 1, &status);
  ASSERT_EQ(provider, nullptr);
  EXPECT_EQ(status.error_code(), grpc::StatusCode::INVALID_ARGUMENT);
  EXPECT_EQ(status.error_message(), "\"name\" field is not present.");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
