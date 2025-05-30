
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/alts/grpc_alts_credentials_options.h"

#include <grpc/grpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"
#include "src/core/util/crash.h"

#define ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_1 "abc@google.com"
#define ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_2 "def@google.com"

const size_t kTargetServiceAccountNum = 2;

TEST(GrpcAltsCredentialsOptionsTest, CopyClientOptionsFailure) {

  grpc_alts_credentials_options* options =
      grpc_alts_credentials_client_options_create();

  ASSERT_EQ(grpc_alts_credentials_options_copy(nullptr), nullptr);

  grpc_alts_credentials_options_destroy(options);
}

static size_t get_target_service_account_num(
    grpc_alts_credentials_options* options) {
  auto client_options =
      reinterpret_cast<grpc_alts_credentials_client_options*>(options);
  size_t num = 0;
  target_service_account* node = client_options->target_account_list_head;
  while (node != nullptr) {
    num++;
    node = node->next;
  }
  return num;
}

TEST(GrpcAltsCredentialsOptionsTest, ClientOptionsApiSuccess) {

  grpc_alts_credentials_options* options =
      grpc_alts_credentials_client_options_create();

  grpc_alts_credentials_client_options_add_target_service_account(
      options, ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_1);
  grpc_alts_credentials_client_options_add_target_service_account(
      options, ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_2);

  ASSERT_EQ(get_target_service_account_num(options), kTargetServiceAccountNum);
  auto client_options =
      reinterpret_cast<grpc_alts_credentials_client_options*>(options);
  ASSERT_STREQ(client_options->target_account_list_head->data,
               ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_2);
  ASSERT_STREQ(client_options->target_account_list_head->next->data,
               ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_1);

  grpc_alts_credentials_options* new_options =
      grpc_alts_credentials_options_copy(options);
  ASSERT_EQ(get_target_service_account_num(new_options),
            kTargetServiceAccountNum);
  auto new_client_options =
      reinterpret_cast<grpc_alts_credentials_client_options*>(new_options);
  ASSERT_STREQ(new_client_options->target_account_list_head->data,
               ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_2);
  ASSERT_STREQ(new_client_options->target_account_list_head->next->data,
               ALTS_CLIENT_OPTIONS_TEST_TARGET_SERVICE_ACCOUNT_1);

  grpc_alts_credentials_options_destroy(options);
  grpc_alts_credentials_options_destroy(new_options);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
