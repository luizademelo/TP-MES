
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>

#include <array>
#include <memory>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "gtest/gtest.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/load_balancing/lb_policy_test_lib.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class RoundRobinTest : public LoadBalancingPolicyTest {
 protected:
  RoundRobinTest() : LoadBalancingPolicyTest("round_robin") {}
};

TEST_F(RoundRobinTest, Basic) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  EXPECT_EQ(ApplyUpdate(BuildUpdate(kAddresses, nullptr), lb_policy()),
            absl::OkStatus());
  ExpectRoundRobinStartup(kAddresses);
}

TEST_F(RoundRobinTest, AddressUpdates) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  EXPECT_EQ(ApplyUpdate(BuildUpdate(kAddresses, nullptr), lb_policy()),
            absl::OkStatus());
  ExpectRoundRobinStartup(kAddresses);

  EXPECT_EQ(
      ApplyUpdate(BuildUpdate(absl::MakeSpan(kAddresses).first(2), nullptr),
                  lb_policy()),
      absl::OkStatus());
  WaitForRoundRobinListChange(kAddresses, absl::MakeSpan(kAddresses).first(2));

  EXPECT_EQ(
      ApplyUpdate(BuildUpdate(absl::MakeSpan(kAddresses).last(2), nullptr),
                  lb_policy()),
      absl::OkStatus());
  WaitForRoundRobinListChange(absl::MakeSpan(kAddresses).first(2),
                              absl::MakeSpan(kAddresses).last(2));
}

TEST_F(RoundRobinTest, MultipleAddressesPerEndpoint) {
  constexpr std::array<absl::string_view, 2> kEndpoint1Addresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  constexpr std::array<absl::string_view, 2> kEndpoint2Addresses = {
      "ipv4:127.0.0.1:445", "ipv4:127.0.0.1:446"};
  const std::array<EndpointAddresses, 2> kEndpoints = {
      MakeEndpointAddresses(kEndpoint1Addresses),
      MakeEndpointAddresses(kEndpoint2Addresses)};
  EXPECT_EQ(ApplyUpdate(BuildUpdate(kEndpoints, nullptr), lb_policy_.get()),
            absl::OkStatus());

  auto* subchannel1_0 = FindSubchannel(kEndpoint1Addresses[0]);
  ASSERT_NE(subchannel1_0, nullptr) << "Address: " << kEndpoint1Addresses[0];
  auto* subchannel1_1 = FindSubchannel(kEndpoint1Addresses[1]);
  ASSERT_NE(subchannel1_1, nullptr) << "Address: " << kEndpoint1Addresses[1];
  auto* subchannel2_0 = FindSubchannel(kEndpoint2Addresses[0]);
  ASSERT_NE(subchannel2_0, nullptr) << "Address: " << kEndpoint2Addresses[0];
  auto* subchannel2_1 = FindSubchannel(kEndpoint2Addresses[1]);
  ASSERT_NE(subchannel2_1, nullptr) << "Address: " << kEndpoint2Addresses[1];

  EXPECT_TRUE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_TRUE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  ExpectConnectingUpdate();

  subchannel2_0->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                      absl::UnavailableError("ugh"));
  EXPECT_TRUE(subchannel1_1->ConnectionRequested());
  subchannel1_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2_0->SetConnectivityState(GRPC_CHANNEL_READY);
  auto picker = WaitForConnected();
  ExpectRoundRobinPicks(picker.get(), {kEndpoint2Addresses[0]});

  subchannel1_1->SetConnectivityState(GRPC_CHANNEL_READY);
  WaitForRoundRobinListChange({kEndpoint2Addresses[0]},
                              {kEndpoint1Addresses[1], kEndpoint2Addresses[0]});

  EXPECT_FALSE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_FALSE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_IDLE);
  EXPECT_FALSE(subchannel1_0->ConnectionRequested());

  ExpectEndpointAddressChange(kEndpoint1Addresses, 1, 0, [&]() {

    WaitForRoundRobinListChange(
        {kEndpoint1Addresses[1], kEndpoint2Addresses[0]},
        {kEndpoint2Addresses[0]});
  });

  WaitForRoundRobinListChange({kEndpoint2Addresses[0]},
                              {kEndpoint1Addresses[0], kEndpoint2Addresses[0]});

  EXPECT_FALSE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_FALSE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
