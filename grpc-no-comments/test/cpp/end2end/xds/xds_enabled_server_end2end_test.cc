
// Copyright 2017 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/xds_server_builder.h>

#include <memory>
#include <optional>

#include "absl/strings/str_cat.h"
#include "absl/time/time.h"
#include "envoy/config/listener/v3/listener.pb.h"
#include "envoy/config/route/v3/route.pb.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.pb.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/util/env.h"
#include "src/core/util/time.h"
#include "src/proto/grpc/testing/echo.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/resolve_localhost_ip46.h"
#include "test/core/test_util/scoped_env_var.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/xds/xds_end2end_test_lib.h"

namespace grpc {
namespace testing {
namespace {

using ::envoy::config::listener::v3::FilterChainMatch;

class XdsEnabledServerTest : public XdsEnd2endTest {
 protected:
  void SetUp() override {}

  void DoSetUp(
      const std::optional<XdsBootstrapBuilder>& builder = std::nullopt) {

    InitClient(builder, "",

               500,
               "", nullptr,
               InsecureChannelCredentials());
    CreateBackends(1, true, InsecureServerCredentials());
    EdsResourceArgs args({{"locality0", CreateEndpointsForBackends(0, 1)}});
    balancer_->ads_service()->SetEdsResource(BuildEdsResource(args));
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, XdsEnabledServerTest,
                         ::testing::Values(XdsTestType().set_bootstrap_source(
                             XdsTestType::kBootstrapFromEnvVar)),
                         &XdsTestType::Name);

TEST_P(XdsEnabledServerTest, Basic) {
  DoSetUp();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  WaitForBackend(DEBUG_LOCATION, 0);
}

TEST_P(XdsEnabledServerTest, ListenerDeletionFailsByDefault) {
  DoSetUp();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  WaitForBackend(DEBUG_LOCATION, 0);

  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) break;
    ASSERT_TRUE(response_state.has_value());
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
  }

  balancer_->ads_service()->UnsetResource(
      kLdsTypeUrl, GetServerListenerName(backends_[0]->port()));

  ASSERT_TRUE(
      backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::NOT_FOUND));
}

TEST_P(XdsEnabledServerTest, ListenerDeletionIgnoredIfConfigured) {
  DoSetUp(MakeBootstrapBuilder().SetIgnoreResourceDeletion());
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  WaitForBackend(DEBUG_LOCATION, 0);

  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) break;
    ASSERT_TRUE(response_state.has_value());
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
  }

  balancer_->ads_service()->UnsetResource(
      kLdsTypeUrl, GetServerListenerName(backends_[0]->port()));

  absl::Time deadline =
      absl::Now() + (absl::Seconds(10) * grpc_test_slowdown_factor());
  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) {
      gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
      continue;
    }
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
    ASSERT_LT(absl::Now(), deadline);
    break;
  }

  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(XdsEnabledServerTest,
       ListenerDeletionFailsWithFailOnDataErrorsIfEnabled) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  DoSetUp(MakeBootstrapBuilder().SetFailOnDataErrors());
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  WaitForBackend(DEBUG_LOCATION, 0);

  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) break;
    ASSERT_TRUE(response_state.has_value());
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
  }

  balancer_->ads_service()->UnsetResource(
      kLdsTypeUrl, GetServerListenerName(backends_[0]->port()));

  ASSERT_TRUE(
      backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::NOT_FOUND));
}

TEST_P(XdsEnabledServerTest,
       ListenerDeletionIgnoredByDefaultIfDataErrorHandlingEnabled) {
  grpc_core::testing::ScopedExperimentalEnvVar env(
      "GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  DoSetUp();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  WaitForBackend(DEBUG_LOCATION, 0);

  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) break;
    ASSERT_TRUE(response_state.has_value());
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
  }

  balancer_->ads_service()->UnsetResource(
      kLdsTypeUrl, GetServerListenerName(backends_[0]->port()));

  absl::Time deadline =
      absl::Now() + (absl::Seconds(10) * grpc_test_slowdown_factor());
  while (true) {
    auto response_state = balancer_->ads_service()->lds_response_state();
    if (!response_state.has_value()) {
      gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
      continue;
    }
    EXPECT_EQ(response_state->state, AdsServiceImpl::ResponseState::ACKED);
    ASSERT_LT(absl::Now(), deadline);
    break;
  }

  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(XdsEnabledServerTest, BadLdsUpdateNoApiListenerNorAddress) {
  DoSetUp();
  Listener listener = default_server_listener_;
  listener.clear_address();
  listener.set_name(GetServerListenerName(backends_[0]->port()));
  balancer_->ads_service()->SetLdsResource(listener);
  StartBackend(0);
  const auto response_state = WaitForLdsNack(DEBUG_LOCATION);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_THAT(response_state->error_message,
              ::testing::EndsWith(absl::StrCat(
                  GetServerListenerName(backends_[0]->port()),
                  ": INVALID_ARGUMENT: Listener has neither address nor "
                  "ApiListener]")));
}

TEST_P(XdsEnabledServerTest, NonTcpListener) {
  DoSetUp();
  Listener listener = default_listener_;
  listener = PopulateServerListenerNameAndPort(listener, backends_[0]->port());
  auto hcm = ClientHcmAccessor().Unpack(listener);
  auto* rds = hcm.mutable_rds();
  rds->set_route_config_name(kDefaultRouteConfigurationName);
  rds->mutable_config_source()->mutable_self();
  ClientHcmAccessor().Pack(hcm, &listener);
  balancer_->ads_service()->SetLdsResource(listener);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(
      grpc::StatusCode::FAILED_PRECONDITION));
}

TEST_P(XdsEnabledServerTest, ListenerAddressMismatch) {
  DoSetUp();
  Listener listener = default_server_listener_;

  listener.mutable_address()->mutable_socket_address()->set_address(
      "192.168.1.1");
  SetServerListenerNameAndRouteConfiguration(balancer_.get(), listener,
                                             backends_[0]->port(),
                                             default_server_route_config_);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(
      grpc::StatusCode::FAILED_PRECONDITION));
}

class XdsEnabledServerStatusNotificationTest : public XdsEnabledServerTest {
 protected:
  void SetValidLdsUpdate() {
    SetServerListenerNameAndRouteConfiguration(
        balancer_.get(), default_server_listener_, backends_[0]->port(),
        default_server_route_config_);
  }

  void SetInvalidLdsUpdate() {
    Listener listener = default_server_listener_;
    listener.clear_address();
    listener.set_name(GetServerListenerName(backends_[0]->port()));
    balancer_->ads_service()->SetLdsResource(listener);
  }

  void UnsetLdsUpdate() {
    balancer_->ads_service()->UnsetResource(
        kLdsTypeUrl, GetServerListenerName(backends_[0]->port()));
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, XdsEnabledServerStatusNotificationTest,
                         ::testing::Values(XdsTestType()), &XdsTestType::Name);

TEST_P(XdsEnabledServerStatusNotificationTest, ServingStatus) {
  DoSetUp();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsEnabledServerStatusNotificationTest, NotServingStatus) {
  DoSetUp();
  SetInvalidLdsUpdate();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(
      grpc::StatusCode::INVALID_ARGUMENT));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
}

TEST_P(XdsEnabledServerStatusNotificationTest, ErrorUpdateWhenAlreadyServing) {
  DoSetUp();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));

  SetInvalidLdsUpdate();
  auto response_state =
      WaitForLdsNack(DEBUG_LOCATION, RpcOptions(), StatusCode::OK);
  ASSERT_TRUE(response_state.has_value()) << "timed out waiting for NACK";
  EXPECT_THAT(response_state->error_message,
              ::testing::EndsWith(absl::StrCat(
                  GetServerListenerName(backends_[0]->port()),
                  ": INVALID_ARGUMENT: Listener has neither address nor "
                  "ApiListener]")));
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION);
}

TEST_P(XdsEnabledServerStatusNotificationTest,
       NotServingStatusToServingStatusTransition) {
  DoSetUp();
  SetInvalidLdsUpdate();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(
      grpc::StatusCode::INVALID_ARGUMENT));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));

  SetValidLdsUpdate();
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsEnabledServerStatusNotificationTest,
       ServingStatusToNonServingStatusTransition) {
  DoSetUp(MakeBootstrapBuilder().SetFailOnDataErrors());
  SetValidLdsUpdate();
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));

  UnsetLdsUpdate();
  ASSERT_TRUE(
      backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::NOT_FOUND));
  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex(
          "connections to all backends failing; last error: "));
}

TEST_P(XdsEnabledServerStatusNotificationTest, RepeatedServingStatusChanges) {
  DoSetUp(MakeBootstrapBuilder().SetFailOnDataErrors());
  StartBackend(0);
  for (int i = 0; i < 5; ++i) {

    SetValidLdsUpdate();
    ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
    CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));

    UnsetLdsUpdate();
    ASSERT_TRUE(
        backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::NOT_FOUND));
    SendRpcsUntilFailure(
        DEBUG_LOCATION, StatusCode::UNAVAILABLE,
        MakeConnectionFailureRegex(
            "connections to all backends failing; last error: "));
  }
}

TEST_P(XdsEnabledServerStatusNotificationTest, ExistingRpcsOnResourceDeletion) {
  DoSetUp(MakeBootstrapBuilder().SetFailOnDataErrors());
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  constexpr int kNumChannels = 10;
  struct StreamingRpc {
    std::shared_ptr<Channel> channel;
    std::unique_ptr<grpc::testing::EchoTestService::Stub> stub;
    ClientContext context;
    std::unique_ptr<ClientReaderWriter<EchoRequest, EchoResponse>> stream;
  } streaming_rpcs[kNumChannels];
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  ChannelArguments args;
  args.SetInt(GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL, 1);
  for (int i = 0; i < kNumChannels; i++) {
    streaming_rpcs[i].channel =
        CreateCustomChannel(grpc_core::LocalIpUri(backends_[0]->port()),
                            InsecureChannelCredentials(), args);
    streaming_rpcs[i].stub =
        grpc::testing::EchoTestService::NewStub(streaming_rpcs[i].channel);
    streaming_rpcs[i].context.set_wait_for_ready(true);
    streaming_rpcs[i].stream =
        streaming_rpcs[i].stub->BidiStream(&streaming_rpcs[i].context);
    EXPECT_TRUE(streaming_rpcs[i].stream->Write(request));
    streaming_rpcs[i].stream->Read(&response);
    EXPECT_EQ(request.message(), response.message());
  }

  UnsetLdsUpdate();
  ASSERT_TRUE(
      backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::NOT_FOUND));
  SendRpcsUntilFailure(
      DEBUG_LOCATION, StatusCode::UNAVAILABLE,
      MakeConnectionFailureRegex(
          "connections to all backends failing; last error: "));
  for (int i = 0; i < kNumChannels; i++) {
    EXPECT_TRUE(streaming_rpcs[i].stream->Write(request));
    streaming_rpcs[i].stream->Read(&response);
    EXPECT_EQ(request.message(), response.message());
    EXPECT_TRUE(streaming_rpcs[i].stream->WritesDone());
    auto status = streaming_rpcs[i].stream->Finish();
    EXPECT_TRUE(status.ok())
        << status.error_message() << ", " << status.error_details() << ", "
        << streaming_rpcs[i].context.debug_error_string();

    ClientContext new_context;
    new_context.set_deadline(grpc_timeout_milliseconds_to_deadline(1000));
    EXPECT_FALSE(
        streaming_rpcs[i].stub->Echo(&new_context, request, &response).ok());
  }
}

TEST_P(XdsEnabledServerStatusNotificationTest,
       ExistingRpcsFailOnResourceUpdateAfterDrainGraceTimeExpires) {
  DoSetUp();
  constexpr int kDrainGraceTimeMs = 100;
  xds_drain_grace_time_ms_ = kDrainGraceTimeMs;
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  constexpr int kNumChannels = 10;
  struct StreamingRpc {
    std::shared_ptr<Channel> channel;
    std::unique_ptr<grpc::testing::EchoTestService::Stub> stub;
    ClientContext context;
    std::unique_ptr<ClientReaderWriter<EchoRequest, EchoResponse>> stream;
  } streaming_rpcs[kNumChannels];
  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello");
  ChannelArguments args;
  args.SetInt(GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL, 1);
  for (int i = 0; i < kNumChannels; i++) {
    streaming_rpcs[i].channel =
        CreateCustomChannel(grpc_core::LocalIpUri(backends_[0]->port()),
                            InsecureChannelCredentials(), args);
    streaming_rpcs[i].stub =
        grpc::testing::EchoTestService::NewStub(streaming_rpcs[i].channel);
    streaming_rpcs[i].context.set_wait_for_ready(true);
    streaming_rpcs[i].stream =
        streaming_rpcs[i].stub->BidiStream(&streaming_rpcs[i].context);
    EXPECT_TRUE(streaming_rpcs[i].stream->Write(request));
    streaming_rpcs[i].stream->Read(&response);
    EXPECT_EQ(request.message(), response.message());
  }
  grpc_core::Timestamp update_time = NowFromCycleCounter();

  auto route_config = default_server_route_config_;
  route_config.mutable_virtual_hosts(0)->mutable_routes(0)->mutable_redirect();
  SetServerListenerNameAndRouteConfiguration(
      balancer_.get(), default_server_listener_, backends_[0]->port(),
      route_config);
  SendRpcsUntilFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                       "UNAVAILABLE:matching route has unsupported action");

  for (int i = 0; i < kNumChannels; i++) {

    EXPECT_FALSE(streaming_rpcs[i].stream->Read(&response));

    EXPECT_GE(NowFromCycleCounter() - update_time,
              grpc_core::Duration::Milliseconds(kDrainGraceTimeMs));
    auto status = streaming_rpcs[i].stream->Finish();
    EXPECT_EQ(status.error_code(), grpc::StatusCode::UNAVAILABLE)
        << status.error_code() << ", " << status.error_message() << ", "
        << status.error_details() << ", "
        << streaming_rpcs[i].context.debug_error_string();
    EXPECT_EQ(status.error_message(),
              "Drain grace time expired. Closing connection immediately.");
  }
}

class XdsServerFilterChainMatchTest : public XdsEnabledServerTest {
 public:
  void SetUp() override { DoSetUp(); }

  HttpConnectionManager GetHttpConnectionManager(const Listener& listener) {
    HttpConnectionManager http_connection_manager =
        ServerHcmAccessor().Unpack(listener);
    *http_connection_manager.mutable_route_config() =
        default_server_route_config_;
    return http_connection_manager;
  }
};

INSTANTIATE_TEST_SUITE_P(XdsTest, XdsServerFilterChainMatchTest,
                         ::testing::Values(XdsTestType().set_bootstrap_source(
                             XdsTestType::kBootstrapFromEnvVar)),
                         &XdsTestType::Name);

TEST_P(XdsServerFilterChainMatchTest,
       DefaultFilterChainUsedWhenNoFilterChainMentioned) {
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       DefaultFilterChainUsedWhenOtherFilterChainsDontMatch) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()
      ->mutable_destination_port()
      ->set_value(8080);
  SetServerListenerNameAndRouteConfiguration(balancer_.get(), listener,
                                             backends_[0]->port(),
                                             default_server_route_config_);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithDestinationPortDontMatch) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()
      ->mutable_destination_port()
      ->set_value(8080);
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
}

TEST_P(XdsServerFilterChainMatchTest, FilterChainsWithServerNamesDontMatch) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_server_names("server_name");
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithTransportProtocolsOtherThanRawBufferDontMatch) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->set_transport_protocol("tls");
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithApplicationProtocolsDontMatch) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_application_protocols("h2");
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      MakeConnectionFailureRegex(
                          "connections to all backends failing; last error: "));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithTransportProtocolRawBufferIsPreferred) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->set_transport_protocol(
      "raw_buffer");

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_application_protocols("h2");
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithMoreSpecificDestinationPrefixRangesArePreferred) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  auto* prefix_range =
      filter_chain->mutable_filter_chain_match()->add_prefix_ranges();
  prefix_range->set_address_prefix(grpc_core::LocalIp());
  prefix_range->mutable_prefix_len()->set_value(4);
  prefix_range =
      filter_chain->mutable_filter_chain_match()->add_prefix_ranges();
  prefix_range->set_address_prefix(grpc_core::LocalIp());
  prefix_range->mutable_prefix_len()->set_value(16);
  filter_chain->mutable_filter_chain_match()->add_server_names("server_name");

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  prefix_range =
      filter_chain->mutable_filter_chain_match()->add_prefix_ranges();
  prefix_range->set_address_prefix(grpc_core::LocalIp());
  prefix_range->mutable_prefix_len()->set_value(8);
  prefix_range =
      filter_chain->mutable_filter_chain_match()->add_prefix_ranges();
  prefix_range->set_address_prefix(grpc_core::LocalIp());
  prefix_range->mutable_prefix_len()->set_value(24);

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  prefix_range =
      filter_chain->mutable_filter_chain_match()->add_prefix_ranges();
  prefix_range->set_address_prefix("192.168.1.1");
  prefix_range->mutable_prefix_len()->set_value(30);
  filter_chain->mutable_filter_chain_match()->add_server_names("server_name");

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_server_names("server_name");
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsThatMentionSourceTypeArePreferred) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->set_source_type(
      FilterChainMatch::SAME_IP_OR_LOOPBACK);

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->set_source_type(
      FilterChainMatch::EXTERNAL);
  filter_chain->mutable_filter_chain_match()->add_source_ports(
      backends_[0]->port());

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_source_ports(
      backends_[0]->port());
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithMoreSpecificSourcePrefixRangesArePreferred) {
  Listener listener = default_server_listener_;

  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  auto* source_prefix_range =
      filter_chain->mutable_filter_chain_match()->add_source_prefix_ranges();
  source_prefix_range->set_address_prefix(grpc_core::LocalIp());
  source_prefix_range->mutable_prefix_len()->set_value(4);
  source_prefix_range =
      filter_chain->mutable_filter_chain_match()->add_source_prefix_ranges();
  source_prefix_range->set_address_prefix(grpc_core::LocalIp());
  source_prefix_range->mutable_prefix_len()->set_value(16);
  filter_chain->mutable_filter_chain_match()->add_source_ports(
      backends_[0]->port());

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  source_prefix_range =
      filter_chain->mutable_filter_chain_match()->add_source_prefix_ranges();
  source_prefix_range->set_address_prefix(grpc_core::LocalIp());
  source_prefix_range->mutable_prefix_len()->set_value(8);
  source_prefix_range =
      filter_chain->mutable_filter_chain_match()->add_source_prefix_ranges();
  source_prefix_range->set_address_prefix(grpc_core::LocalIp());
  source_prefix_range->mutable_prefix_len()->set_value(24);

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  source_prefix_range =
      filter_chain->mutable_filter_chain_match()->add_source_prefix_ranges();
  source_prefix_range->set_address_prefix("192.168.1.1");
  source_prefix_range->mutable_prefix_len()->set_value(30);
  filter_chain->mutable_filter_chain_match()->add_source_ports(
      backends_[0]->port());

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));
  filter_chain->mutable_filter_chain_match()->add_source_ports(
      backends_[0]->port());
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerFilterChainMatchTest,
       FilterChainsWithMoreSpecificSourcePortArePreferred) {
  Listener listener = default_server_listener_;
  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      GetHttpConnectionManager(listener));

  for (int i = 1; i < 65536; i++) {
    filter_chain->mutable_filter_chain_match()->add_source_ports(i);
  }

  auto hcm = GetHttpConnectionManager(listener);
  hcm.mutable_route_config()
      ->mutable_virtual_hosts(0)
      ->mutable_routes(0)
      ->mutable_redirect();
  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(hcm);
  listener.clear_default_filter_chain();
  balancer_->ads_service()->SetLdsResource(
      PopulateServerListenerNameAndPort(listener, backends_[0]->port()));
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));

  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

class XdsServerRdsTest : public XdsEnabledServerTest {
 public:
  void SetUp() override { DoSetUp(); }
};

INSTANTIATE_TEST_SUITE_P(
    XdsTest, XdsServerRdsTest,
    ::testing::Values(
        XdsTestType().set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar),
        XdsTestType()
            .set_bootstrap_source(XdsTestType::kBootstrapFromEnvVar)
            .set_enable_rds_testing()),
    &XdsTestType::Name);

TEST_P(XdsServerRdsTest, Basic) {
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerRdsTest, FailsRouteMatchesOtherThanNonForwardingAction) {
  SetServerListenerNameAndRouteConfiguration(
      balancer_.get(), default_server_listener_, backends_[0]->port(),
      default_route_config_ );
  StartBackend(0);

  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "UNAVAILABLE:matching route has unsupported action");
}

TEST_P(XdsServerRdsTest, NonInlineRouteConfigurationNonDefaultFilterChain) {
  if (!GetParam().enable_rds_testing()) return;
  Listener listener = default_server_listener_;
  auto* filter_chain = listener.add_filter_chains();
  HttpConnectionManager http_connection_manager =
      ServerHcmAccessor().Unpack(listener);
  auto* rds = http_connection_manager.mutable_rds();
  rds->set_route_config_name(kDefaultServerRouteConfigurationName);
  rds->mutable_config_source()->mutable_self();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);
  SetServerListenerNameAndRouteConfiguration(balancer_.get(), listener,
                                             backends_[0]->port(),
                                             default_server_route_config_);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

TEST_P(XdsServerRdsTest, NonInlineRouteConfigurationNotAvailable) {
  if (!GetParam().enable_rds_testing()) return;
  Listener listener = default_server_listener_;
  HttpConnectionManager http_connection_manager =
      ServerHcmAccessor().Unpack(listener);
  auto* rds = http_connection_manager.mutable_rds();
  rds->set_route_config_name("unknown_server_route_config");
  rds->mutable_config_source()->mutable_self();
  listener.add_filter_chains()->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);
  SetServerListenerNameAndRouteConfiguration(balancer_.get(), listener,
                                             backends_[0]->port(),
                                             default_server_route_config_);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendFailure(DEBUG_LOCATION, StatusCode::UNAVAILABLE,
                      "RDS resource unknown_server_route_config: "
                      "does not exist \\(node ID:xds_end2end_test\\)");
}

TEST_P(XdsServerRdsTest, MultipleRouteConfigurations) {
  Listener listener = default_server_listener_;

  auto new_route_config = default_server_route_config_;
  new_route_config.set_name("new_server_route_config");
  HttpConnectionManager http_connection_manager =
      ServerHcmAccessor().Unpack(listener);
  auto* rds = http_connection_manager.mutable_rds();
  rds->set_route_config_name(new_route_config.name());
  rds->mutable_config_source()->mutable_self();
  listener.add_filter_chains()->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);

  auto another_route_config = default_server_route_config_;
  another_route_config.set_name("another_server_route_config");
  http_connection_manager.mutable_rds()->set_route_config_name(
      another_route_config.name());
  auto* filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);
  filter_chain->mutable_filter_chain_match()->set_source_type(
      FilterChainMatch::SAME_IP_OR_LOOPBACK);

  filter_chain = listener.add_filter_chains();
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);
  filter_chain->mutable_filter_chain_match()->set_source_type(
      FilterChainMatch::EXTERNAL);

  filter_chain = listener.add_filter_chains();
  filter_chain->mutable_filter_chain_match()->add_source_ports(1234);
  http_connection_manager = ServerHcmAccessor().Unpack(listener);
  *http_connection_manager.mutable_route_config() =
      default_server_route_config_;
  filter_chain->add_filters()->mutable_typed_config()->PackFrom(
      http_connection_manager);

  balancer_->ads_service()->SetRdsResource(new_route_config);
  balancer_->ads_service()->SetRdsResource(another_route_config);
  SetServerListenerNameAndRouteConfiguration(balancer_.get(), listener,
                                             backends_[0]->port(),
                                             default_server_route_config_);
  StartBackend(0);
  ASSERT_TRUE(backends_[0]->WaitOnServingStatusChange(grpc::StatusCode::OK));
  CheckRpcSendOk(DEBUG_LOCATION, 1, RpcOptions().set_wait_for_ready(true));
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  grpc_core::ConfigVars::Overrides overrides;
  overrides.client_channel_backup_poll_interval_ms = 1;
  overrides.trace =
      "call,channel,client_channel,client_channel_call,client_channel_lb_call,"
      "handshaker";
  grpc_core::ConfigVars::SetOverrides(overrides);
#if TARGET_OS_IPHONE

  grpc_core::SetEnv("grpc_cfstream", "0");
#endif
  grpc_init();
  const auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
