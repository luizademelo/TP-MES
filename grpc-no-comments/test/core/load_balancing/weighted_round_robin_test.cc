
// Copyright 2022 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/json.h>
#include <inttypes.h>
#include <stddef.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "absl/types/span.h"
#include "gtest/gtest.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/weighted_target/weighted_target.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/load_balancing/lb_policy_test_lib.h"
#include "test/core/test_util/fake_stats_plugin.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

constexpr absl::string_view kLocalityName = "locality0";

class WeightedRoundRobinTest : public LoadBalancingPolicyTest {
 protected:
  class ConfigBuilder {
   public:
    ConfigBuilder() {

      SetBlackoutPeriod(Duration::Seconds(1));
    }

    ConfigBuilder& SetEnableOobLoadReport(bool value) {
      json_["enableOobLoadReport"] = Json::FromBool(value);
      return *this;
    }
    ConfigBuilder& SetOobReportingPeriod(Duration duration) {
      json_["oobReportingPeriod"] = Json::FromString(duration.ToJsonString());
      return *this;
    }
    ConfigBuilder& SetBlackoutPeriod(Duration duration) {
      json_["blackoutPeriod"] = Json::FromString(duration.ToJsonString());
      return *this;
    }
    ConfigBuilder& SetWeightUpdatePeriod(Duration duration) {
      json_["weightUpdatePeriod"] = Json::FromString(duration.ToJsonString());
      return *this;
    }
    ConfigBuilder& SetWeightExpirationPeriod(Duration duration) {
      json_["weightExpirationPeriod"] =
          Json::FromString(duration.ToJsonString());
      return *this;
    }
    ConfigBuilder& SetErrorUtilizationPenalty(float value) {
      json_["errorUtilizationPenalty"] = Json::FromNumber(value);
      return *this;
    }

    RefCountedPtr<LoadBalancingPolicy::Config> Build() {
      Json config = Json::FromArray({Json::FromObject(
          {{"weighted_round_robin", Json::FromObject(json_)}})});
      LOG(INFO) << "CONFIG: " << JsonDump(config);
      return MakeConfig(config);
    }

   private:
    Json::Object json_;
  };

  WeightedRoundRobinTest()
      : LoadBalancingPolicyTest(
            "weighted_round_robin",
            ChannelArgs().Set(GRPC_ARG_LB_WEIGHTED_TARGET_CHILD,
                              kLocalityName)) {}

  void SetUp() override {
    LoadBalancingPolicyTest::SetUp();
    if (!grpc_event_engine::experimental::IsSaneTimerEnvironment()) {
      GTEST_SKIP() << "Needs most EventEngine experiments enabled";
    }
    SetExpectedTimerDuration(std::chrono::seconds(1));
  }

  RefCountedPtr<LoadBalancingPolicy::SubchannelPicker>
  SendInitialUpdateAndWaitForConnected(
      absl::Span<const absl::string_view> addresses,
      ConfigBuilder config_builder = ConfigBuilder(),
      absl::Span<const absl::string_view> update_addresses = {},
      SourceLocation location = SourceLocation()) {
    if (update_addresses.empty()) update_addresses = addresses;
    EXPECT_EQ(ApplyUpdate(BuildUpdate(update_addresses, config_builder.Build()),
                          lb_policy()),
              absl::OkStatus());

    for (size_t i = 0; i < addresses.size(); ++i) {
      auto* subchannel = FindSubchannel(addresses[i]);
      EXPECT_NE(subchannel, nullptr)
          << addresses[i] << " at " << location.file() << ":"
          << location.line();
      if (subchannel == nullptr) return nullptr;

      EXPECT_TRUE(subchannel->ConnectionRequested())
          << addresses[i] << " at " << location.file() << ":"
          << location.line();

      subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

      if (i == 0) ExpectConnectingUpdate(location);
      subchannel->SetConnectivityState(GRPC_CHANNEL_READY);
    }
    return WaitForConnected(location);
  }

  static std::map<absl::string_view, size_t> MakePickMap(
      absl::Span<const std::string> picks) {
    std::map<absl::string_view, size_t> actual;
    for (const auto& address : picks) {
      ++actual.emplace(address, 0).first->second;
    }
    return actual;
  }

  static std::string PickMapString(
      const std::map<absl::string_view, size_t>& pick_map) {
    return absl::StrJoin(pick_map, ",", absl::PairFormatter("="));
  }

  static BackendMetricData MakeBackendMetricData(double app_utilization,
                                                 double qps, double eps,
                                                 double cpu_utilization = 0) {
    BackendMetricData b;
    b.cpu_utilization = cpu_utilization;
    b.application_utilization = app_utilization;
    b.qps = qps;
    b.eps = eps;
    return b;
  }

  static size_t NumPicksNeeded(const std::map<absl::string_view ,
                                              size_t >& expected) {
    size_t num_picks = 0;
    for (const auto& p : expected) {
      num_picks += p.second;
    }
    return num_picks;
  }

  static void ReportBackendMetrics(
      absl::Span<const std::string> picks,
      const std::vector<
          std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>>&
          subchannel_call_trackers,
      const std::map<absl::string_view , BackendMetricData>&
          backend_metrics) {
    for (size_t i = 0; i < picks.size(); ++i) {
      const auto& address = picks[i];
      auto& subchannel_call_tracker = subchannel_call_trackers[i];
      if (subchannel_call_tracker != nullptr) {
        subchannel_call_tracker->Start();
        std::optional<BackendMetricData> backend_metric_data;
        auto it = backend_metrics.find(address);
        if (it != backend_metrics.end()) {
          backend_metric_data.emplace();
          backend_metric_data->qps = it->second.qps;
          backend_metric_data->eps = it->second.eps;
          backend_metric_data->cpu_utilization = it->second.cpu_utilization;
          backend_metric_data->application_utilization =
              it->second.application_utilization;
        }
        FakeMetadata metadata({});
        FakeBackendMetricAccessor backend_metric_accessor(
            std::move(backend_metric_data));
        LoadBalancingPolicy::SubchannelCallTrackerInterface::FinishArgs args = {
            address, absl::OkStatus(), &metadata, &backend_metric_accessor};
        subchannel_call_tracker->Finish(args);
      }
    }
  }

  void ReportOobBackendMetrics(
      const std::map<absl::string_view , BackendMetricData>&
          backend_metrics) {
    for (const auto& p : backend_metrics) {
      auto* subchannel = FindSubchannel(p.first);
      BackendMetricData backend_metric_data;
      backend_metric_data.qps = p.second.qps;
      backend_metric_data.eps = p.second.eps;
      backend_metric_data.cpu_utilization = p.second.cpu_utilization;
      backend_metric_data.application_utilization =
          p.second.application_utilization;
      subchannel->SendOobBackendMetricReport(backend_metric_data);
    }
  }

  void ExpectWeightedRoundRobinPicks(
      LoadBalancingPolicy::SubchannelPicker* picker,
      const std::map<absl::string_view , BackendMetricData>&
          backend_metrics,
      const std::map<absl::string_view , size_t >&
          expected,
      SourceLocation location = SourceLocation()) {
    std::vector<
        std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>>
        subchannel_call_trackers;
    auto picks = GetCompletePicks(picker, NumPicksNeeded(expected), {},
                                  &subchannel_call_trackers, location);
    ASSERT_TRUE(picks.has_value()) << location.file() << ":" << location.line();
    LOG(INFO) << "PICKS: " << absl::StrJoin(*picks, " ");
    ReportBackendMetrics(*picks, subchannel_call_trackers, backend_metrics);
    auto actual = MakePickMap(*picks);
    LOG(INFO) << "Pick map: " << PickMapString(actual);
    EXPECT_EQ(expected, actual)
        << "Expected: " << PickMapString(expected)
        << "\nActual: " << PickMapString(actual) << "\nat " << location.file()
        << ":" << location.line();
  }

  bool WaitForWeightedRoundRobinPicks(
      RefCountedPtr<LoadBalancingPolicy::SubchannelPicker>* picker,
      const std::map<absl::string_view , BackendMetricData>&
          backend_metrics,
      std::map<absl::string_view , size_t > expected,
      absl::Duration timeout = absl::Seconds(5),
      bool run_timer_callbacks = true,
      SourceLocation location = SourceLocation()) {
    LOG(INFO) << "==> WaitForWeightedRoundRobinPicks(): Expecting "
              << PickMapString(expected);
    size_t num_picks = NumPicksNeeded(expected);
    absl::Time deadline = absl::Now() + timeout;
    while (true) {
      LOG(INFO) << "TOP OF LOOP";

      size_t num_passes = 0;
      for (; num_passes < 3; ++num_passes) {
        LOG(INFO) << "PASS " << num_passes << ": DOING PICKS";
        std::vector<std::unique_ptr<
            LoadBalancingPolicy::SubchannelCallTrackerInterface>>
            subchannel_call_trackers;
        auto picks = GetCompletePicks(picker->get(), num_picks, {},
                                      &subchannel_call_trackers, location);
        EXPECT_TRUE(picks.has_value())
            << location.file() << ":" << location.line();
        if (!picks.has_value()) return false;
        LOG(INFO) << "PICKS: " << absl::StrJoin(*picks, " ");

        ReportBackendMetrics(*picks, subchannel_call_trackers, backend_metrics);

        auto actual = MakePickMap(*picks);
        LOG(INFO) << "Pick map:\nExpected: " << PickMapString(expected)
                  << "\n  Actual: " << PickMapString(actual);
        if (expected != actual) {

          for (const auto& address : *picks) {
            bool found = expected.find(address) != expected.end();
            EXPECT_TRUE(found)
                << "unexpected pick address " << address << " at "
                << location.file() << ":" << location.line();
            if (!found) return false;
          }
          break;
        }

        if (!helper_->QueueEmpty()) break;
      }
      if (num_passes == 3) return true;

      absl::Time now = absl::Now();
      EXPECT_LT(now, deadline) << location.file() << ":" << location.line();
      if (now >= deadline) return false;

      if (!helper_->QueueEmpty()) {
        *picker = ExpectState(GRPC_CHANNEL_READY, absl::OkStatus(), location);
        EXPECT_NE(*picker, nullptr)
            << location.file() << ":" << location.line();
        if (*picker == nullptr) return false;
      } else if (run_timer_callbacks) {
        LOG(INFO) << "running timer callback...";

        IncrementTimeBy(Duration::Seconds(1));
      }
    }
  }
};

TEST_F(WeightedRoundRobinTest, Basic) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(kAddresses);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, CpuUtilWithNoAppUtil) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(kAddresses);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.9)},
       {kAddresses[1],
        MakeBackendMetricData(0,
                              100.0,
                              0.0, 0.3)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.9)},
       {kAddresses[1], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.3)},
       {kAddresses[2], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.3)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, AppUtilOverCpuUtil) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(kAddresses);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0,
                                             0.3)},
       {kAddresses[1],
        MakeBackendMetricData(0.3,
                              100.0,
                              0.0, 0.4)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0,
                                             0.2)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0,
                                             0.6)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0,
                                             0.5)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, Eps) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetErrorUtilizationPenalty(1.0));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.1,
                                             100.0, 50.0)},
       {kAddresses[1], MakeBackendMetricData(0.1,
                                             100.0, 20.0)},
       {kAddresses[2], MakeBackendMetricData(0.1,
                                             100.0, 10.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 2}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, IgnoresDuplicateAddresses) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  const std::array<absl::string_view, 4> kUpdateAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443",
      "ipv4:127.0.0.1:441"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder(), kUpdateAddresses);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, FallsBackToRoundRobinWithoutWeights) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(kAddresses);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 1}, {kAddresses[2], 1}});
}

TEST_F(WeightedRoundRobinTest, OobReporting) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetEnableOobLoadReport(true));
  ASSERT_NE(picker, nullptr);

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  for (const auto& address : kAddresses) {
    auto* subchannel = FindSubchannel(address);
    ASSERT_NE(subchannel, nullptr);
    subchannel->CheckOobReportingPeriod(Duration::Seconds(10));
  }
}

TEST_F(WeightedRoundRobinTest, OobReportingCpuUtilWithNoAppUtil) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetEnableOobLoadReport(true));
  ASSERT_NE(picker, nullptr);

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.9)},
       {kAddresses[1], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.3)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0,
                                             100.0, 0.0,
                                             0.9)},
       {kAddresses[1],
        MakeBackendMetricData(0,
                              100.0,
                              0.0, 0.3)},
       {kAddresses[2],
        MakeBackendMetricData(0,
                              100.0,
                              0.0, 0.3)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  for (const auto& address : kAddresses) {
    auto* subchannel = FindSubchannel(address);
    ASSERT_NE(subchannel, nullptr);
    subchannel->CheckOobReportingPeriod(Duration::Seconds(10));
  }
}

TEST_F(WeightedRoundRobinTest, OobReportingAppUtilOverCpuUtil) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetEnableOobLoadReport(true));
  ASSERT_NE(picker, nullptr);

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0,
                                             0.3)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0,
                                             0.4)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0,
                                             0.2)},
       {kAddresses[1],
        MakeBackendMetricData(0.3,
                              100.0,
                              0.0, 0.6)},
       {kAddresses[2],
        MakeBackendMetricData(0.3,
                              100.0,
                              0.0, 0.5)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  for (const auto& address : kAddresses) {
    auto* subchannel = FindSubchannel(address);
    ASSERT_NE(subchannel, nullptr);
    subchannel->CheckOobReportingPeriod(Duration::Seconds(10));
  }
}

TEST_F(WeightedRoundRobinTest, HonorsOobReportingPeriod) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetEnableOobLoadReport(true).SetOobReportingPeriod(
          Duration::Seconds(5)));
  ASSERT_NE(picker, nullptr);
  ReportOobBackendMetrics(
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}});
  WaitForWeightedRoundRobinPicks(
      &picker, {},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
  for (const auto& address : kAddresses) {
    auto* subchannel = FindSubchannel(address);
    ASSERT_NE(subchannel, nullptr);
    subchannel->CheckOobReportingPeriod(Duration::Seconds(5));
  }
}

TEST_F(WeightedRoundRobinTest, HonorsWeightUpdatePeriod) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  SetExpectedTimerDuration(std::chrono::seconds(2));
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetWeightUpdatePeriod(Duration::Seconds(2)));
  ASSERT_NE(picker, nullptr);
  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, WeightUpdatePeriodLowerBound) {
  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  SetExpectedTimerDuration(std::chrono::milliseconds(100));
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetWeightUpdatePeriod(Duration::Milliseconds(10)));
  ASSERT_NE(picker, nullptr);
  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, WeightExpirationPeriod) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetWeightExpirationPeriod(Duration::Seconds(2)));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  IncrementTimeBy(Duration::Seconds(2));

  ExpectWeightedRoundRobinPicks(
      picker.get(), {},
      {{kAddresses[0], 3}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, BlackoutPeriodAfterWeightExpiration) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetWeightExpirationPeriod(Duration::Seconds(2)));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  IncrementTimeBy(Duration::Seconds(2));

  ExpectWeightedRoundRobinPicks(
      picker.get(), {},
      {{kAddresses[0], 3}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  ExpectWeightedRoundRobinPicks(
      picker.get(),
      {{kAddresses[0], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.9,
                                             100.0, 0.0)}},
      {{kAddresses[0], 3}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  IncrementTimeBy(Duration::Seconds(1));
  ExpectWeightedRoundRobinPicks(
      picker.get(), {},
      {{kAddresses[0], 3}, {kAddresses[1], 3}, {kAddresses[2], 1}});
}

TEST_F(WeightedRoundRobinTest, BlackoutPeriodAfterDisconnect) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetWeightExpirationPeriod(Duration::Seconds(2)));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  auto* subchannel = FindSubchannel(kAddresses[2]);
  subchannel->SetConnectivityState(GRPC_CHANNEL_IDLE);
  ExpectReresolutionRequest();
  EXPECT_TRUE(subchannel->ConnectionRequested());
  subchannel->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  subchannel->SetConnectivityState(GRPC_CHANNEL_READY);

  picker = ExpectState(GRPC_CHANNEL_READY, absl::OkStatus());
  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  IncrementTimeBy(Duration::Seconds(1));
  ExpectWeightedRoundRobinPicks(
      picker.get(),
      {{kAddresses[0], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.9,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});
}

TEST_F(WeightedRoundRobinTest, BlackoutPeriodDoesNotGetResetAfterUpdate) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto config_builder =
      ConfigBuilder().SetWeightExpirationPeriod(Duration::Seconds(2));
  auto picker =
      SendInitialUpdateAndWaitForConnected(kAddresses, config_builder);
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  EXPECT_EQ(
      ApplyUpdate(BuildUpdate(kAddresses, config_builder.Build()), lb_policy()),
      absl::OkStatus());

  picker = ExpectState(GRPC_CHANNEL_READY, absl::OkStatus());
  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}},
      absl::Seconds(5), false);
}

TEST_F(WeightedRoundRobinTest, ZeroErrorUtilPenalty) {

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses, ConfigBuilder().SetErrorUtilizationPenalty(0.0));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.1,
                                             100.0, 50.0)},
       {kAddresses[1], MakeBackendMetricData(0.1,
                                             100.0, 20.0)},
       {kAddresses[2], MakeBackendMetricData(0.1,
                                             100.0, 10.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 1}, {kAddresses[2], 1}});
}

TEST_F(WeightedRoundRobinTest, MultipleAddressesPerEndpoint) {

  SetExpectedTimerDuration(std::nullopt);
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
  EXPECT_EQ(ApplyUpdate(BuildUpdate(kEndpoints, ConfigBuilder().Build()),
                        lb_policy_.get()),
            absl::OkStatus());

  auto* subchannel1_0 = FindSubchannel(kEndpoint1Addresses[0]);
  ASSERT_NE(subchannel1_0, nullptr) << "Address: " << kEndpoint1Addresses[0];
  auto* subchannel1_1 = FindSubchannel(kEndpoint1Addresses[1]);
  ASSERT_NE(subchannel1_1, nullptr) << "Address: " << kEndpoint1Addresses[1];
  auto* subchannel2_0 = FindSubchannel(kEndpoint2Addresses[0]);
  ASSERT_NE(subchannel2_0, nullptr) << "Address: " << kEndpoint2Addresses[0];
  auto* subchannel2_1 = FindSubchannel(kEndpoint2Addresses[1]);
  ASSERT_NE(subchannel2_1, nullptr) << "Address: " << kEndpoint2Addresses[1];
  auto* subchannel3_0 = FindSubchannel(kEndpoint3Addresses[0]);
  ASSERT_NE(subchannel3_0, nullptr) << "Address: " << kEndpoint3Addresses[0];
  auto* subchannel3_1 = FindSubchannel(kEndpoint3Addresses[1]);
  ASSERT_NE(subchannel3_1, nullptr) << "Address: " << kEndpoint3Addresses[1];

  EXPECT_TRUE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_TRUE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());
  EXPECT_TRUE(subchannel3_0->ConnectionRequested());
  EXPECT_FALSE(subchannel3_1->ConnectionRequested());

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_CONNECTING);
  ExpectConnectingUpdate();

  subchannel2_0->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel3_0->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_TRANSIENT_FAILURE,
                                      absl::UnavailableError("ugh"));
  EXPECT_TRUE(subchannel1_1->ConnectionRequested());
  subchannel1_1->SetConnectivityState(GRPC_CHANNEL_CONNECTING);

  subchannel2_0->SetConnectivityState(GRPC_CHANNEL_READY);
  auto picker = WaitForConnected();
  ExpectRoundRobinPicks(picker.get(), {kEndpoint2Addresses[0]});

  subchannel3_0->SetConnectivityState(GRPC_CHANNEL_READY);
  picker = WaitForRoundRobinListChange(
      {kEndpoint2Addresses[0]},
      {kEndpoint2Addresses[0], kEndpoint3Addresses[0]});

  subchannel1_1->SetConnectivityState(GRPC_CHANNEL_READY);
  picker = WaitForRoundRobinListChange(
      {kEndpoint2Addresses[0], kEndpoint3Addresses[0]},
      {kEndpoint1Addresses[1], kEndpoint2Addresses[0], kEndpoint3Addresses[0]});

  EXPECT_FALSE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_FALSE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());
  EXPECT_FALSE(subchannel3_0->ConnectionRequested());
  EXPECT_FALSE(subchannel3_1->ConnectionRequested());

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kEndpoint1Addresses[1],
        MakeBackendMetricData(0.3, 100.0,
                              0.0)},
       {kEndpoint2Addresses[0],
        MakeBackendMetricData(0.9, 100.0,
                              0.0)},
       {kEndpoint3Addresses[0],
        MakeBackendMetricData(0.3, 100.0,
                              0.0)}},
      {{kEndpoint1Addresses[1], 3},
       {kEndpoint2Addresses[0], 1},
       {kEndpoint3Addresses[0], 3}});

  subchannel1_0->SetConnectivityState(GRPC_CHANNEL_IDLE);
  EXPECT_FALSE(subchannel1_0->ConnectionRequested());

  ExpectEndpointAddressChange(
      kEndpoint1Addresses, 1, 0,

      [&]() {
        picker = ExpectState(GRPC_CHANNEL_READY);
        WaitForWeightedRoundRobinPicks(
            &picker,
            {{kEndpoint2Addresses[0],
              MakeBackendMetricData(0.9, 100.0,
                                    0.0)},
             {kEndpoint3Addresses[0],
              MakeBackendMetricData(0.3, 100.0,
                                    0.0)}},
            {{kEndpoint2Addresses[0], 1}, {kEndpoint3Addresses[0], 3}});
      });

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kEndpoint1Addresses[0],
        MakeBackendMetricData(0.3, 100.0,
                              0.0)},
       {kEndpoint2Addresses[0],
        MakeBackendMetricData(0.9, 100.0,
                              0.0)},
       {kEndpoint3Addresses[0],
        MakeBackendMetricData(0.3, 100.0,
                              0.0)}},
      {{kEndpoint1Addresses[0], 3},
       {kEndpoint2Addresses[0], 1},
       {kEndpoint3Addresses[0], 3}});

  EXPECT_FALSE(subchannel1_0->ConnectionRequested());
  EXPECT_FALSE(subchannel1_1->ConnectionRequested());
  EXPECT_FALSE(subchannel2_0->ConnectionRequested());
  EXPECT_FALSE(subchannel2_1->ConnectionRequested());
  EXPECT_FALSE(subchannel3_0->ConnectionRequested());
  EXPECT_FALSE(subchannel3_1->ConnectionRequested());
}

TEST_F(WeightedRoundRobinTest, MetricDefinitionRrFallback) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.wrr.rr_fallback");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.wrr.rr_fallback");
  EXPECT_EQ(descriptor->unit, "{update}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys,
              ::testing::ElementsAre("grpc.lb.locality"));
}

TEST_F(WeightedRoundRobinTest, MetricDefinitionEndpointWeightNotYetUsable) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.wrr.endpoint_weight_not_yet_usable");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.wrr.endpoint_weight_not_yet_usable");
  EXPECT_EQ(descriptor->unit, "{endpoint}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys,
              ::testing::ElementsAre("grpc.lb.locality"));
}

TEST_F(WeightedRoundRobinTest, MetricDefinitionEndpointWeightStale) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.wrr.endpoint_weight_stale");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kUInt64);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kCounter);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.wrr.endpoint_weight_stale");
  EXPECT_EQ(descriptor->unit, "{endpoint}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys,
              ::testing::ElementsAre("grpc.lb.locality"));
}

TEST_F(WeightedRoundRobinTest, MetricDefinitionEndpointWeights) {
  const auto* descriptor =
      GlobalInstrumentsRegistryTestPeer::FindMetricDescriptorByName(
          "grpc.lb.wrr.endpoint_weights");
  ASSERT_NE(descriptor, nullptr);
  EXPECT_EQ(descriptor->value_type,
            GlobalInstrumentsRegistry::ValueType::kDouble);
  EXPECT_EQ(descriptor->instrument_type,
            GlobalInstrumentsRegistry::InstrumentType::kHistogram);
  EXPECT_EQ(descriptor->enable_by_default, false);
  EXPECT_EQ(descriptor->name, "grpc.lb.wrr.endpoint_weights");
  EXPECT_EQ(descriptor->unit, "{weight}");
  EXPECT_THAT(descriptor->label_keys, ::testing::ElementsAre("grpc.target"));
  EXPECT_THAT(descriptor->optional_label_keys,
              ::testing::ElementsAre("grpc.lb.locality"));
}

TEST_F(WeightedRoundRobinTest, MetricValues) {
  const auto kRrFallback =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.wrr.rr_fallback")
          .value();
  const auto kEndpointWeightNotYetUsable =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.wrr.endpoint_weight_not_yet_usable")
          .value();
  const auto kEndpointWeightStale =
      GlobalInstrumentsRegistryTestPeer::FindUInt64CounterHandleByName(
          "grpc.lb.wrr.endpoint_weight_stale")
          .value();
  const auto kEndpointWeights =
      GlobalInstrumentsRegistryTestPeer::FindDoubleHistogramHandleByName(
          "grpc.lb.wrr.endpoint_weights")
          .value();
  const absl::string_view kLabelValues[] = {target_};
  const absl::string_view kOptionalLabelValues[] = {kLocalityName};
  auto stats_plugin = std::make_shared<FakeStatsPlugin>(
      nullptr, true);
  stats_plugin_group_.AddStatsPlugin(stats_plugin, nullptr);

  const std::array<absl::string_view, 3> kAddresses = {
      "ipv4:127.0.0.1:441", "ipv4:127.0.0.1:442", "ipv4:127.0.0.1:443"};
  auto picker = SendInitialUpdateAndWaitForConnected(
      kAddresses,
      ConfigBuilder().SetWeightExpirationPeriod(Duration::Seconds(2)));
  ASSERT_NE(picker, nullptr);

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 2}});

  WaitForWeightedRoundRobinPicks(
      &picker,
      {{kAddresses[0], MakeBackendMetricData(0.9,
                                             100.0, 0.0)},
       {kAddresses[1], MakeBackendMetricData(0.3,
                                             100.0, 0.0)},
       {kAddresses[2], MakeBackendMetricData(0.3,
                                             100.0, 0.0)}},
      {{kAddresses[0], 1}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  EXPECT_THAT(stats_plugin->GetDoubleHistogramValue(
                  kEndpointWeights, kLabelValues, kOptionalLabelValues),
              ::testing::Optional(::testing::ElementsAre(

                  0,

                  0,

                  0, 0,

                  0, 0,

                  0, 0, 0,

                  ::testing::DoubleNear(111.111115, 0.000001),
                  ::testing::DoubleNear(333.333344, 0.000001), 0,

                  ::testing::DoubleNear(111.111115, 0.000001),
                  ::testing::DoubleNear(333.333344, 0.000001),
                  ::testing::DoubleNear(333.333344, 0.000001))));

  EXPECT_THAT(stats_plugin->GetUInt64CounterValue(kRrFallback, kLabelValues,
                                                  kOptionalLabelValues),
              ::testing::Optional(5));

  EXPECT_THAT(
      stats_plugin->GetUInt64CounterValue(kEndpointWeightNotYetUsable,
                                          kLabelValues, kOptionalLabelValues),
      ::testing::Optional(10));

  EXPECT_THAT(stats_plugin->GetUInt64CounterValue(
                  kEndpointWeightStale, kLabelValues, kOptionalLabelValues),
              ::testing::Optional(0));

  LOG(INFO) << "advancing time to trigger staleness...";
  IncrementTimeBy(Duration::Seconds(2));

  ExpectWeightedRoundRobinPicks(
      picker.get(), {},
      {{kAddresses[0], 3}, {kAddresses[1], 3}, {kAddresses[2], 3}});

  EXPECT_THAT(stats_plugin->GetUInt64CounterValue(
                  kEndpointWeightStale, kLabelValues, kOptionalLabelValues),
              ::testing::Optional(3));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  return RUN_ALL_TESTS();
}
