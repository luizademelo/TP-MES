// Copyright 2023 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"
#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/experiments/config.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/time.h"
#include "test/core/test_util/mock_endpoint.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

class ConfigurationTest : public ::testing::Test {
 protected:
  ConfigurationTest() {
    auto engine = grpc_event_engine::experimental::GetDefaultEventEngine();
    mock_endpoint_controller_ =
        grpc_event_engine::experimental::MockEndpointController::Create(engine);
    mock_endpoint_controller_->NoMoreReads();
    args_ = args_.SetObject(ResourceQuota::Default());
    args_ = args_.SetObject(std::move(engine));
  }

  std::shared_ptr<grpc_event_engine::experimental::MockEndpointController>
      mock_endpoint_controller_;
  ChannelArgs args_;
};

TEST_F(ConfigurationTest, ClientKeepaliveDefaults) {
  ExecCtx exec_ctx;
  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          true));
  EXPECT_EQ(t->keepalive_time, Duration::Infinity());
  EXPECT_EQ(t->keepalive_timeout, Duration::Infinity());
  EXPECT_EQ(t->keepalive_permit_without_calls, false);
  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 2);
  t->Orphan();
}

TEST_F(ConfigurationTest, ClientKeepaliveExplicitArgs) {
  ExecCtx exec_ctx;
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_TIME_MS, 20000);
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, true);
  args_ = args_.Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 3);
  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          true));
  EXPECT_EQ(t->keepalive_time, Duration::Seconds(20));
  EXPECT_EQ(t->keepalive_timeout, Duration::Seconds(10));
  EXPECT_EQ(t->keepalive_permit_without_calls, true);
  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 3);
  t->Orphan();
}

TEST_F(ConfigurationTest, ServerKeepaliveDefaults) {
  ExecCtx exec_ctx;
  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          false));
  EXPECT_EQ(t->keepalive_time, Duration::Hours(2));
  EXPECT_EQ(t->keepalive_timeout, Duration::Seconds(20));
  EXPECT_EQ(t->keepalive_permit_without_calls, false);

  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 0);
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMinPingIntervalWithoutData(),
            Duration::Minutes(5));
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMaxPingStrikes(), 2);
  t->Orphan();
}

TEST_F(ConfigurationTest, ServerKeepaliveExplicitArgs) {
  ExecCtx exec_ctx;
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_TIME_MS, 20000);
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
  args_ = args_.Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, true);
  args_ = args_.Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 3);
  args_ =
      args_.Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 20000);
  args_ = args_.Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, 0);
  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          false));
  EXPECT_EQ(t->keepalive_time, Duration::Seconds(20));
  EXPECT_EQ(t->keepalive_timeout, Duration::Seconds(10));
  EXPECT_EQ(t->keepalive_permit_without_calls, true);

  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 0);
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMinPingIntervalWithoutData(),
            Duration::Seconds(20));
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMaxPingStrikes(), 0);
  t->Orphan();
}

TEST_F(ConfigurationTest, ModifyClientDefaults) {
  ExecCtx exec_ctx;

  ChannelArgs args = args_.Set(GRPC_ARG_KEEPALIVE_TIME_MS, 20000);
  args = args.Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
  args = args.Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, true);
  args = args.Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 3);
  grpc_chttp2_config_default_keepalive_args(args, true);

  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          true));
  EXPECT_EQ(t->keepalive_time, Duration::Seconds(20));
  EXPECT_EQ(t->keepalive_timeout, Duration::Seconds(10));
  EXPECT_EQ(t->keepalive_permit_without_calls, true);
  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 3);
  t->Orphan();
}

TEST_F(ConfigurationTest, ModifyServerDefaults) {
  ExecCtx exec_ctx;

  ChannelArgs args = args_.Set(GRPC_ARG_KEEPALIVE_TIME_MS, 20000);
  args = args.Set(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
  args = args.Set(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, true);
  args = args.Set(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 3);
  args = args.Set(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 20000);
  args = args.Set(GRPC_ARG_HTTP2_MAX_PING_STRIKES, 0);
  grpc_chttp2_config_default_keepalive_args(args, false);

  grpc_chttp2_transport* t =
      reinterpret_cast<grpc_chttp2_transport*>(grpc_create_chttp2_transport(
          args_,
          OrphanablePtr<grpc_endpoint>(
              mock_endpoint_controller_->TakeCEndpoint()),
          false));
  EXPECT_EQ(t->keepalive_time, Duration::Seconds(20));
  EXPECT_EQ(t->keepalive_timeout, Duration::Seconds(10));
  EXPECT_EQ(t->keepalive_permit_without_calls, true);

  EXPECT_EQ(t->ping_rate_policy.TestOnlyMaxPingsWithoutData(), 0);
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMinPingIntervalWithoutData(),
            Duration::Seconds(20));
  EXPECT_EQ(t->ping_abuse_policy.TestOnlyMaxPingStrikes(), 0);
  t->Orphan();
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
