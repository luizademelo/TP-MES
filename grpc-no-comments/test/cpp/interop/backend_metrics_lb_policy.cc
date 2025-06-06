
// Copyright 2023 gRPC authors.

#include "test/cpp/interop/backend_metrics_lb_policy.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/oob_backend_metric.h"

namespace grpc {
namespace testing {

namespace {

using grpc_core::CoreConfiguration;
using grpc_core::LoadBalancingPolicy;
using grpc_core::MakeRefCounted;
using grpc_core::OrphanablePtr;
using grpc_core::RefCountedPtr;

constexpr absl::string_view kBackendMetricsLbPolicyName =
    "test_backend_metrics_load_balancer";
constexpr absl::string_view kMetricsTrackerArgument = "orca_metrics_tracker";

LoadReportTracker::LoadReportEntry BackendMetricDataToOrcaLoadReport(
    const grpc_core::BackendMetricData* backend_metric_data) {
  if (backend_metric_data == nullptr) {
    return std::nullopt;
  }
  TestOrcaReport load_report;
  load_report.set_cpu_utilization(backend_metric_data->cpu_utilization);
  load_report.set_memory_utilization(backend_metric_data->mem_utilization);
  for (const auto& p : backend_metric_data->request_cost) {
    std::string name(p.first);
    (*load_report.mutable_request_cost())[name] = p.second;
  }
  for (const auto& p : backend_metric_data->utilization) {
    std::string name(p.first);
    (*load_report.mutable_utilization())[name] = p.second;
  }
  return load_report;
}

class BackendMetricsLbPolicy : public LoadBalancingPolicy {
 public:
  explicit BackendMetricsLbPolicy(Args args)
      : LoadBalancingPolicy(std::move(args), 2) {
    load_report_tracker_ =
        channel_args().GetPointer<LoadReportTracker>(kMetricsTrackerArgument);
    CHECK_NE(load_report_tracker_, nullptr);
    Args delegate_args;
    delegate_args.work_serializer = work_serializer();
    delegate_args.args = channel_args();
    delegate_args.channel_control_helper =
        std::make_unique<Helper>(RefCountedPtr<BackendMetricsLbPolicy>(this));
    delegate_ =
        CoreConfiguration::Get().lb_policy_registry().CreateLoadBalancingPolicy(
            "pick_first", std::move(delegate_args));
    grpc_pollset_set_add_pollset_set(delegate_->interested_parties(),
                                     interested_parties());
  }

  ~BackendMetricsLbPolicy() override = default;

  absl::string_view name() const override {
    return kBackendMetricsLbPolicyName;
  }

  absl::Status UpdateLocked(UpdateArgs args) override {
    auto config =
        CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
            grpc_core::Json::FromArray({grpc_core::Json::FromObject(
                {{"pick_first", grpc_core::Json::FromObject({})}})}));
    args.config = std::move(config.value());
    return delegate_->UpdateLocked(std::move(args));
  }

  void ExitIdleLocked() override { delegate_->ExitIdleLocked(); }

  void ResetBackoffLocked() override { delegate_->ResetBackoffLocked(); }

 private:
  class Picker : public SubchannelPicker {
   public:
    Picker(RefCountedPtr<SubchannelPicker> delegate_picker,
           LoadReportTracker* load_report_tracker)
        : delegate_picker_(std::move(delegate_picker)),
          load_report_tracker_(load_report_tracker) {}

    PickResult Pick(PickArgs args) override {

      PickResult result = delegate_picker_->Pick(args);

      auto* complete_pick = std::get_if<PickResult::Complete>(&result.result);
      if (complete_pick != nullptr) {
        complete_pick->subchannel_call_tracker =
            std::make_unique<SubchannelCallTracker>(load_report_tracker_);
      }
      return result;
    }

   private:
    RefCountedPtr<SubchannelPicker> delegate_picker_;
    LoadReportTracker* load_report_tracker_;
  };

  class OobMetricWatcher : public grpc_core::OobBackendMetricWatcher {
   public:
    explicit OobMetricWatcher(LoadReportTracker* load_report_tracker)
        : load_report_tracker_(load_report_tracker) {}

   private:
    void OnBackendMetricReport(
        const grpc_core::BackendMetricData& backend_metric_data) override {
      load_report_tracker_->RecordOobLoadReport(backend_metric_data);
    }

    LoadReportTracker* load_report_tracker_;
  };

  class Helper : public ParentOwningDelegatingChannelControlHelper<
                     BackendMetricsLbPolicy> {
   public:
    explicit Helper(RefCountedPtr<BackendMetricsLbPolicy> parent)
        : ParentOwningDelegatingChannelControlHelper(std::move(parent)) {}

    RefCountedPtr<grpc_core::SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const grpc_core::ChannelArgs& per_address_args,
        const grpc_core::ChannelArgs& args) override {
      auto subchannel =
          parent_helper()->CreateSubchannel(address, per_address_args, args);
      subchannel->AddDataWatcher(MakeOobBackendMetricWatcher(
          grpc_core::Duration::Seconds(1),
          std::make_unique<OobMetricWatcher>(parent()->load_report_tracker_)));
      return subchannel;
    }

    void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                     RefCountedPtr<SubchannelPicker> picker) override {
      parent_helper()->UpdateState(
          state, status,
          MakeRefCounted<Picker>(std::move(picker),
                                 parent()->load_report_tracker_));
    }
  };

  class SubchannelCallTracker : public SubchannelCallTrackerInterface {
   public:
    explicit SubchannelCallTracker(LoadReportTracker* load_report_tracker)
        : load_report_tracker_(load_report_tracker) {}

    void Start() override {}

    void Finish(FinishArgs args) override {
      load_report_tracker_->RecordPerRpcLoadReport(
          args.backend_metric_accessor->GetBackendMetricData());
    }

   private:
    LoadReportTracker* load_report_tracker_;
  };

  void ShutdownLocked() override {
    grpc_pollset_set_del_pollset_set(delegate_->interested_parties(),
                                     interested_parties());
    delegate_.reset();
  }

  OrphanablePtr<LoadBalancingPolicy> delegate_;
  LoadReportTracker* load_report_tracker_;
};

class BackendMetricsLbPolicyFactory
    : public grpc_core::LoadBalancingPolicyFactory {
 private:
  class BackendMetricsLbPolicyFactoryConfig
      : public LoadBalancingPolicy::Config {
   private:
    absl::string_view name() const override {
      return kBackendMetricsLbPolicyName;
    }
  };

  absl::string_view name() const override {
    return kBackendMetricsLbPolicyName;
  }

  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return grpc_core::MakeOrphanable<BackendMetricsLbPolicy>(std::move(args));
  }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const grpc_core::Json& ) const override {
    return MakeRefCounted<BackendMetricsLbPolicyFactoryConfig>();
  }
};
}

void RegisterBackendMetricsLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<BackendMetricsLbPolicyFactory>());
}

void LoadReportTracker::RecordPerRpcLoadReport(
    const grpc_core::BackendMetricData* backend_metric_data) {
  grpc_core::MutexLock lock(&load_reports_mu_);
  per_rpc_load_reports_.emplace_back(
      BackendMetricDataToOrcaLoadReport(backend_metric_data));
}

void LoadReportTracker::RecordOobLoadReport(
    const grpc_core::BackendMetricData& oob_metric_data) {
  grpc_core::MutexLock lock(&load_reports_mu_);
  oob_load_reports_.emplace_back(
      *BackendMetricDataToOrcaLoadReport(&oob_metric_data));
  load_reports_cv_.Signal();
}

std::optional<LoadReportTracker::LoadReportEntry>
LoadReportTracker::GetNextLoadReport() {
  grpc_core::MutexLock lock(&load_reports_mu_);
  if (per_rpc_load_reports_.empty()) {
    return std::nullopt;
  }
  auto report = std::move(per_rpc_load_reports_.front());
  per_rpc_load_reports_.pop_front();
  return report;
}

LoadReportTracker::LoadReportEntry LoadReportTracker::WaitForOobLoadReport(
    const std::function<bool(const TestOrcaReport&)>& predicate,
    absl::Duration poll_timeout, size_t max_attempts) {
  grpc_core::MutexLock lock(&load_reports_mu_);

  for (size_t i = 0; i < max_attempts; i++) {
    if (oob_load_reports_.empty()) {
      load_reports_cv_.WaitWithTimeout(&load_reports_mu_, poll_timeout);
      if (oob_load_reports_.empty()) {
        return std::nullopt;
      }
    }
    auto report = std::move(oob_load_reports_.front());
    oob_load_reports_.pop_front();
    if (predicate(report)) {
      VLOG(2) << "Report #" << (i + 1) << " matched";
      return report;
    }
  }
  return std::nullopt;
}

void LoadReportTracker::ResetCollectedLoadReports() {
  grpc_core::MutexLock lock(&load_reports_mu_);
  per_rpc_load_reports_.clear();
  oob_load_reports_.clear();
}

ChannelArguments LoadReportTracker::GetChannelArguments() {
  ChannelArguments arguments;
  arguments.SetPointer(std::string(kMetricsTrackerArgument), this);
  return arguments;
}

}
}
