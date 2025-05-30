
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/json.h>
#include <stddef.h>

#include <algorithm>
#include <array>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/types/span.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/ext/filters/stateful_session/stateful_session_filter.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/xds/xds_config.h"
#include "src/core/util/json/json.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/xds/grpc/xds_health_status.h"
#include "test/core/load_balancing/lb_policy_test_lib.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {
class XdsOverrideHostTest : public LoadBalancingPolicyTest {
 protected:
  XdsOverrideHostTest()
      : LoadBalancingPolicyTest("xds_override_host_experimental") {}

  void SetUp() override {
    LoadBalancingPolicyTest::SetUp();
    if (!grpc_event_engine::experimental::IsSaneTimerEnvironment()) {
      GTEST_SKIP() << "Needs most EventEngine experiments enabled";
    }
  }

  static RefCountedPtr<const XdsConfig> MakeXdsConfig(
      absl::Span<const absl::string_view> override_host_statuses = {"UNKNOWN",
                                                                    "HEALTHY"},
      std::optional<Duration> connection_idle_timeout = std::nullopt,
      std::string cluster_name = "cluster_name") {
    auto cluster_resource = std::make_shared<XdsClusterResource>();
    for (const absl::string_view host_status : override_host_statuses) {
      cluster_resource->override_host_statuses.Add(
          XdsHealthStatus::FromString(host_status).value());
    }
    if (connection_idle_timeout.has_value()) {
      cluster_resource->connection_idle_timeout = *connection_idle_timeout;
    }
    auto xds_config = MakeRefCounted<XdsConfig>();
    xds_config->clusters[std::move(cluster_name)].emplace(
        std::move(cluster_resource), nullptr, "");
    return xds_config;
  }

  absl::Status UpdateXdsOverrideHostPolicy(
      absl::Span<const EndpointAddresses> endpoints,
      absl::Span<const absl::string_view> override_host_statuses = {"UNKNOWN",
                                                                    "HEALTHY"},
      std::optional<Duration> connection_idle_timeout = std::nullopt,
      std::string cluster_name = "cluster_name",
      std::string child_policy = "round_robin") {
    auto config = MakeConfig(Json::FromArray({Json::FromObject(
        {{"xds_override_host_experimental",
          Json::FromObject(
              {{"clusterName", Json::FromString(cluster_name)},
               {"childPolicy",
                Json::FromArray({Json::FromObject(
                    {{child_policy, Json::FromObject({})}})})}})}})}));
    auto xds_config = MakeXdsConfig(override_host_statuses,
                                    connection_idle_timeout, cluster_name);
    return ApplyUpdate(
        BuildUpdate(endpoints, std::move(config),
                    ChannelArgs().SetObject(std::move(xds_config))),
        lb_policy());
  }

  absl::Status UpdateXdsOverrideHostPolicy(
      absl::Span<const absl::string_view> addresses,
      absl::Span<const absl::string_view> override_host_statuses = {"UNKNOWN",
                                                                    "HEALTHY"},
      std::optional<Duration> connection_idle_timeout = std::nullopt,
      std::string cluster_name = "cluster_name",
      std::string child_policy = "round_robin") {
    return UpdateXdsOverrideHostPolicy(
        MakeEndpointAddressesListFromAddressList(addresses),
        override_host_statuses, connection_idle_timeout,
        std::move(cluster_name), std::move(child_policy));
  }

  RefCountedPtr<LoadBalancingPolicy::SubchannelPicker>
  ExpectStartupWithRoundRobin(absl::Span<const absl::string_view> addresses,
                              SourceLocation location = SourceLocation()) {
    EXPECT_EQ(UpdateXdsOverrideHostPolicy(addresses), absl::OkStatus())
        << location.file() << ":" << location.line();
    return ExpectRoundRobinStartup(addresses, location);
  }

  EndpointAddresses MakeAddressWithHealthStatus(
      absl::string_view address, XdsHealthStatus::HealthStatus status) {
    return EndpointAddresses(
        MakeAddress(address),
        ChannelArgs().Set(GRPC_ARG_XDS_HEALTH_STATUS, status));
  }

  void ApplyUpdateWithHealthStatuses(
      absl::Span<const std::pair<const absl::string_view,
                                 XdsHealthStatus::HealthStatus>>
          addresses_and_statuses,
      absl::Span<const absl::string_view> override_host_status = {"UNKNOWN",
                                                                  "HEALTHY"},
      std::optional<Duration> connection_idle_timeout = std::nullopt) {
    EndpointAddressesList endpoints;
    for (auto address_and_status : addresses_and_statuses) {
      endpoints.push_back(MakeAddressWithHealthStatus(
          address_and_status.first, address_and_status.second));
    }
    EXPECT_EQ(UpdateXdsOverrideHostPolicy(endpoints, override_host_status,
                                          connection_idle_timeout),
              absl::OkStatus());
  }

  struct OverrideHostAttributeStorage {

    std::string address_list;
    XdsOverrideHostAttribute attribute;

    explicit OverrideHostAttributeStorage(std::string addresses)
        : address_list(std::move(addresses)), attribute(address_list) {}
  };

  XdsOverrideHostAttribute* MakeOverrideHostAttribute(
      absl::Span<const absl::string_view> addresses) {
    std::vector<absl::string_view> address_list;
    address_list.reserve(addresses.size());
    for (absl::string_view address : addresses) {
      address_list.emplace_back(absl::StripPrefix(address, "ipv4:"));
    }
    attribute_storage_.emplace_back(
        std::make_unique<OverrideHostAttributeStorage>(
            absl::StrJoin(address_list, ",")));
    return &attribute_storage_.back()->attribute;
  }

  XdsOverrideHostAttribute* MakeOverrideHostAttribute(
      absl::string_view address) {
    const std::array<absl::string_view, 1> addresses = {address};
    return MakeOverrideHostAttribute(addresses);
  }

  void ExpectOverridePicks(
      LoadBalancingPolicy::SubchannelPicker* picker,
      XdsOverrideHostAttribute* attribute, absl::string_view expected,
      absl::Span<const absl::string_view> expected_address_list = {},
      SourceLocation location = SourceLocation()) {
    std::array<absl::string_view, 1> kArray = {expected};
    if (expected_address_list.empty()) expected_address_list = kArray;
    std::vector<absl::string_view> expected_addresses;
    expected_addresses.reserve(expected_address_list.size());
    for (absl::string_view address : expected_address_list) {
      expected_addresses.push_back(absl::StripPrefix(address, "ipv4:"));
    }
    std::string expected_addresses_str = absl::StrJoin(expected_addresses, ",");
    for (size_t i = 0; i < 3; ++i) {
      EXPECT_EQ(ExpectPickComplete(picker, {attribute}, {},
                                   nullptr,
                                   nullptr, location),
                expected)
          << location.file() << ":" << location.line();
      EXPECT_EQ(attribute->actual_address_list(), expected_addresses_str)
          << "  Actual: " << attribute->actual_address_list() << "\n"
          << "Expected: " << expected_addresses_str << "\n"
          << location.file() << ":" << location.line();
    }
  }

  void ExpectRoundRobinPicksWithAttribute(
      LoadBalancingPolicy::SubchannelPicker* picker,
      XdsOverrideHostAttribute* attribute,
      absl::Span<const absl::string_view> expected,
      SourceLocation location = SourceLocation()) {
    std::vector<std::string> actual_picks;
    for (size_t i = 0; i < expected.size(); ++i) {
      auto address =
          ExpectPickComplete(picker, {attribute}, {},
                             nullptr,
                             nullptr, location);
      ASSERT_TRUE(address.has_value())
          << location.file() << ":" << location.line();
      EXPECT_THAT(*address, ::testing::AnyOfArray(expected))
          << location.file() << ":" << location.line();
      EXPECT_EQ(attribute->actual_address_list(),
                absl::StripPrefix(*address, "ipv4:"))
          << "  Actual: " << attribute->actual_address_list() << "\n"
          << "Expected: " << absl::StripPrefix(*address, "ipv4:") << "\n"
          << location.file() << ":" << location.line();
      actual_picks.push_back(std::move(*address));
    }
    EXPECT_TRUE(PicksAreRoundRobin(expected, actual_picks))
        << location.file() << ":" << location.line();
  }

  std::vector<std::unique_ptr<OverrideHostAttributeStorage>> attribute_storage_;
};

TEST_F(XdsOverrideHostTest, DelegatesToChild) {
  ExpectStartupWithRoundRobin(
      {"ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"});
}

TEST_F(XdsOverrideHostTest, NoConfigReportsError) {
  EXPECT_EQ(
      ApplyUpdate(
          BuildUpdate({"ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442"}, nullptr),
          lb_policy()),
      absl::InvalidArgumentError("Missing policy config"));
}

TEST_F(XdsOverrideHostTest, OverrideHost) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);
  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  auto* address0_attribute = MakeOverrideHostAttribute(kAddresses[0]);
  ExpectOverridePicks(picker.get(), address0_attribute, kAddresses[0]);
}

TEST_F(XdsOverrideHostTest, SubchannelNotFound) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);
  auto* attribute = MakeOverrideHostAttribute("no such host");
  ExpectRoundRobinPicksWithAttribute(picker.get(), attribute, kAddresses);
}

TEST_F(XdsOverrideHostTest, SubchannelsComeAndGo) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  EXPECT_EQ(UpdateXdsOverrideHostPolicy({kAddresses[0], kAddresses[2]}),
            absl::OkStatus());
  picker =
      WaitForRoundRobinListChange(kAddresses, {kAddresses[0], kAddresses[2]});

  ExpectRoundRobinPicksWithAttribute(picker.get(), address1_attribute,
                                     {kAddresses[0], kAddresses[2]});

  EXPECT_EQ(UpdateXdsOverrideHostPolicy({kAddresses[1], kAddresses[2]}),
            absl::OkStatus());
  picker = WaitForRoundRobinListChange({kAddresses[0], kAddresses[2]},
                                       {kAddresses[1], kAddresses[2]});

  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
}

TEST_F(XdsOverrideHostTest,
       OverrideIsQueuedInIdleOrConnectingAndFailedInTransientFailure) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  LOG(INFO) << "### subchannel 1 reporting IDLE";
  auto subchannel = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel, nullptr);
  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(subchannel->ConnectionRequested());
  LOG(INFO) << "### expecting re-resolution request";
  ExpectReresolutionRequest();
  LOG(INFO) << "### expecting RR picks to exclude the disconnected subchannel";
  picker =
      WaitForRoundRobinListChange(kAddresses, {kAddresses[0], kAddresses[2]});

  ExpectPickQueued(picker.get(), {address1_attribute});

  LOG(INFO) << "### subchannel 1 reporting CONNECTING";
  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  ExpectPickQueued(picker.get(), {address1_attribute});

  LOG(INFO) << "### subchannel 1 reporting TRANSIENT_FAILURE";
  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::ResourceExhaustedError("Hmmmm"));
  LOG(INFO) << "### expecting re-resolution request";
  ExpectReresolutionRequest();
  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  LOG(INFO) << "### checking that host override is not used";
  ExpectRoundRobinPicksWithAttribute(picker.get(), address1_attribute,
                                     {kAddresses[0], kAddresses[2]});
}

TEST_F(XdsOverrideHostTest, DrainingState) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);

  WaitForWorkSerializerToFlush();

  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  ExpectRoundRobinPicksWithAttribute(picker.get(), address1_attribute,
                                     {kAddresses[0], kAddresses[2]});
}

TEST_F(XdsOverrideHostTest, DrainingSubchannelIsConnecting) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  LOG(INFO) << "### sending update with DRAINING host";
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  auto subchannel = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel, nullptr);
  picker = ExpectState(GRPC_CHANNEL_READY);

  WaitForWorkSerializerToFlush();
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  LOG(INFO) << "### closing connection to DRAINING host";
  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectPickQueued(picker.get(), {address1_attribute});
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  LOG(INFO) << "### subchannel starts reconnecting";
  WaitForWorkSerializerToFlush();
  EXPECT_TRUE(subchannel->ConnectionRequested());
  ExpectQueueEmpty();
  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectPickQueued(picker.get(), {address1_attribute});
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  LOG(INFO) << "### subchannel becomes reconnected";
  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);
  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});
}

TEST_F(XdsOverrideHostTest, DrainingToHealthy) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);

  WaitForWorkSerializerToFlush();
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kHealthy},
                                 {kAddresses[1], XdsHealthStatus::kHealthy},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectRoundRobinPicks(picker.get(), kAddresses);
}

TEST_F(XdsOverrideHostTest, OverrideHostStatus) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto* address0_attribute = MakeOverrideHostAttribute(kAddresses[0]);
  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  auto* address2_attribute = MakeOverrideHostAttribute(kAddresses[2]);
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kHealthy},
                                 {kAddresses[2], XdsHealthStatus::kDraining}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  WaitForWorkSerializerToFlush();
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[1]});
  ExpectOverridePicks(picker.get(), address0_attribute, kAddresses[0]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kHealthy},
                                 {kAddresses[2], XdsHealthStatus::kDraining}},
                                {"HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[1]});
  ExpectRoundRobinPicksWithAttribute(picker.get(), address0_attribute,
                                     {kAddresses[0], kAddresses[1]});
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kHealthy},
                                 {kAddresses[2], XdsHealthStatus::kDraining}},
                                {"UNKNOWN", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[1]});
  ExpectOverridePicks(picker.get(), address0_attribute, kAddresses[0]);
  ExpectRoundRobinPicksWithAttribute(picker.get(), address1_attribute,
                                     {kAddresses[0], kAddresses[1]});
  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kHealthy},
                                 {kAddresses[2], XdsHealthStatus::kDraining}},
                                {"UNKNOWN", "HEALTHY"});
  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[1]});
  ExpectOverridePicks(picker.get(), address0_attribute, kAddresses[0]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectRoundRobinPicksWithAttribute(picker.get(), address2_attribute,
                                     {kAddresses[0], kAddresses[1]});
}

TEST_F(XdsOverrideHostTest, MultipleAddressesPerEndpoint) {
  constexpr std::array<absl::string_view, 2> kEndpoint1Addresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  constexpr std::array<absl::string_view, 2> kEndpoint2Addresses = {
      "ipv4:127.0.0.1:445", "ipv4:127.0.0.1:446"};
  constexpr std::array<absl::string_view, 2> kEndpoint3Addresses = {
      "ipv4:127.0.0.1:447", "ipv4:127.0.0.1:448"};
  const std::array<EndpointAddresses, 3> kEndpoints = {
      MakeEndpointAddresses(kEndpoint1Addresses),
      MakeEndpointAddresses(kEndpoint2Addresses),
      MakeEndpointAddresses(kEndpoint3Addresses)};
  EXPECT_EQ(UpdateXdsOverrideHostPolicy(kEndpoints), absl::OkStatus());
  auto picker = ExpectRoundRobinStartup(kEndpoints);
  ASSERT_NE(picker, nullptr);

  auto* endpoint1_attribute = MakeOverrideHostAttribute(kEndpoint1Addresses);
  ExpectOverridePicks(picker.get(), endpoint1_attribute, kEndpoint1Addresses[0],
                      kEndpoint1Addresses);
  auto* endpoint2_attribute = MakeOverrideHostAttribute(kEndpoint2Addresses);
  ExpectOverridePicks(picker.get(), endpoint2_attribute, kEndpoint2Addresses[0],
                      kEndpoint2Addresses);

  ExpectEndpointAddressChange(kEndpoint1Addresses, 0, 1, [&]() {
    WaitForRoundRobinListChange(
        {kEndpoint1Addresses[0], kEndpoint2Addresses[0],
         kEndpoint3Addresses[0]},
        {kEndpoint2Addresses[0], kEndpoint3Addresses[0]});
  });
  WaitForRoundRobinListChange(
      {kEndpoint2Addresses[0], kEndpoint3Addresses[0]},
      {kEndpoint1Addresses[1], kEndpoint2Addresses[0], kEndpoint3Addresses[0]});

  ExpectOverridePicks(picker.get(), endpoint1_attribute, kEndpoint1Addresses[1],
                      {kEndpoint1Addresses[1], kEndpoint1Addresses[0]});
}

TEST_F(XdsOverrideHostTest, ChildPolicyNeverCreatedSubchannel) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});

  auto picker = ExpectRoundRobinStartup({kAddresses[0], kAddresses[2]});

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  EXPECT_GE(subchannel->NumWatchers(), 1);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  EXPECT_EQ(subchannel2, nullptr);
  auto* subchannel3 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel3, nullptr);
  EXPECT_GE(subchannel3->NumWatchers(), 1);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectPickQueued(picker.get(), {address1_attribute});
  WaitForWorkSerializerToFlush();
  subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);
  EXPECT_EQ(subchannel2->NumWatchers(), 1);

  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  ExpectPickQueued(picker.get(), {address1_attribute});
  WaitForWorkSerializerToFlush();
  EXPECT_TRUE(subchannel2->ConnectionRequested());
  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  ExpectPickQueued(picker.get(), {address1_attribute});

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);

  picker = ExpectState(GRPC_CHANNEL_READY);
  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
}

TEST_F(XdsOverrideHostTest,
       ChildPolicyUnrefsSubchannelNotUsedWithinIdleThreshold) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = ExpectStartupWithRoundRobin(kAddresses);
  ASSERT_NE(picker, nullptr);

  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kHealthy}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"});
  picker = ExpectState(GRPC_CHANNEL_READY);

  WaitForWorkSerializerToFlush();

  ExpectRoundRobinPicks(picker.get(), {kAddresses[0], kAddresses[2]});

  auto* subchannel0 = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel0, nullptr);
  EXPECT_GE(subchannel0->NumWatchers(), 1);
  auto* subchannel1 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel1, nullptr);
  EXPECT_EQ(subchannel1->NumWatchers(), 0);
  auto* subchannel2 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel2, nullptr);
  EXPECT_GE(subchannel2->NumWatchers(), 1);
}

TEST_F(XdsOverrideHostTest, IdleTimer) {
  std::vector<grpc_event_engine::experimental::EventEngine::Duration>
      timer_durations;
  fuzzing_ee_->SetRunAfterDurationCallback(
      [&timer_durations](
          grpc_event_engine::experimental::EventEngine::Duration duration) {
        timer_durations.push_back(duration);
      });
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  LOG(INFO) << "### sending initial update";
  EXPECT_EQ(UpdateXdsOverrideHostPolicy(kAddresses, {"UNKNOWN", "HEALTHY"},
                                        Duration::Minutes(1)),
            absl::OkStatus());

  EXPECT_THAT(timer_durations, ::testing::ElementsAre(Duration::Minutes(1)));
  timer_durations.clear();
  auto picker = ExpectRoundRobinStartup(kAddresses);
  ASSERT_NE(picker, nullptr);

  auto* address1_attribute = MakeOverrideHostAttribute(kAddresses[1]);
  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  auto* address2_attribute = MakeOverrideHostAttribute(kAddresses[2]);
  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);

  LOG(INFO) << "### moving endpoints 1 and 2 to state DRAINING";
  IncrementTimeBy(Duration::Seconds(5));
  ApplyUpdateWithHealthStatuses({{kAddresses[0], XdsHealthStatus::kUnknown},
                                 {kAddresses[1], XdsHealthStatus::kDraining},
                                 {kAddresses[2], XdsHealthStatus::kDraining}},
                                {"UNKNOWN", "HEALTHY", "DRAINING"},
                                Duration::Minutes(1));

  EXPECT_THAT(timer_durations, ::testing::ElementsAre(Duration::Seconds(55)));
  timer_durations.clear();
  picker = ExpectState(GRPC_CHANNEL_READY);

  WaitForWorkSerializerToFlush();

  ExpectRoundRobinPicks(picker.get(), {kAddresses[0]});

  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);
  ExpectOverridePicks(picker.get(), address2_attribute, kAddresses[2]);

  auto* subchannel1 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel1, nullptr);
  EXPECT_EQ(subchannel1->NumWatchers(), 1);
  auto* subchannel2 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel2, nullptr);
  EXPECT_EQ(subchannel2->NumWatchers(), 1);

  IncrementTimeBy(Duration::Seconds(55));
  EXPECT_EQ(subchannel1->NumWatchers(), 1);
  EXPECT_EQ(subchannel2->NumWatchers(), 1);

  EXPECT_THAT(timer_durations, ::testing::ElementsAre(Duration::Seconds(5)));
  timer_durations.clear();

  ExpectOverridePicks(picker.get(), address1_attribute, kAddresses[1]);

  IncrementTimeBy(Duration::Seconds(5));
  EXPECT_EQ(subchannel1->NumWatchers(), 1);
  EXPECT_EQ(subchannel2->NumWatchers(), 0);

  EXPECT_THAT(timer_durations, ::testing::ElementsAre(Duration::Seconds(55)));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
