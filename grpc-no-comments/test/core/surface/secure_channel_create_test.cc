
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/channel.h"
#include "test/core/test_util/test_config.h"

void test_unknown_scheme_target(void) {
  grpc_channel_credentials* creds =
      grpc_fake_transport_security_credentials_create();
  grpc_channel* chan = grpc_channel_create("blah://blah", creds, nullptr);
  grpc_channel_element* elem = grpc_channel_stack_element(
      grpc_core::Channel::FromC(chan)->channel_stack(), 0);
  ASSERT_EQ(elem->filter->name.name(), "lame-client");
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Channel::FromC(chan)->Unref();
  creds->Unref();
}

void test_security_connector_already_in_arg(void) {
  grpc_arg arg = grpc_security_connector_to_arg(nullptr);
  grpc_channel_args args;
  args.num_args = 1;
  args.args = &arg;
  grpc_channel* chan = grpc_channel_create(nullptr, nullptr, &args);
  grpc_channel_element* elem = grpc_channel_stack_element(
      grpc_core::Channel::FromC(chan)->channel_stack(), 0);
  ASSERT_EQ(elem->filter->name.name(), "lame-client");
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Channel::FromC(chan)->Unref();
}

void test_null_creds(void) {
  grpc_channel* chan = grpc_channel_create(nullptr, nullptr, nullptr);
  grpc_channel_element* elem = grpc_channel_stack_element(
      grpc_core::Channel::FromC(chan)->channel_stack(), 0);
  ASSERT_EQ(elem->filter->name.name(), "lame-client");
  grpc_core::ExecCtx exec_ctx;
  grpc_core::Channel::FromC(chan)->Unref();
}

TEST(SecureChannelCreateTest, MainTest) {
  grpc_init();
  test_security_connector_already_in_arg();
  test_null_creds();
  grpc_core::CoreConfiguration::RunWithSpecialConfiguration(
      [](grpc_core::CoreConfiguration::Builder* builder) {
        BuildCoreConfiguration(builder);

        builder->resolver_registry()->Reset();
      },
      []() { test_unknown_scheme_target(); });
  grpc_shutdown();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
