
// Copyright 2022 gRPC authors.

#include "src/core/load_balancing/pick_first/pick_first.h"

#include <grpc/grpc.h>
#include <grpc/support/json.h>
#include <stddef.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/notification.h"
#include "absl/types/span.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/work_serializer.h"
#include "test/core/load_balancing/lb_policy_test_lib.h"
#include "test/core/test_util/fake_stats_plugin.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

class PickFirstTest : public LoadBalancingPolicyTest {
 protected:
  explicit PickFirstTest(ChannelArgs channel_args = ChannelArgs())
      : LoadBalancingPolicyTest("pick_first", channel_args) {}

  void SetUp() override {
    LoadBalancingPolicyTest::SetUp();
    SetExpectedTimerDuration(std::chrono::milliseconds(250));
  }

  static RefCountedPtr<LoadBalancingPolicy::Config> MakePickFirstConfig(
      std::optional<bool> shuffle_address_list = std::nullopt) {
    return MakeConfig(Json::FromArray({Json::FromObject(
        {{"pick_first",
          shuffle_address_list.has_value()
              ? Json::FromObject({{"shuffleAddressList",
                                   Json::FromBool(*shuffle_address_list)}})
              : Json::FromObject({})}})}));
  }

  void GetOrderAddressesArePicked(
      absl::Span<const absl::string_view> addresses,
      std::vector<absl::string_view>* out_address_order) {
    out_address_order->clear();
    ExitIdle();

    std::map<SubchannelState*, absl::string_view> subchannels;
    for (auto address : addresses) {
      auto* subchannel = FindSubchannel(address);
      ASSERT_NE(subchannel, nullptr);
      subchannels.emplace(subchannel, address);
    }

    while (!subchannels.empty()) {

      SubchannelState* subchannel = nullptr;
      for (const auto& p : subchannels) {
        if (p.first->ConnectionRequested()) {
          out_address_order->push_back(p.second);
          subchannel = p.first;
          break;
        }
      }
      ASSERT_NE(subchannel, nullptr);

      subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

      if (subchannels.size() == addresses.size()) {
        ExpectConnectingUpdate();
      }
      if (subchannels.size() > 1) {

        subchannel->SetConnectivityState(
            GRPC_CHANNEL_TRANSIENT_FAILURE,
            absl::UnavailableError("failed to connect"));
        subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
      } else {

        subchannel->SetConnectivityState(GRPC_CHANNEL_READY);
        auto picker = WaitForConnected();
        ASSERT_NE(picker, nullptr);
        EXPECT_EQ(ExpectPickComplete(picker.get()), out_address_order->back());

        subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
        ExpectReresolutionRequest();

        ExpectState(GRPC_CHANNEL_IDLE);
      }

      subchannels.erase(subchannel);
    }
  }
};

TEST_F(PickFirstTest, FirstAddressWorks) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
}

TEST_F(PickFirstTest, FirstAddressFails) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[1]);
  }
}

TEST_F(PickFirstTest, FlattensEndpointAddressesList) {

  constexpr std::array<absl::string_view, 2> kEndpoint1Addresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  constexpr std::array<absl::string_view, 1> kEndpoint2Addresses = {
      "ipv4:127.0.0.1:445"};
  const std::array<EndpointAddresses, 2> kEndpoints = {
      MakeEndpointAddresses(kEndpoint1Addresses),
      MakeEndpointAddresses(kEndpoint2Addresses)};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kEndpoints, MakePickFirstConfig(false)), lb_policy_.get());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kEndpoint1Addresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kEndpoint1Addresses[1]);
  ASSERT_NE(subchannel2, nullptr);
  auto* subchannel3 = FindSubchannel(kEndpoint2Addresses[0]);
  ASSERT_NE(subchannel3, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());
  EXPECT_FALSE(subchannel3->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel2->ConnectionRequested());
  EXPECT_FALSE(subchannel3->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel3->ConnectionRequested());

  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel3->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kEndpoint2Addresses[0]);
  }
}

TEST_F(PickFirstTest, FirstTwoAddressesInTransientFailureAtStart) {

  constexpr std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445"};
  auto* subchannel = CreateSubchannel(kAddresses[0]);
  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"),
                                   false);
  auto* subchannel2 = CreateSubchannel(kAddresses[1]);
  subchannel2->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                    absl::UnavailableError("failed to connect"),
                                    false);
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel3 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel3, nullptr);

  EXPECT_TRUE(subchannel3->ConnectionRequested());

  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel3->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[2]);
  }
}

TEST_F(PickFirstTest, AllAddressesInTransientFailureAtStart) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  auto* subchannel = CreateSubchannel(kAddresses[0]);
  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"),
                                   false);
  auto* subchannel2 = CreateSubchannel(kAddresses[1]);
  subchannel2->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                    absl::UnavailableError("failed to connect"),
                                    false);
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status, absl::UnavailableError(
                          "failed to connect to all addresses; "
                          "last error: UNAVAILABLE: failed to connect"));
  });

  EXPECT_FALSE(subchannel->ConnectionRequested());
  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
}

TEST_F(PickFirstTest, StaysInTransientFailureAfterAddressListUpdate) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  auto* subchannel = CreateSubchannel(kAddresses[0]);
  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"),
                                   false);
  auto* subchannel2 = CreateSubchannel(kAddresses[1]);
  subchannel2->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                    absl::UnavailableError("failed to connect"),
                                    false);
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status, absl::UnavailableError(
                          "failed to connect to all addresses; "
                          "last error: UNAVAILABLE: failed to connect"));
  });

  EXPECT_FALSE(subchannel->ConnectionRequested());
  EXPECT_FALSE(subchannel2->ConnectionRequested());

  constexpr std::array<absl::string_view, 2> kAddresses2 = {
      kAddresses[0], "ipv4:127.0.0.1:445"};
  status = ApplyUpdate(BuildUpdate(kAddresses2, MakePickFirstConfig(false)),
                       lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel3 = FindSubchannel(kAddresses2[1]);
  ASSERT_NE(subchannel3, nullptr);

  EXPECT_TRUE(subchannel3->ConnectionRequested());

  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel3->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses2[1]);
  }
}

TEST_F(PickFirstTest, ResolverUpdateBeforeLeavingIdle) {
  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  constexpr std::array<absl::string_view, 2> kNewAddresses = {
      "ipv4:127.0.0.1:445", "ipv4:127.0.0.1:446"};

  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
  ExpectReresolutionRequest();
  ExpectState(GRPC_CHANNEL_IDLE);

  absl::Notification notification;
  work_serializer_->Run([&]() {

    work_serializer_->Run([&]() {

      absl::Status status = lb_policy()->UpdateLocked(
          BuildUpdate(kNewAddresses, MakePickFirstConfig(false)));
      EXPECT_TRUE(status.ok()) << status;

      work_serializer_->Run([&]() { notification.Notify(); });
    });

    lb_policy()->ExitIdleLocked();
  });
  while (!notification.HasBeenNotified()) {
    fuzzing_ee_->Tick();
  }

  auto* subchannel3 = FindSubchannel(kNewAddresses[0]);
  ASSERT_NE(subchannel3, nullptr);
  auto* subchannel4 = FindSubchannel(kNewAddresses[1]);
  ASSERT_NE(subchannel4, nullptr);

  EXPECT_TRUE(subchannel3->ConnectionRequested());
  EXPECT_FALSE(subchannel->ConnectionRequested());
  EXPECT_FALSE(subchannel2->ConnectionRequested());
  EXPECT_FALSE(subchannel4->ConnectionRequested());

  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel3->SetConnectivityState(GRPC_CHANNEL_READY);

  picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kNewAddresses[0]);
  }
}

TEST_F(PickFirstTest, HappyEyeballs) {

  constexpr std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);
  auto* subchannel3 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel3, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel2->ConnectionRequested());
  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel3->ConnectionRequested());
  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  IncrementTimeBy(Duration::Milliseconds(250));
  DrainConnectingUpdates();

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
}

TEST_F(PickFirstTest, HappyEyeballsCompletesWithoutSuccess) {

  constexpr std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);
  auto* subchannel3 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel3, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel2->ConnectionRequested());
  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel3->ConnectionRequested());
  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  IncrementTimeBy(Duration::Milliseconds(250));
  DrainConnectingUpdates();

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);

  subchannel3->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));
  ExpectQueueEmpty();

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status, absl::UnavailableError(
                          "failed to connect to all addresses; "
                          "last error: UNAVAILABLE: failed to connect"));
  });

  EXPECT_FALSE(subchannel->ConnectionRequested());
  EXPECT_TRUE(subchannel2->ConnectionRequested());
  EXPECT_FALSE(subchannel3->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(subchannel->ConnectionRequested());
  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));
  EXPECT_FALSE(subchannel->ConnectionRequested());

  subchannel3->SetConnectivityState(GRPC_CHANNEL_IDLE);
  EXPECT_TRUE(subchannel3->ConnectionRequested());
  subchannel3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));
  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel3->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));
  EXPECT_FALSE(subchannel3->ConnectionRequested());
  ExpectReresolutionRequest();
  ExpectTransientFailureUpdate(
      absl::UnavailableError("failed to connect to all addresses; "
                             "last error: UNAVAILABLE: failed to connect"));

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);

  EXPECT_TRUE(subchannel2->ConnectionRequested());
  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[1]);
  }
}

TEST_F(PickFirstTest,
       HappyEyeballsLastSubchannelFailsWhileAnotherIsStillPending) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel2->ConnectionRequested());
  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));

  DrainConnectingUpdates();

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status, absl::UnavailableError(
                          "failed to connect to all addresses; "
                          "last error: UNAVAILABLE: failed to connect"));
  });

  EXPECT_FALSE(subchannel->ConnectionRequested());
  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[1]);
  }
}

TEST_F(PickFirstTest, HappyEyeballsAddressInterleaving) {

  constexpr std::array<absl::string_view, 6> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445",
      "ipv4:127.0.0.1:446", "ipv6:[::1]:444",     "ipv6:[::1]:445"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel_ipv4_1 = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel_ipv4_1, nullptr);
  auto* subchannel_ipv4_2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel_ipv4_2, nullptr);
  auto* subchannel_ipv4_3 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel_ipv4_3, nullptr);
  auto* subchannel_ipv4_4 = FindSubchannel(kAddresses[3]);
  ASSERT_NE(subchannel_ipv4_4, nullptr);
  auto* subchannel_ipv6_1 = FindSubchannel(kAddresses[4]);
  ASSERT_NE(subchannel_ipv6_1, nullptr);
  auto* subchannel_ipv6_2 = FindSubchannel(kAddresses[5]);
  ASSERT_NE(subchannel_ipv6_2, nullptr);

  EXPECT_TRUE(subchannel_ipv4_1->ConnectionRequested());
  subchannel_ipv4_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv6_1->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv6_2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv6_1->ConnectionRequested());
  subchannel_ipv6_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv6_2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_2->ConnectionRequested());
  subchannel_ipv4_2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv6_2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv6_2->ConnectionRequested());
  subchannel_ipv6_2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_3->ConnectionRequested());
  subchannel_ipv4_3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_4->ConnectionRequested());
  subchannel_ipv4_4->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();
}

TEST_F(PickFirstTest,
       HappyEyeballsAddressInterleavingSecondFamilyHasMoreAddresses) {

  constexpr std::array<absl::string_view, 6> kAddresses = {
      "ipv6:[::1]:444",     "ipv6:[::1]:445",     "ipv4:127.0.0.1:443",
      "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445", "ipv4:127.0.0.1:446"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel_ipv6_1 = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel_ipv6_1, nullptr);
  auto* subchannel_ipv6_2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel_ipv6_2, nullptr);
  auto* subchannel_ipv4_1 = FindSubchannel(kAddresses[2]);
  ASSERT_NE(subchannel_ipv4_1, nullptr);
  auto* subchannel_ipv4_2 = FindSubchannel(kAddresses[3]);
  ASSERT_NE(subchannel_ipv4_2, nullptr);
  auto* subchannel_ipv4_3 = FindSubchannel(kAddresses[4]);
  ASSERT_NE(subchannel_ipv4_3, nullptr);
  auto* subchannel_ipv4_4 = FindSubchannel(kAddresses[5]);
  ASSERT_NE(subchannel_ipv4_4, nullptr);

  EXPECT_TRUE(subchannel_ipv6_1->ConnectionRequested());
  subchannel_ipv6_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv6_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_1->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_1->ConnectionRequested());
  subchannel_ipv4_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv6_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv6_2->ConnectionRequested());
  subchannel_ipv6_2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_2->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_2->ConnectionRequested());
  subchannel_ipv4_2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_3->ConnectionRequested());
  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_3->ConnectionRequested());
  subchannel_ipv4_3->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel_ipv4_4->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel_ipv4_4->ConnectionRequested());
  subchannel_ipv4_4->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();
}

TEST_F(PickFirstTest, FirstAddressGoesIdleBeforeSecondOneFails) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));

  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);

  subchannel2->SetConnectivityState(
      GRPC_CHANNEL_TRANSIENT_FAILURE,
      absl::UnavailableError("failed to connect"));

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status, absl::UnavailableError(
                          "failed to connect to all addresses; "
                          "last error: UNAVAILABLE: failed to connect"));
  });

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
}

TEST_F(PickFirstTest, GoesIdleWhenConnectionFailsThenCanReconnect) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);

  ExpectReresolutionRequest();

  ExpectStateAndQueuingPicker(GRPC_CHANNEL_IDLE);

  WaitForWorkSerializerToFlush();
  WaitForWorkSerializerToFlush();
  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
}

TEST_F(PickFirstTest, AddressUpdateRemovedSelectedAddress) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }

  status = ApplyUpdate(BuildUpdate({kAddresses[1]}, MakePickFirstConfig(false)),
                       lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  ExpectReresolutionRequest();

  ExpectStateAndQueuingPicker(GRPC_CHANNEL_IDLE);

  WaitForWorkSerializerToFlush();
  WaitForWorkSerializerToFlush();
  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);

  picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[1]);
  }
}

TEST_F(PickFirstTest, AddressUpdateRetainsSelectedAddress) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }

  status = ApplyUpdate(
      BuildUpdate({kAddresses[1], kAddresses[0]}, MakePickFirstConfig(false)),
      lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  picker = ExpectState(GRPC_CHANNEL_READY);
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[0]);
  }
  EXPECT_FALSE(subchannel2->ConnectionRequested());
}

TEST_F(PickFirstTest, SubchannelNotificationAfterShutdown) {

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel->SetConnectivityState(
      GRPC_CHANNEL_READY, absl::OkStatus(),
      true,
      [&]() {

        IncrementTimeBy(Duration::Milliseconds(250),
                        false);

        lb_policy_.reset();
      });

  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
}

TEST_F(PickFirstTest,
       SubchannelInitiallyReportsTransientFailureButIsIdleForHappyEyeballs) {
  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};

  auto* subchannel2 = CreateSubchannel(kAddresses[1]);
  subchannel2->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                    absl::UnavailableError("failed to connect"),
                                    false);

  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  IncrementTimeBy(Duration::Milliseconds(250));

  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel2->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                    absl::UnavailableError("ugh"));

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("ugh2"));

  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectReresolutionRequest();

  WaitForConnectionFailed([&](const absl::Status& status) {
    EXPECT_EQ(status,
              absl::UnavailableError("failed to connect to all addresses; "
                                     "last error: UNAVAILABLE: ugh2"));
  });
}

TEST_F(PickFirstTest, WithShuffle) {
  constexpr std::array<absl::string_view, 6> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445",
      "ipv4:127.0.0.1:446", "ipv4:127.0.0.1:447", "ipv4:127.0.0.1:448"};

  constexpr size_t kMaxTries = 10;
  std::vector<absl::string_view> addresses_after_update;
  bool shuffled = false;
  for (size_t i = 0; i < kMaxTries; ++i) {
    absl::Status status = ApplyUpdate(
        BuildUpdate(kAddresses, MakePickFirstConfig(true)), lb_policy());
    EXPECT_TRUE(status.ok()) << status;
    GetOrderAddressesArePicked(kAddresses, &addresses_after_update);
    if (absl::MakeConstSpan(addresses_after_update) !=
        absl::MakeConstSpan(kAddresses)) {
      shuffled = true;
      break;
    }
  }
  ASSERT_TRUE(shuffled);

  std::vector<absl::string_view> addresses_on_another_try;
  GetOrderAddressesArePicked(kAddresses, &addresses_on_another_try);
  EXPECT_EQ(addresses_on_another_try, addresses_after_update);
}

TEST_F(PickFirstTest, ShufflingDisabled) {
  constexpr std::array<absl::string_view, 6> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444", "ipv4:127.0.0.1:445",
      "ipv4:127.0.0.1:446", "ipv4:127.0.0.1:447", "ipv4:127.0.0.1:448"};
  constexpr static size_t kMaxAttempts = 5;
  for (size_t attempt = 0; attempt < kMaxAttempts; ++attempt) {
    absl::Status status = ApplyUpdate(
        BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
    EXPECT_TRUE(status.ok()) << status;
    std::vector<absl::string_view> address_order;
    GetOrderAddressesArePicked(kAddresses, &address_order);
    EXPECT_THAT(address_order, ::testing::ElementsAreArray(kAddresses));
  }
}

TEST_F(PickFirstTest, MetricDefinitionDisconnections) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.pick_first.disconnections");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.pick_first.disconnections");
  EXPECT_EQ(descriptor->unit, "{disconnection}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(PickFirstTest, MetricDefinitionConnectionAttemptsSucceeded) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.pick_first.connection_attempts_succeeded");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name,
            "grpc.lb.pick_first.connection_attempts_succeeded");
  EXPECT_EQ(descriptor->unit, "{attempt}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(PickFirstTest, MetricDefinitionConnectionAttemptsFailed) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.pick_first.connection_attempts_failed");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.pick_first.connection_attempts_failed");
  EXPECT_EQ(descriptor->unit, "{attempt}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys, ::testing::ElementsAre());
}

TEST_F(PickFirstTest, MetricValues) {
  const auto kDisconnections =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.pick_first.disconnections")
          .value();
  const auto kConnectionAttemptsSucceeded =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.pick_first.connection_attempts_succeeded")
          .value();
  const auto kConnectionAttemptsFailed =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.pick_first.connection_attempts_failed")
          .value();
  const absl::string_view kLabelValues[] = {target_};
  auto stats_plugin = std::make_shared<FakeStatsPlugin>(
      nullptr, true);
  stats_plugin_group_.AddStatsPlugin(stats_plugin, nullptr);

  constexpr std::array<absl::string_view, 2> kAddresses = {
      "ipv4:127.0.0.1:443", "ipv4:127.0.0.1:444"};
  absl::Status status = ApplyUpdate(
      BuildUpdate(kAddresses, MakePickFirstConfig(false)), lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddresses[0]);
  ASSERT_NE(subchannel, nullptr);
  auto* subchannel2 = FindSubchannel(kAddresses[1]);
  ASSERT_NE(subchannel2, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  EXPECT_FALSE(subchannel2->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                   absl::UnavailableError("failed to connect"));
  EXPECT_THAT(stats_plugin->GetUInt64CounterValue(kConnectionAttemptsFailed,
                                                  kLabelValues, {}),
              ::testing::Optional(1));

  EXPECT_TRUE(subchannel2->ConnectionRequested());

  subchannel2->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2->SetConnectivityState(GRPC_CHANNEL_READY);
  EXPECT_THAT(stats_plugin->GetUInt64CounterValue(kConnectionAttemptsSucceeded,
                                                  kLabelValues, {}),
              ::testing::Optional(1));

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(ExpectPickComplete(picker.get()), kAddresses[1]);
  }

  subchannel2->SetConnectivityState(GRPC_CHANNEL_IDLE);
  ExpectReresolutionRequest();
  ExpectState(GRPC_CHANNEL_IDLE);
  EXPECT_THAT(
      stats_plugin->GetUInt64CounterValue(kDisconnections, kLabelValues, {}),
      ::testing::Optional(1));
}

class PickFirstHealthCheckingEnabledTest : public PickFirstTest {
 protected:
  PickFirstHealthCheckingEnabledTest()
      : PickFirstTest(ChannelArgs().Set(
            GRPC_ARG_INTERNAL_PICK_FIRST_ENABLE_HEALTH_CHECKING, true)) {}
};

TEST_F(PickFirstHealthCheckingEnabledTest, UpdateWithReadyChannel) {
  constexpr absl::string_view kAddress = "ipv4:127.0.0.1:443";
  LoadBalancingPolicy::UpdateArgs update =
      BuildUpdate({kAddress}, MakePickFirstConfig());
  absl::Status status = ApplyUpdate(update, lb_policy());
  EXPECT_TRUE(status.ok()) << status;

  auto* subchannel = FindSubchannel(kAddress);
  ASSERT_NE(subchannel, nullptr);

  EXPECT_TRUE(subchannel->ConnectionRequested());

  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  ExpectConnectingUpdate();

  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  auto picker = WaitForConnected();
  ASSERT_NE(picker, nullptr);
  EXPECT_EQ(ExpectPickComplete(picker.get()), kAddress);

  status =
      ApplyUpdate(BuildUpdate({kAddress}, MakePickFirstConfig()), lb_policy());
  EXPECT_TRUE(status.ok()) << status;
  picker = ExpectState(GRPC_CHANNEL_READY);
  EXPECT_EQ(ExpectPickComplete(picker.get()), kAddress);

  EXPECT_EQ(subchannel->NumWatchers(), 2);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
