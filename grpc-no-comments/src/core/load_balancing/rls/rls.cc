
// Copyright 2020 gRPC authors.

#include "src/core/load_balancing/rls/rls.h"

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/hash/hash.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/backoff.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/match.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/upb_utils.h"
#include "src/core/util/uuid_v4.h"
#include "src/core/util/validation_errors.h"
#include "src/core/util/work_serializer.h"
#include "src/proto/grpc/lookup/v1/rls.upb.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"

using ::grpc_event_engine::experimental::EventEngine;

namespace grpc_core {

namespace {

constexpr absl::string_view kMetricLabelRlsServerTarget =
    "grpc.lb.rls.server_target";
constexpr absl::string_view kMetricLabelRlsInstanceUuid =
    "grpc.lb.rls.instance_uuid";
constexpr absl::string_view kMetricRlsDataPlaneTarget =
    "grpc.lb.rls.data_plane_target";
constexpr absl::string_view kMetricLabelPickResult = "grpc.lb.pick_result";

const auto kMetricCacheSize =
    GlobalInstrumentsRegistry::RegisterCallbackInt64Gauge(
        "grpc.lb.rls.cache_size", "EXPERIMENTAL.  Size of the RLS cache.", "By",
        false)
        .Labels(kMetricLabelTarget, kMetricLabelRlsServerTarget,
                kMetricLabelRlsInstanceUuid)
        .Build();

const auto kMetricCacheEntries =
    GlobalInstrumentsRegistry::RegisterCallbackInt64Gauge(
        "grpc.lb.rls.cache_entries",
        "EXPERIMENTAL.  Number of entries in the RLS cache.", "{entry}", false)
        .Labels(kMetricLabelTarget, kMetricLabelRlsServerTarget,
                kMetricLabelRlsInstanceUuid)
        .Build();

const auto kMetricDefaultTargetPicks =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.rls.default_target_picks",
        "EXPERIMENTAL.  Number of LB picks sent to the default target.",
        "{pick}", false)
        .Labels(kMetricLabelTarget, kMetricLabelRlsServerTarget,
                kMetricRlsDataPlaneTarget, kMetricLabelPickResult)
        .Build();

const auto kMetricTargetPicks =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.rls.target_picks",
        "EXPERIMENTAL.  Number of LB picks sent to each RLS target.  Note that "
        "if the default target is also returned by the RLS server, RPCs sent "
        "to that target from the cache will be counted in this metric, not "
        "in grpc.rls.default_target_picks.",
        "{pick}", false)
        .Labels(kMetricLabelTarget, kMetricLabelRlsServerTarget,
                kMetricRlsDataPlaneTarget, kMetricLabelPickResult)
        .Build();

const auto kMetricFailedPicks =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.rls.failed_picks",
        "EXPERIMENTAL.  Number of LB picks failed due to either a failed RLS "
        "request or the RLS channel being throttled.",
        "{pick}", false)
        .Labels(kMetricLabelTarget, kMetricLabelRlsServerTarget)
        .Build();

const char kGrpc[] = "grpc";
const char* kRlsRequestPath = "/grpc.lookup.v1.RouteLookupService/RouteLookup";
const char* kFakeTargetFieldValue = "fake_target_field_value";
const char* kRlsHeaderKey = "x-google-rls-data";

const Duration kMinExpirationTime = Duration::Seconds(5);
const Duration kCacheBackoffInitial = Duration::Seconds(1);
const double kCacheBackoffMultiplier = 1.6;
const double kCacheBackoffJitter = 0.2;
const Duration kCacheBackoffMax = Duration::Minutes(2);
const Duration kDefaultThrottleWindowSize = Duration::Seconds(30);
const double kDefaultThrottleRatioForSuccesses = 2.0;
const int kDefaultThrottlePadding = 8;
const Duration kCacheCleanupTimerInterval = Duration::Minutes(1);
const int64_t kMaxCacheSizeBytes = 5 * 1024 * 1024;

class RlsLb final : public LoadBalancingPolicy {
 public:
  explicit RlsLb(Args args);

  absl::string_view name() const override { return RlsLbConfig::Name(); }
  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:

  struct RequestKey {
    std::map<std::string, std::string> key_map;

    bool operator==(const RequestKey& rhs) const {
      return key_map == rhs.key_map;
    }

    template <typename H>
    friend H AbslHashValue(H h, const RequestKey& key) {
      std::hash<std::string> string_hasher;
      for (auto& [key, value] : key.key_map) {
        h = H::combine(std::move(h), string_hasher(key), string_hasher(value));
      }
      return h;
    }

    size_t Size() const {
      size_t size = sizeof(RequestKey);
      for (auto& [key, value] : key_map) {
        size += key.length() + value.length();
      }
      return size;
    }

    std::string ToString() const {
      return absl::StrCat(
          "{", absl::StrJoin(key_map, ",", absl::PairFormatter("=")), "}");
    }
  };

  struct ResponseInfo {
    absl::Status status;
    std::vector<std::string> targets;
    grpc_event_engine::experimental::Slice header_data;

    std::string ToString() const {
      return absl::StrFormat("{status=%s, targets=[%s], header_data=\"%s\"}",
                             status.ToString(), absl::StrJoin(targets, ","),
                             header_data.as_string_view());
    }
  };

  class ChildPolicyWrapper final : public DualRefCounted<ChildPolicyWrapper> {
   public:
    ChildPolicyWrapper(RefCountedPtr<RlsLb> lb_policy, std::string target);

    const std::string& target() const { return target_; }

    PickResult Pick(PickArgs args) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return picker_->Pick(args);
    }

    void StartUpdate(OrphanablePtr<ChildPolicyHandler>* child_policy_to_delete)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);
    absl::Status MaybeFinishUpdate() ABSL_LOCKS_EXCLUDED(&RlsLb::mu_);

    void ExitIdleLocked() {
      if (child_policy_ != nullptr) child_policy_->ExitIdleLocked();
    }

    void ResetBackoffLocked() {
      if (child_policy_ != nullptr) child_policy_->ResetBackoffLocked();
    }

    grpc_connectivity_state connectivity_state() const
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return connectivity_state_;
    }

   private:

    class ChildPolicyHelper final : public DelegatingChannelControlHelper {
     public:
      explicit ChildPolicyHelper(WeakRefCountedPtr<ChildPolicyWrapper> wrapper)
          : wrapper_(std::move(wrapper)) {}
      ~ChildPolicyHelper() override {
        wrapper_.reset(DEBUG_LOCATION, "ChildPolicyHelper");
      }

      void UpdateState(grpc_connectivity_state state,
                       const absl::Status& status,
                       RefCountedPtr<SubchannelPicker> picker) override;

     private:
      ChannelControlHelper* parent_helper() const override {
        return wrapper_->lb_policy_->channel_control_helper();
      }

      WeakRefCountedPtr<ChildPolicyWrapper> wrapper_;
    };

    // Note: We are forced to disable lock analysis here because

    void Orphaned() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

    RefCountedPtr<RlsLb> lb_policy_;
    std::string target_;

    bool is_shutdown_ = false;

    OrphanablePtr<ChildPolicyHandler> child_policy_;
    RefCountedPtr<LoadBalancingPolicy::Config> pending_config_;

    grpc_connectivity_state connectivity_state_ ABSL_GUARDED_BY(&RlsLb::mu_) =
        GRPC_CHANNEL_CONNECTING;
    RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker_
        ABSL_GUARDED_BY(&RlsLb::mu_);
  };

  class Picker final : public LoadBalancingPolicy::SubchannelPicker {
   public:
    explicit Picker(RefCountedPtr<RlsLb> lb_policy);

    PickResult Pick(PickArgs args) override;

   private:
    PickResult PickFromDefaultTargetOrFail(const char* reason, PickArgs args,
                                           absl::Status status)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    RefCountedPtr<RlsLb> lb_policy_;
    RefCountedPtr<RlsLbConfig> config_;
    RefCountedPtr<ChildPolicyWrapper> default_child_policy_;
  };

  class Cache final {
   public:
    using Iterator = std::list<RequestKey>::iterator;

    class Entry final : public InternallyRefCounted<Entry> {
     public:
      Entry(RefCountedPtr<RlsLb> lb_policy, const RequestKey& key);

      // Note: We are forced to disable lock analysis here because

      void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

      const absl::Status& status() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return status_;
      }
      Timestamp backoff_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return backoff_time_;
      }
      Timestamp backoff_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return backoff_expiration_time_;
      }
      Timestamp data_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return data_expiration_time_;
      }
      const grpc_event_engine::experimental::Slice& header_data() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return header_data_;
      }
      Timestamp stale_time() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return stale_time_;
      }
      Timestamp min_expiration_time() const
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return min_expiration_time_;
      }

      std::unique_ptr<BackOff> TakeBackoffState()
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        return std::move(backoff_state_);
      }

      size_t Size() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      PickResult Pick(PickArgs args, absl::string_view lookup_service)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      void ResetBackoff() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      bool ShouldRemove() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      bool CanEvict() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      std::vector<ChildPolicyWrapper*> OnRlsResponseLocked(
          ResponseInfo response, std::unique_ptr<BackOff> backoff_state,
          OrphanablePtr<ChildPolicyHandler>* child_policy_to_delete)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      void MarkUsed() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      void TakeChildPolicyWrappers(
          std::vector<RefCountedPtr<ChildPolicyWrapper>>* child_policy_wrappers)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
        child_policy_wrappers->insert(
            child_policy_wrappers->end(),
            std::make_move_iterator(child_policy_wrappers_.begin()),
            std::make_move_iterator(child_policy_wrappers_.end()));
        child_policy_wrappers_.clear();
      }

     private:
      class BackoffTimer final : public InternallyRefCounted<BackoffTimer> {
       public:
        BackoffTimer(RefCountedPtr<Entry> entry, Duration delay);

        // Note: We are forced to disable lock analysis here because

        void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

       private:
        void OnBackoffTimerLocked();

        RefCountedPtr<Entry> entry_;
        std::optional<EventEngine::TaskHandle> backoff_timer_task_handle_
            ABSL_GUARDED_BY(&RlsLb::mu_);
      };

      RefCountedPtr<RlsLb> lb_policy_;

      bool is_shutdown_ ABSL_GUARDED_BY(&RlsLb::mu_) = false;

      absl::Status status_ ABSL_GUARDED_BY(&RlsLb::mu_);
      std::unique_ptr<BackOff> backoff_state_ ABSL_GUARDED_BY(&RlsLb::mu_);
      Timestamp backoff_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      Timestamp backoff_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      OrphanablePtr<BackoffTimer> backoff_timer_;

      std::vector<RefCountedPtr<ChildPolicyWrapper>> child_policy_wrappers_
          ABSL_GUARDED_BY(&RlsLb::mu_);
      grpc_event_engine::experimental::Slice header_data_
          ABSL_GUARDED_BY(&RlsLb::mu_);
      Timestamp data_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_) =
          Timestamp::InfPast();
      Timestamp stale_time_ ABSL_GUARDED_BY(&RlsLb::mu_) = Timestamp::InfPast();

      Timestamp min_expiration_time_ ABSL_GUARDED_BY(&RlsLb::mu_);
      Cache::Iterator lru_iterator_ ABSL_GUARDED_BY(&RlsLb::mu_);
    };

    explicit Cache(RlsLb* lb_policy);

    Entry* Find(const RequestKey& key)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    Entry* FindOrInsert(const RequestKey& key,
                        std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                            child_policy_wrappers_to_delete)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    void Resize(size_t bytes, std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                                  child_policy_wrappers_to_delete)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    void ResetAllBackoff() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    GRPC_MUST_USE_RESULT std::vector<RefCountedPtr<ChildPolicyWrapper>>
    Shutdown() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    void ReportMetricsLocked(CallbackMetricReporter& reporter)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

   private:

    void StartCleanupTimer() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    void OnCleanupTimer();

    static size_t EntrySizeForKey(const RequestKey& key);

    void MaybeShrinkSize(size_t bytes,
                         std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                             child_policy_wrappers_to_delete)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    RlsLb* lb_policy_;

    size_t size_limit_ ABSL_GUARDED_BY(&RlsLb::mu_) = 0;
    size_t size_ ABSL_GUARDED_BY(&RlsLb::mu_) = 0;

    std::list<RequestKey> lru_list_ ABSL_GUARDED_BY(&RlsLb::mu_);
    std::unordered_map<RequestKey, OrphanablePtr<Entry>, absl::Hash<RequestKey>>
        map_ ABSL_GUARDED_BY(&RlsLb::mu_);
    std::optional<EventEngine::TaskHandle> cleanup_timer_handle_;
  };

  class RlsChannel final : public InternallyRefCounted<RlsChannel> {
   public:
    explicit RlsChannel(RefCountedPtr<RlsLb> lb_policy);

    void Orphan() override;

    void StartRlsCall(const RequestKey& key, Cache::Entry* stale_entry)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    void ReportResponseLocked(bool response_succeeded)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

    bool ShouldThrottle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
      return throttle_.ShouldThrottle();
    }

    void ResetBackoff();

    Channel* channel() const { return channel_.get(); }

   private:

    class StateWatcher final : public AsyncConnectivityStateWatcherInterface {
     public:
      explicit StateWatcher(RefCountedPtr<RlsChannel> rls_channel)
          : AsyncConnectivityStateWatcherInterface(
                rls_channel->lb_policy_->work_serializer()),
            rls_channel_(std::move(rls_channel)) {}

     private:
      void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                     const absl::Status& status) override;

      RefCountedPtr<RlsChannel> rls_channel_;
      bool was_transient_failure_ = false;
    };

    class Throttle final {
     public:
      explicit Throttle(
          Duration window_size = kDefaultThrottleWindowSize,
          float ratio_for_successes = kDefaultThrottleRatioForSuccesses,
          int padding = kDefaultThrottlePadding)
          : window_size_(window_size),
            ratio_for_successes_(ratio_for_successes),
            padding_(padding) {}

      bool ShouldThrottle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

      void RegisterResponse(bool success)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_);

     private:
      Duration window_size_;
      double ratio_for_successes_;
      int padding_;
      std::mt19937 rng_{std::random_device()()};

      std::deque<Timestamp> requests_ ABSL_GUARDED_BY(&RlsLb::mu_);

      std::deque<Timestamp> failures_ ABSL_GUARDED_BY(&RlsLb::mu_);
    };

    RefCountedPtr<RlsLb> lb_policy_;
    bool is_shutdown_ = false;

    RefCountedPtr<Channel> channel_;
    RefCountedPtr<channelz::ChannelNode> parent_channelz_node_;
    StateWatcher* watcher_ = nullptr;
    Throttle throttle_ ABSL_GUARDED_BY(&RlsLb::mu_);
  };

  class RlsRequest final : public InternallyRefCounted<RlsRequest> {
   public:

    RlsRequest(RefCountedPtr<RlsLb> lb_policy, RlsLb::RequestKey key,
               RefCountedPtr<RlsChannel> rls_channel,
               std::unique_ptr<BackOff> backoff_state,
               grpc_lookup_v1_RouteLookupRequest_Reason reason,
               grpc_event_engine::experimental::Slice stale_header_data);
    ~RlsRequest() override;

    void Orphan() override;

   private:

    static void StartCall(void* arg, grpc_error_handle error);

    void StartCallLocked();

    static void OnRlsCallComplete(void* arg, grpc_error_handle error);

    void OnRlsCallCompleteLocked(grpc_error_handle error);

    grpc_byte_buffer* MakeRequestProto();
    ResponseInfo ParseResponseProto();

    RefCountedPtr<RlsLb> lb_policy_;
    RlsLb::RequestKey key_;
    RefCountedPtr<RlsChannel> rls_channel_;
    std::unique_ptr<BackOff> backoff_state_;
    grpc_lookup_v1_RouteLookupRequest_Reason reason_;
    grpc_event_engine::experimental::Slice stale_header_data_;

    Timestamp deadline_;
    grpc_closure call_start_cb_;
    grpc_closure call_complete_cb_;
    grpc_call* call_ = nullptr;
    grpc_byte_buffer* send_message_ = nullptr;
    grpc_metadata_array recv_initial_metadata_;
    grpc_byte_buffer* recv_message_ = nullptr;
    grpc_metadata_array recv_trailing_metadata_;
    grpc_status_code status_recv_;
    grpc_slice status_details_recv_;
  };

  void ShutdownLocked() override;

  void UpdatePickerAsync();

  void UpdatePickerLocked() ABSL_LOCKS_EXCLUDED(&mu_);

  template <typename HandleType>
  void MaybeExportPickCount(HandleType handle, absl::string_view target,
                            absl::string_view lookup_service,
                            const PickResult& pick_result);

  const std::string instance_uuid_;

  Mutex mu_;
  bool is_shutdown_ ABSL_GUARDED_BY(mu_) = false;
  bool update_in_progress_ = false;
  Cache cache_ ABSL_GUARDED_BY(mu_);

  std::unordered_map<RequestKey, OrphanablePtr<RlsRequest>,
                     absl::Hash<RequestKey>>
      request_map_ ABSL_GUARDED_BY(mu_);

  OrphanablePtr<RlsChannel> rls_channel_ ABSL_GUARDED_BY(mu_);

  absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> addresses_;
  ChannelArgs channel_args_;
  RefCountedPtr<RlsLbConfig> config_;
  RefCountedPtr<ChildPolicyWrapper> default_child_policy_;
  std::map<std::string , ChildPolicyWrapper*> child_policy_map_;

  std::unique_ptr<RegisteredMetricCallback> registered_metric_callback_;
};

RlsLb::ChildPolicyWrapper::ChildPolicyWrapper(RefCountedPtr<RlsLb> lb_policy,
                                              std::string target)
    : DualRefCounted<ChildPolicyWrapper>(
          GRPC_TRACE_FLAG_ENABLED(rls_lb) ? "ChildPolicyWrapper" : nullptr),
      lb_policy_(std::move(lb_policy)),
      target_(std::move(target)),
      picker_(MakeRefCounted<QueuePicker>(nullptr)) {
  lb_policy_->child_policy_map_.emplace(target_, this);
}

void RlsLb::ChildPolicyWrapper::Orphaned() {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] ChildPolicyWrapper=" << this
      << " [" << target_ << "]: shutdown";
  is_shutdown_ = true;
  lb_policy_->child_policy_map_.erase(target_);
  if (child_policy_ != nullptr) {
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     lb_policy_->interested_parties());
    child_policy_.reset();
  }
  picker_.reset();
}

std::optional<Json> InsertOrUpdateChildPolicyField(const std::string& field,
                                                   const std::string& value,
                                                   const Json& config,
                                                   ValidationErrors* errors) {
  if (config.type() != Json::Type::kArray) {
    errors->AddError("is not an array");
    return std::nullopt;
  }
  const size_t original_num_errors = errors->size();
  Json::Array array;
  for (size_t i = 0; i < config.array().size(); ++i) {
    const Json& child_json = config.array()[i];
    ValidationErrors::ScopedField json_field(errors, absl::StrCat("[", i, "]"));
    if (child_json.type() != Json::Type::kObject) {
      errors->AddError("is not an object");
    } else if (const Json::Object& child = child_json.object();
               child.size() != 1) {
      errors->AddError("child policy object contains more than one field");
    } else {
      const auto& [child_name, child_config_json] = *child.begin();
      ValidationErrors::ScopedField json_field(
          errors, absl::StrCat("[\"", child_name, "\"]"));
      if (child_config_json.type() != Json::Type::kObject) {
        errors->AddError("child policy config is not an object");
      } else {
        Json::Object child_config = child_config_json.object();
        child_config[field] = Json::FromString(value);
        array.emplace_back(Json::FromObject(
            {{child_name, Json::FromObject(std::move(child_config))}}));
      }
    }
  }
  if (errors->size() != original_num_errors) return std::nullopt;
  return Json::FromArray(std::move(array));
}

void RlsLb::ChildPolicyWrapper::StartUpdate(
    OrphanablePtr<ChildPolicyHandler>* child_policy_to_delete) {
  ValidationErrors errors;
  auto child_policy_config = InsertOrUpdateChildPolicyField(
      lb_policy_->config_->child_policy_config_target_field_name(), target_,
      lb_policy_->config_->child_policy_config(), &errors);
  CHECK(child_policy_config.has_value());
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] ChildPolicyWrapper=" << this
      << " [" << target_
      << "]: validating update, config: " << JsonDump(*child_policy_config);
  auto config =
      CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
          *child_policy_config);

  if (!config.ok()) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_.get() << "] ChildPolicyWrapper=" << this
        << " [" << target_ << "]: config failed to parse: " << config.status();
    pending_config_.reset();
    picker_ = MakeRefCounted<TransientFailurePicker>(
        absl::UnavailableError(config.status().message()));
    *child_policy_to_delete = std::move(child_policy_);
  } else {
    pending_config_ = std::move(*config);
  }
}

absl::Status RlsLb::ChildPolicyWrapper::MaybeFinishUpdate() {

  if (pending_config_ == nullptr) return absl::OkStatus();

  if (child_policy_ == nullptr) {
    Args create_args;
    create_args.work_serializer = lb_policy_->work_serializer();
    create_args.channel_control_helper = std::make_unique<ChildPolicyHelper>(
        WeakRef(DEBUG_LOCATION, "ChildPolicyHelper"));
    create_args.args = lb_policy_->channel_args_;
    child_policy_ = MakeOrphanable<ChildPolicyHandler>(std::move(create_args),
                                                       &rls_lb_trace);
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_.get() << "] ChildPolicyWrapper=" << this
        << " [" << target_ << "], created new child policy handler "
        << child_policy_.get();
    grpc_pollset_set_add_pollset_set(child_policy_->interested_parties(),
                                     lb_policy_->interested_parties());
  }

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] ChildPolicyWrapper=" << this
      << " [" << target_ << "], updating child policy handler "
      << child_policy_.get();
  UpdateArgs update_args;
  update_args.config = std::move(pending_config_);
  update_args.addresses = lb_policy_->addresses_;
  update_args.args = lb_policy_->channel_args_;
  return child_policy_->UpdateLocked(std::move(update_args));
}

void RlsLb::ChildPolicyWrapper::ChildPolicyHelper::UpdateState(
    grpc_connectivity_state state, const absl::Status& status,
    RefCountedPtr<SubchannelPicker> picker) {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << wrapper_->lb_policy_.get()
      << "] ChildPolicyWrapper=" << wrapper_.get() << " [" << wrapper_->target_
      << "] ChildPolicyHelper=" << this
      << ": UpdateState(state=" << ConnectivityStateName(state)
      << ", status=" << status << ", picker=" << picker.get() << ")";
  if (wrapper_->is_shutdown_) return;
  {
    MutexLock lock(&wrapper_->lb_policy_->mu_);

    if (wrapper_->connectivity_state_ == GRPC_CHANNEL_TRANSIENT_FAILURE &&
        state != GRPC_CHANNEL_READY) {
      return;
    }
    wrapper_->connectivity_state_ = state;
    DCHECK(picker != nullptr);
    if (picker != nullptr) {

      wrapper_->picker_.swap(picker);
    }
  }
  wrapper_->lb_policy_->UpdatePickerLocked();
}

std::map<std::string, std::string> BuildKeyMap(
    const RlsLbConfig::KeyBuilderMap& key_builder_map, absl::string_view path,
    absl::string_view host,
    const LoadBalancingPolicy::MetadataInterface* initial_metadata) {
  size_t last_slash_pos = path.npos;

  auto it = key_builder_map.find(std::string(path));
  if (it == key_builder_map.end()) {

    last_slash_pos = path.rfind('/');
    DCHECK(last_slash_pos != path.npos);
    if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    std::string service(path.substr(0, last_slash_pos + 1));
    it = key_builder_map.find(service);
    if (it == key_builder_map.end()) return {};
  }
  const RlsLbConfig::KeyBuilder* key_builder = &it->second;

  std::map<std::string, std::string> key_map;

  for (const auto& [key, header_names] : key_builder->header_keys) {
    for (const std::string& header_name : header_names) {
      std::string buffer;
      std::optional<absl::string_view> value =
          initial_metadata->Lookup(header_name, &buffer);
      if (value.has_value()) {
        key_map[key] = std::string(*value);
        break;
      }
    }
  }

  key_map.insert(key_builder->constant_keys.begin(),
                 key_builder->constant_keys.end());

  if (!key_builder->host_key.empty()) {
    key_map[key_builder->host_key] = std::string(host);
  }

  if (!key_builder->service_key.empty()) {
    if (last_slash_pos == path.npos) {
      last_slash_pos = path.rfind('/');
      DCHECK(last_slash_pos != path.npos);
      if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    }
    key_map[key_builder->service_key] =
        std::string(path.substr(1, last_slash_pos - 1));
  }

  if (!key_builder->method_key.empty()) {
    if (last_slash_pos == path.npos) {
      last_slash_pos = path.rfind('/');
      DCHECK(last_slash_pos != path.npos);
      if (GPR_UNLIKELY(last_slash_pos == path.npos)) return {};
    }
    key_map[key_builder->method_key] =
        std::string(path.substr(last_slash_pos + 1));
  }
  return key_map;
}

RlsLb::Picker::Picker(RefCountedPtr<RlsLb> lb_policy)
    : lb_policy_(std::move(lb_policy)), config_(lb_policy_->config_) {
  if (lb_policy_->default_child_policy_ != nullptr) {
    default_child_policy_ =
        lb_policy_->default_child_policy_->Ref(DEBUG_LOCATION, "Picker");
  }
}

LoadBalancingPolicy::PickResult RlsLb::Picker::Pick(PickArgs args) {

  RequestKey key = {
      BuildKeyMap(config_->key_builder_map(), args.path,
                  lb_policy_->channel_control_helper()->GetAuthority(),
                  args.initial_metadata)};
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] picker=" << this
      << ": request keys: " << key.ToString();
  Timestamp now = Timestamp::Now();
  MutexLock lock(&lb_policy_->mu_);
  if (lb_policy_->is_shutdown_) {
    return PickResult::Fail(
        absl::UnavailableError("LB policy already shut down"));
  }

  Cache::Entry* entry = lb_policy_->cache_.Find(key);

  if ((entry == nullptr ||
       (entry->stale_time() < now && entry->backoff_time() < now)) &&
      lb_policy_->request_map_.find(key) == lb_policy_->request_map_.end()) {

    if (lb_policy_->rls_channel_->ShouldThrottle()) {

      if (entry == nullptr || entry->data_expiration_time() < now) {
        return PickFromDefaultTargetOrFail(
            "RLS call throttled", args,
            absl::UnavailableError("RLS request throttled"));
      }
    }

    lb_policy_->rls_channel_->StartRlsCall(
        key, (entry == nullptr || entry->data_expiration_time() < now) ? nullptr
                                                                       : entry);
  }

  if (entry != nullptr) {

    if (entry->data_expiration_time() >= now) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << lb_policy_.get() << "] picker=" << this
          << ": using cache entry " << entry;
      return entry->Pick(args, config_->lookup_service());
    }

    if (entry->backoff_time() >= now) {
      return PickFromDefaultTargetOrFail(
          "RLS call in backoff", args,
          absl::UnavailableError(absl::StrCat("RLS request failed: ",
                                              entry->status().ToString())));
    }
  }

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] picker=" << this
      << ": RLS request pending; queuing pick";
  return PickResult::Queue();
}

LoadBalancingPolicy::PickResult RlsLb::Picker::PickFromDefaultTargetOrFail(
    const char* reason, PickArgs args, absl::Status status) {
  if (default_child_policy_ != nullptr) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_.get() << "] picker=" << this << ": "
        << reason << "; using default target";
    auto pick_result = default_child_policy_->Pick(args);
    lb_policy_->MaybeExportPickCount(kMetricDefaultTargetPicks,
                                     config_->default_target(),
                                     config_->lookup_service(), pick_result);
    return pick_result;
  }
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] picker=" << this << ": " << reason
      << "; failing pick";
  auto& stats_plugins =
      lb_policy_->channel_control_helper()->GetStatsPluginGroup();
  stats_plugins.AddCounter(kMetricFailedPicks, 1,
                           {lb_policy_->channel_control_helper()->GetTarget(),
                            config_->lookup_service()},
                           {});
  return PickResult::Fail(std::move(status));
}

RlsLb::Cache::Entry::BackoffTimer::BackoffTimer(RefCountedPtr<Entry> entry,
                                                Duration delay)
    : entry_(std::move(entry)) {
  backoff_timer_task_handle_ =
      entry_->lb_policy_->channel_control_helper()->GetEventEngine()->RunAfter(
          delay, [self = Ref(DEBUG_LOCATION, "BackoffTimer")]() mutable {
            ExecCtx exec_ctx;
            auto self_ptr = self.get();
            self_ptr->entry_->lb_policy_->work_serializer()->Run(
                [self = std::move(self)]() { self->OnBackoffTimerLocked(); });
          });
}

void RlsLb::Cache::Entry::BackoffTimer::Orphan() {
  if (backoff_timer_task_handle_.has_value() &&
      entry_->lb_policy_->channel_control_helper()->GetEventEngine()->Cancel(
          *backoff_timer_task_handle_)) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << entry_->lb_policy_.get()
        << "] cache entry=" << entry_.get() << " "
        << (entry_->is_shutdown_ ? "(shut down)"
                                 : entry_->lru_iterator_->ToString())
        << ", backoff timer canceled";
  }
  backoff_timer_task_handle_.reset();
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::Cache::Entry::BackoffTimer::OnBackoffTimerLocked() {
  {
    MutexLock lock(&entry_->lb_policy_->mu_);
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << entry_->lb_policy_.get()
        << "] cache entry=" << entry_.get() << " "
        << (entry_->is_shutdown_ ? "(shut down)"
                                 : entry_->lru_iterator_->ToString())
        << ", backoff timer fired";

    if (!backoff_timer_task_handle_.has_value()) return;
    backoff_timer_task_handle_.reset();
  }

  entry_->lb_policy_->UpdatePickerLocked();
}

std::unique_ptr<BackOff> MakeCacheEntryBackoff() {
  return std::make_unique<BackOff>(
      BackOff::Options()
          .set_initial_backoff(kCacheBackoffInitial)
          .set_multiplier(kCacheBackoffMultiplier)
          .set_jitter(kCacheBackoffJitter)
          .set_max_backoff(kCacheBackoffMax));
}

RlsLb::Cache::Entry::Entry(RefCountedPtr<RlsLb> lb_policy,
                           const RequestKey& key)
    : InternallyRefCounted<Entry>(GRPC_TRACE_FLAG_ENABLED(rls_lb) ? "CacheEntry"
                                                                  : nullptr),
      lb_policy_(std::move(lb_policy)),
      backoff_state_(MakeCacheEntryBackoff()),
      min_expiration_time_(Timestamp::Now() + kMinExpirationTime),
      lru_iterator_(lb_policy_->cache_.lru_list_.insert(
          lb_policy_->cache_.lru_list_.end(), key)) {}

void RlsLb::Cache::Entry::Orphan() {

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] cache entry=" << this << " "
      << lru_iterator_->ToString() << ": cache entry evicted";
  is_shutdown_ = true;
  lb_policy_->cache_.lru_list_.erase(lru_iterator_);
  lru_iterator_ = lb_policy_->cache_.lru_list_.end();
  CHECK(child_policy_wrappers_.empty());
  backoff_state_.reset();
  if (backoff_timer_ != nullptr) {
    backoff_timer_.reset();
    lb_policy_->UpdatePickerAsync();
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

size_t RlsLb::Cache::Entry::Size() const {

  CHECK(!is_shutdown_);
  return lb_policy_->cache_.EntrySizeForKey(*lru_iterator_);
}

LoadBalancingPolicy::PickResult RlsLb::Cache::Entry::Pick(
    PickArgs args, absl::string_view lookup_service) {
  size_t i = 0;
  ChildPolicyWrapper* child_policy_wrapper = nullptr;

  for (; i < child_policy_wrappers_.size(); ++i) {
    child_policy_wrapper = child_policy_wrappers_[i].get();
    if (child_policy_wrapper->connectivity_state() ==
            GRPC_CHANNEL_TRANSIENT_FAILURE &&
        i < child_policy_wrappers_.size() - 1) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << lb_policy_.get() << "] cache entry=" << this << " "
          << lru_iterator_->ToString() << ": target "
          << child_policy_wrapper->target() << " (" << i << " of "
          << child_policy_wrappers_.size()
          << ") in state TRANSIENT_FAILURE; skipping";
      continue;
    }
    break;
  }

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] cache entry=" << this << " "
      << lru_iterator_->ToString() << ": target "
      << child_policy_wrapper->target() << " (" << i << " of "
      << child_policy_wrappers_.size() << ") in state "
      << ConnectivityStateName(child_policy_wrapper->connectivity_state())
      << "; delegating";
  auto pick_result = child_policy_wrapper->Pick(args);
  lb_policy_->MaybeExportPickCount(kMetricTargetPicks,
                                   child_policy_wrapper->target(),
                                   lookup_service, pick_result);

  if (!header_data_.empty()) {
    auto* complete_pick =
        std::get_if<PickResult::Complete>(&pick_result.result);
    if (complete_pick != nullptr) {
      complete_pick->metadata_mutations.Set(kRlsHeaderKey, header_data_.Ref());
    }
  }
  return pick_result;
}

void RlsLb::Cache::Entry::ResetBackoff() {
  backoff_time_ = Timestamp::InfPast();
  backoff_timer_.reset();
}

bool RlsLb::Cache::Entry::ShouldRemove() const {
  Timestamp now = Timestamp::Now();
  return data_expiration_time_ < now && backoff_expiration_time_ < now;
}

bool RlsLb::Cache::Entry::CanEvict() const {
  Timestamp now = Timestamp::Now();
  return min_expiration_time_ < now;
}

void RlsLb::Cache::Entry::MarkUsed() {
  auto& lru_list = lb_policy_->cache_.lru_list_;
  auto new_it = lru_list.insert(lru_list.end(), *lru_iterator_);
  lru_list.erase(lru_iterator_);
  lru_iterator_ = new_it;
}

std::vector<RlsLb::ChildPolicyWrapper*>
RlsLb::Cache::Entry::OnRlsResponseLocked(
    ResponseInfo response, std::unique_ptr<BackOff> backoff_state,
    OrphanablePtr<ChildPolicyHandler>* child_policy_to_delete) {

  MarkUsed();

  if (!response.status.ok()) {
    status_ = response.status;
    if (backoff_state != nullptr) {
      backoff_state_ = std::move(backoff_state);
    } else {
      backoff_state_ = MakeCacheEntryBackoff();
    }
    const Duration delay = backoff_state_->NextAttemptDelay();
    const Timestamp now = Timestamp::Now();
    backoff_time_ = now + delay;
    backoff_expiration_time_ = now + delay * 2;
    backoff_timer_ = MakeOrphanable<BackoffTimer>(
        Ref(DEBUG_LOCATION, "BackoffTimer"), delay);
    lb_policy_->UpdatePickerAsync();
    return {};
  }

  header_data_ = std::move(response.header_data);
  Timestamp now = Timestamp::Now();
  data_expiration_time_ = now + lb_policy_->config_->max_age();
  stale_time_ = now + lb_policy_->config_->stale_age();
  status_ = absl::OkStatus();
  backoff_state_.reset();
  backoff_time_ = Timestamp::InfPast();
  backoff_expiration_time_ = Timestamp::InfPast();

  bool targets_changed = [&]() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&RlsLb::mu_) {
    if (child_policy_wrappers_.size() != response.targets.size()) return true;
    for (size_t i = 0; i < response.targets.size(); ++i) {
      if (child_policy_wrappers_[i]->target() != response.targets[i]) {
        return true;
      }
    }
    return false;
  }();
  if (!targets_changed) {

    lb_policy_->UpdatePickerAsync();
    return {};
  }

  std::set<absl::string_view> old_targets;
  for (RefCountedPtr<ChildPolicyWrapper>& child_policy_wrapper :
       child_policy_wrappers_) {
    old_targets.emplace(child_policy_wrapper->target());
  }
  bool update_picker = false;
  std::vector<ChildPolicyWrapper*> child_policies_to_finish_update;
  std::vector<RefCountedPtr<ChildPolicyWrapper>> new_child_policy_wrappers;
  new_child_policy_wrappers.reserve(response.targets.size());
  for (std::string& target : response.targets) {
    auto it = lb_policy_->child_policy_map_.find(target);
    if (it == lb_policy_->child_policy_map_.end()) {
      auto new_child = MakeRefCounted<ChildPolicyWrapper>(
          lb_policy_.Ref(DEBUG_LOCATION, "ChildPolicyWrapper"), target);
      new_child->StartUpdate(child_policy_to_delete);
      child_policies_to_finish_update.push_back(new_child.get());
      new_child_policy_wrappers.emplace_back(std::move(new_child));
    } else {
      new_child_policy_wrappers.emplace_back(
          it->second->Ref(DEBUG_LOCATION, "CacheEntry"));

      if (old_targets.find(target) == old_targets.end()) {
        update_picker = true;
      }
    }
  }
  child_policy_wrappers_ = std::move(new_child_policy_wrappers);
  if (update_picker) {
    lb_policy_->UpdatePickerAsync();
  }
  return child_policies_to_finish_update;
}

RlsLb::Cache::Cache(RlsLb* lb_policy) : lb_policy_(lb_policy) {
  StartCleanupTimer();
}

RlsLb::Cache::Entry* RlsLb::Cache::Find(const RequestKey& key) {
  auto it = map_.find(key);
  if (it == map_.end()) return nullptr;
  it->second->MarkUsed();
  return it->second.get();
}

RlsLb::Cache::Entry* RlsLb::Cache::FindOrInsert(
    const RequestKey& key, std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                               child_policy_wrappers_to_delete) {
  auto it = map_.find(key);

  if (it == map_.end()) {
    size_t entry_size = EntrySizeForKey(key);
    MaybeShrinkSize(size_limit_ - std::min(size_limit_, entry_size),
                    child_policy_wrappers_to_delete);
    Entry* entry = new Entry(
        lb_policy_->RefAsSubclass<RlsLb>(DEBUG_LOCATION, "CacheEntry"), key);
    map_.emplace(key, OrphanablePtr<Entry>(entry));
    size_ += entry_size;
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_ << "] key=" << key.ToString()
        << ": cache entry added, entry=" << entry;
    return entry;
  }

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_ << "] key=" << key.ToString()
      << ": found cache entry " << it->second.get();
  it->second->MarkUsed();
  return it->second.get();
}

void RlsLb::Cache::Resize(size_t bytes,
                          std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                              child_policy_wrappers_to_delete) {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_ << "] resizing cache to " << bytes << " bytes";
  size_limit_ = bytes;
  MaybeShrinkSize(size_limit_, child_policy_wrappers_to_delete);
}

void RlsLb::Cache::ResetAllBackoff() {
  for (auto& [_, entry] : map_) {
    entry->ResetBackoff();
  }
  lb_policy_->UpdatePickerAsync();
}

std::vector<RefCountedPtr<RlsLb::ChildPolicyWrapper>> RlsLb::Cache::Shutdown() {
  std::vector<RefCountedPtr<ChildPolicyWrapper>>
      child_policy_wrappers_to_delete;
  for (auto& [_, entry] : map_) {
    entry->TakeChildPolicyWrappers(&child_policy_wrappers_to_delete);
  }
  map_.clear();
  lru_list_.clear();
  if (cleanup_timer_handle_.has_value() &&
      lb_policy_->channel_control_helper()->GetEventEngine()->Cancel(
          *cleanup_timer_handle_)) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_ << "] cache cleanup timer canceled";
  }
  cleanup_timer_handle_.reset();
  return child_policy_wrappers_to_delete;
}

void RlsLb::Cache::ReportMetricsLocked(CallbackMetricReporter& reporter) {
  reporter.Report(
      kMetricCacheSize, size_,
      {lb_policy_->channel_control_helper()->GetTarget(),
       lb_policy_->config_->lookup_service(), lb_policy_->instance_uuid_},
      {});
  reporter.Report(
      kMetricCacheEntries, map_.size(),
      {lb_policy_->channel_control_helper()->GetTarget(),
       lb_policy_->config_->lookup_service(), lb_policy_->instance_uuid_},
      {});
}

void RlsLb::Cache::StartCleanupTimer() {
  cleanup_timer_handle_ =
      lb_policy_->channel_control_helper()->GetEventEngine()->RunAfter(
          kCacheCleanupTimerInterval,
          [this, lb_policy = lb_policy_->Ref(DEBUG_LOCATION,
                                             "CacheCleanupTimer")]() mutable {
            ExecCtx exec_ctx;
            lb_policy_->work_serializer()->Run(
                [this, lb_policy = std::move(lb_policy)]() {

                  OnCleanupTimer();
                });
          });
}

void RlsLb::Cache::OnCleanupTimer() {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_ << "] cache cleanup timer fired";
  std::vector<RefCountedPtr<ChildPolicyWrapper>>
      child_policy_wrappers_to_delete;
  MutexLock lock(&lb_policy_->mu_);
  if (!cleanup_timer_handle_.has_value()) return;
  if (lb_policy_->is_shutdown_) return;
  for (auto it = map_.begin(); it != map_.end();) {
    auto& entry = it->second;
    if (GPR_UNLIKELY(entry->ShouldRemove() && entry->CanEvict())) {
      size_ -= entry->Size();
      entry->TakeChildPolicyWrappers(&child_policy_wrappers_to_delete);
      it = map_.erase(it);
    } else {
      ++it;
    }
  }
  StartCleanupTimer();
}

size_t RlsLb::Cache::EntrySizeForKey(const RequestKey& key) {

  return (key.Size() * 2) + sizeof(Entry);
}

void RlsLb::Cache::MaybeShrinkSize(
    size_t bytes, std::vector<RefCountedPtr<ChildPolicyWrapper>>*
                      child_policy_wrappers_to_delete) {
  while (size_ > bytes) {
    auto lru_it = lru_list_.begin();
    if (GPR_UNLIKELY(lru_it == lru_list_.end())) break;
    auto map_it = map_.find(*lru_it);
    CHECK(map_it != map_.end());
    auto& entry = map_it->second;
    if (!entry->CanEvict()) break;
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_ << "] LRU eviction: removing entry "
        << entry.get() << " " << lru_it->ToString();
    size_ -= entry->Size();
    entry->TakeChildPolicyWrappers(child_policy_wrappers_to_delete);
    map_.erase(map_it);
  }
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_
      << "] LRU pass complete: desired size=" << bytes << " size=" << size_;
}

void RlsLb::RlsChannel::StateWatcher::OnConnectivityStateChange(
    grpc_connectivity_state new_state, const absl::Status& status) {
  auto* lb_policy = rls_channel_->lb_policy_.get();
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy << "] RlsChannel=" << rls_channel_.get()
      << " StateWatcher=" << this << ": state changed to "
      << ConnectivityStateName(new_state) << " (" << status << ")";
  if (rls_channel_->is_shutdown_) return;
  MutexLock lock(&lb_policy->mu_);
  if (new_state == GRPC_CHANNEL_READY && was_transient_failure_) {
    was_transient_failure_ = false;

    lb_policy->cache_.ResetAllBackoff();
  } else if (new_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    was_transient_failure_ = true;
  }
}

bool RlsLb::RlsChannel::Throttle::ShouldThrottle() {
  Timestamp now = Timestamp::Now();
  while (!requests_.empty() && now - requests_.front() > window_size_) {
    requests_.pop_front();
  }
  while (!failures_.empty() && now - failures_.front() > window_size_) {
    failures_.pop_front();
  }

  float num_requests = requests_.size();
  float num_successes = num_requests - failures_.size();
  // Note: it's possible that this ratio will be negative, in which case

  float throttle_probability =
      (num_requests - (num_successes * ratio_for_successes_)) /
      (num_requests + padding_);

  std::uniform_real_distribution<float> dist(0, 1.0);

  bool throttle = dist(rng_) < throttle_probability;

  if (throttle) {
    requests_.push_back(now);
    failures_.push_back(now);
  }
  return throttle;
}

void RlsLb::RlsChannel::Throttle::RegisterResponse(bool success) {
  Timestamp now = Timestamp::Now();
  requests_.push_back(now);
  if (!success) failures_.push_back(now);
}

RlsLb::RlsChannel::RlsChannel(RefCountedPtr<RlsLb> lb_policy)
    : InternallyRefCounted<RlsChannel>(
          GRPC_TRACE_FLAG_ENABLED(rls_lb) ? "RlsChannel" : nullptr),
      lb_policy_(std::move(lb_policy)) {

  auto creds =
      lb_policy_->channel_control_helper()->GetUnsafeChannelCredentials();

  auto authority = lb_policy_->channel_control_helper()->GetAuthority();
  ChannelArgs args = ChannelArgs()
                         .Set(GRPC_ARG_DEFAULT_AUTHORITY, authority)
                         .Set(GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL, 1);

  std::optional<absl::string_view> fake_security_expected_targets =
      lb_policy_->channel_args_.GetString(
          GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS);
  if (fake_security_expected_targets.has_value()) {
    args = args.Set(GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS,
                    *fake_security_expected_targets);
  }

  const std::string& service_config =
      lb_policy_->config_->rls_channel_service_config();
  if (!service_config.empty()) {
    args = args.Set(GRPC_ARG_SERVICE_CONFIG, service_config)
               .Set(GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION, 1);
  }
  channel_.reset(Channel::FromC(
      grpc_channel_create(lb_policy_->config_->lookup_service().c_str(),
                          creds.get(), args.ToC().get())));
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] RlsChannel=" << this
      << ": created channel " << channel_.get() << " for "
      << lb_policy_->config_->lookup_service();
  if (channel_ != nullptr) {

    channelz::ChannelNode* child_channelz_node = channel_->channelz_node();
    auto parent_channelz_node =
        lb_policy_->channel_args_.GetObjectRef<channelz::ChannelNode>();
    if (child_channelz_node != nullptr && parent_channelz_node != nullptr) {
      child_channelz_node->AddParent(parent_channelz_node.get());
      parent_channelz_node_ = std::move(parent_channelz_node);
    }

    watcher_ = new StateWatcher(Ref(DEBUG_LOCATION, "StateWatcher"));
    channel_->AddConnectivityWatcher(
        GRPC_CHANNEL_IDLE,
        OrphanablePtr<AsyncConnectivityStateWatcherInterface>(watcher_));
  }
}

void RlsLb::RlsChannel::Orphan() {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] RlsChannel=" << this
      << ", channel=" << channel_.get() << ": shutdown";
  is_shutdown_ = true;
  if (channel_ != nullptr) {

    if (parent_channelz_node_ != nullptr) {
      channelz::ChannelNode* child_channelz_node = channel_->channelz_node();
      CHECK_NE(child_channelz_node, nullptr);
      child_channelz_node->RemoveParent(parent_channelz_node_.get());
    }

    if (watcher_ != nullptr) {
      channel_->RemoveConnectivityWatcher(watcher_);
      watcher_ = nullptr;
    }
    channel_.reset();
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::RlsChannel::StartRlsCall(const RequestKey& key,
                                     Cache::Entry* stale_entry) {
  std::unique_ptr<BackOff> backoff_state;
  grpc_lookup_v1_RouteLookupRequest_Reason reason =
      grpc_lookup_v1_RouteLookupRequest_REASON_MISS;
  grpc_event_engine::experimental::Slice stale_header_data;
  if (stale_entry != nullptr) {
    backoff_state = stale_entry->TakeBackoffState();
    reason = grpc_lookup_v1_RouteLookupRequest_REASON_STALE;
    stale_header_data = stale_entry->header_data().Ref();
  }
  lb_policy_->request_map_.emplace(
      key, MakeOrphanable<RlsRequest>(
               lb_policy_.Ref(DEBUG_LOCATION, "RlsRequest"), key,
               lb_policy_->rls_channel_->Ref(DEBUG_LOCATION, "RlsRequest"),
               std::move(backoff_state), reason, std::move(stale_header_data)));
}

void RlsLb::RlsChannel::ReportResponseLocked(bool response_succeeded) {
  throttle_.RegisterResponse(response_succeeded);
}

void RlsLb::RlsChannel::ResetBackoff() {
  DCHECK(channel_ != nullptr);
  channel_->ResetConnectionBackoff();
}

RlsLb::RlsRequest::RlsRequest(
    RefCountedPtr<RlsLb> lb_policy, RequestKey key,
    RefCountedPtr<RlsChannel> rls_channel,
    std::unique_ptr<BackOff> backoff_state,
    grpc_lookup_v1_RouteLookupRequest_Reason reason,
    grpc_event_engine::experimental::Slice stale_header_data)
    : InternallyRefCounted<RlsRequest>(
          GRPC_TRACE_FLAG_ENABLED(rls_lb) ? "RlsRequest" : nullptr),
      lb_policy_(std::move(lb_policy)),
      key_(std::move(key)),
      rls_channel_(std::move(rls_channel)),
      backoff_state_(std::move(backoff_state)),
      reason_(reason),
      stale_header_data_(std::move(stale_header_data)) {
  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] rls_request=" << this
      << ": RLS request created for key " << key_.ToString();
  GRPC_CLOSURE_INIT(&call_complete_cb_, OnRlsCallComplete, this, nullptr);
  ExecCtx::Run(
      DEBUG_LOCATION,
      GRPC_CLOSURE_INIT(&call_start_cb_, StartCall,
                        Ref(DEBUG_LOCATION, "StartCall").release(), nullptr),
      absl::OkStatus());
}

RlsLb::RlsRequest::~RlsRequest() { CHECK_EQ(call_, nullptr); }

void RlsLb::RlsRequest::Orphan() {
  if (call_ != nullptr) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << lb_policy_.get() << "] rls_request=" << this << " "
        << key_.ToString() << ": cancelling RLS call";
    grpc_call_cancel_internal(call_);
  }
  Unref(DEBUG_LOCATION, "Orphan");
}

void RlsLb::RlsRequest::StartCall(void* arg, grpc_error_handle ) {
  auto* request = static_cast<RlsRequest*>(arg);
  request->lb_policy_->work_serializer()->Run([request]() {
    request->StartCallLocked();
    request->Unref(DEBUG_LOCATION, "StartCall");
  });
}

void RlsLb::RlsRequest::StartCallLocked() {
  {
    MutexLock lock(&lb_policy_->mu_);
    if (lb_policy_->is_shutdown_) return;
  }
  Timestamp now = Timestamp::Now();
  deadline_ = now + lb_policy_->config_->lookup_service_timeout();
  grpc_metadata_array_init(&recv_initial_metadata_);
  grpc_metadata_array_init(&recv_trailing_metadata_);
  call_ = rls_channel_->channel()->CreateCall(
      nullptr, GRPC_PROPAGATE_DEFAULTS, nullptr,
      lb_policy_->interested_parties(),
      Slice::FromStaticString(kRlsRequestPath), std::nullopt,
      deadline_, true);
  grpc_op ops[6];
  memset(ops, 0, sizeof(ops));
  grpc_op* op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  ++op;
  op->op = GRPC_OP_SEND_MESSAGE;
  send_message_ = MakeRequestProto();
  op->data.send_message.send_message = send_message_;
  ++op;
  op->op = GRPC_OP_SEND_CLOSE_FROM_CLIENT;
  ++op;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata =
      &recv_initial_metadata_;
  ++op;
  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &recv_message_;
  ++op;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata = &recv_trailing_metadata_;
  op->data.recv_status_on_client.status = &status_recv_;
  op->data.recv_status_on_client.status_details = &status_details_recv_;
  ++op;
  Ref(DEBUG_LOCATION, "OnRlsCallComplete").release();
  auto call_error = grpc_call_start_batch_and_execute(
      call_, ops, static_cast<size_t>(op - ops), &call_complete_cb_);
  CHECK_EQ(call_error, GRPC_CALL_OK);
}

void RlsLb::RlsRequest::OnRlsCallComplete(void* arg, grpc_error_handle error) {
  auto* request = static_cast<RlsRequest*>(arg);
  request->lb_policy_->work_serializer()->Run([request, error]() {
    request->OnRlsCallCompleteLocked(error);
    request->Unref(DEBUG_LOCATION, "OnRlsCallComplete");
  });
}

void RlsLb::RlsRequest::OnRlsCallCompleteLocked(grpc_error_handle error) {
  if (GRPC_TRACE_FLAG_ENABLED(rls_lb)) {
    std::string status_message(StringViewFromSlice(status_details_recv_));
    LOG(INFO) << "[rlslb " << lb_policy_.get() << "] rls_request=" << this
              << " " << key_.ToString() << ", error=" << StatusToString(error)
              << ", status={" << status_recv_ << ", " << status_message << "}"
              << " RLS call response received";
  }

  ResponseInfo response;
  if (!error.ok()) {
    grpc_status_code code;
    std::string message;
    grpc_error_get_status(error, deadline_, &code, &message,
                          nullptr, nullptr);
    response.status =
        absl::Status(static_cast<absl::StatusCode>(code), message);
  } else if (status_recv_ != GRPC_STATUS_OK) {
    response.status = absl::Status(static_cast<absl::StatusCode>(status_recv_),
                                   StringViewFromSlice(status_details_recv_));
  } else {
    response = ParseResponseProto();
  }

  grpc_byte_buffer_destroy(send_message_);
  grpc_byte_buffer_destroy(recv_message_);
  grpc_metadata_array_destroy(&recv_initial_metadata_);
  grpc_metadata_array_destroy(&recv_trailing_metadata_);
  CSliceUnref(status_details_recv_);
  grpc_call_unref(call_);
  call_ = nullptr;

  GRPC_TRACE_LOG(rls_lb, INFO)
      << "[rlslb " << lb_policy_.get() << "] rls_request=" << this << " "
      << key_.ToString() << ": response info: " << response.ToString();
  std::vector<ChildPolicyWrapper*> child_policies_to_finish_update;
  std::vector<RefCountedPtr<ChildPolicyWrapper>>
      child_policy_wrappers_to_delete;
  OrphanablePtr<ChildPolicyHandler> child_policy_to_delete;
  {
    MutexLock lock(&lb_policy_->mu_);
    if (lb_policy_->is_shutdown_) return;
    rls_channel_->ReportResponseLocked(response.status.ok());
    Cache::Entry* cache_entry =
        lb_policy_->cache_.FindOrInsert(key_, &child_policy_wrappers_to_delete);
    child_policies_to_finish_update = cache_entry->OnRlsResponseLocked(
        std::move(response), std::move(backoff_state_),
        &child_policy_to_delete);
    lb_policy_->request_map_.erase(key_);
  }

  for (ChildPolicyWrapper* child : child_policies_to_finish_update) {

    absl::Status status = child->MaybeFinishUpdate();
    if (!status.ok()) {
      lb_policy_->channel_control_helper()->RequestReresolution();
    }
  }
}

grpc_byte_buffer* RlsLb::RlsRequest::MakeRequestProto() {
  upb::Arena arena;
  grpc_lookup_v1_RouteLookupRequest* req =
      grpc_lookup_v1_RouteLookupRequest_new(arena.ptr());
  grpc_lookup_v1_RouteLookupRequest_set_target_type(
      req, upb_StringView_FromDataAndSize(kGrpc, sizeof(kGrpc) - 1));
  for (const auto& [key, value] : key_.key_map) {
    grpc_lookup_v1_RouteLookupRequest_key_map_set(
        req, upb_StringView_FromDataAndSize(key.data(), key.size()),
        upb_StringView_FromDataAndSize(value.data(), value.size()),
        arena.ptr());
  }
  grpc_lookup_v1_RouteLookupRequest_set_reason(req, reason_);
  if (!stale_header_data_.empty()) {
    grpc_lookup_v1_RouteLookupRequest_set_stale_header_data(
        req, StdStringToUpbString(stale_header_data_.as_string_view()));
  }
  size_t len;
  char* buf =
      grpc_lookup_v1_RouteLookupRequest_serialize(req, arena.ptr(), &len);
  grpc_slice send_slice = grpc_slice_from_copied_buffer(buf, len);
  grpc_byte_buffer* byte_buffer = grpc_raw_byte_buffer_create(&send_slice, 1);
  CSliceUnref(send_slice);
  return byte_buffer;
}

RlsLb::ResponseInfo RlsLb::RlsRequest::ParseResponseProto() {
  ResponseInfo response_info;
  upb::Arena arena;
  grpc_byte_buffer_reader bbr;
  grpc_byte_buffer_reader_init(&bbr, recv_message_);
  grpc_slice recv_slice = grpc_byte_buffer_reader_readall(&bbr);
  grpc_byte_buffer_reader_destroy(&bbr);
  grpc_lookup_v1_RouteLookupResponse* response =
      grpc_lookup_v1_RouteLookupResponse_parse(
          reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(recv_slice)),
          GRPC_SLICE_LENGTH(recv_slice), arena.ptr());
  CSliceUnref(recv_slice);
  if (response == nullptr) {
    response_info.status = absl::InternalError("cannot parse RLS response");
    return response_info;
  }
  size_t num_targets;
  const upb_StringView* targets_strview =
      grpc_lookup_v1_RouteLookupResponse_targets(response, &num_targets);
  if (num_targets == 0) {
    response_info.status =
        absl::InvalidArgumentError("RLS response has no target entry");
    return response_info;
  }
  response_info.targets.reserve(num_targets);
  for (size_t i = 0; i < num_targets; ++i) {
    response_info.targets.emplace_back(targets_strview[i].data,
                                       targets_strview[i].size);
  }
  upb_StringView header_data_strview =
      grpc_lookup_v1_RouteLookupResponse_header_data(response);
  response_info.header_data =
      grpc_event_engine::experimental::Slice::FromCopiedBuffer(
          header_data_strview.data, header_data_strview.size);
  return response_info;
}

std::string GenerateUUID() {
  absl::uniform_int_distribution<uint64_t> distribution;
  SharedBitGen g;
  uint64_t hi = distribution(g);
  uint64_t lo = distribution(g);
  return GenerateUUIDv4(hi, lo);
}

RlsLb::RlsLb(Args args)
    : LoadBalancingPolicy(std::move(args)),
      instance_uuid_(channel_args()
                         .GetOwnedString(GRPC_ARG_TEST_ONLY_RLS_INSTANCE_ID)
                         .value_or(GenerateUUID())),
      cache_(this) {
  GRPC_TRACE_LOG(rls_lb, INFO) << "[rlslb " << this << "] policy created";
}

bool EndpointsEqual(
    const absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> endpoints1,
    const absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>>
        endpoints2) {
  if (endpoints1.status() != endpoints2.status()) return false;
  if (endpoints1.ok()) {
    std::vector<EndpointAddresses> e1_list;
    (*endpoints1)->ForEach([&](const EndpointAddresses& endpoint) {
      e1_list.push_back(endpoint);
    });
    size_t i = 0;
    bool different = false;
    (*endpoints2)->ForEach([&](const EndpointAddresses& endpoint) {
      if (endpoint != e1_list[i++]) different = true;
    });
    if (different) return false;
    if (i != e1_list.size()) return false;
  }
  return true;
}

absl::Status RlsLb::UpdateLocked(UpdateArgs args) {
  GRPC_TRACE_LOG(rls_lb, INFO) << "[rlslb " << this << "] policy updated";
  update_in_progress_ = true;

  RefCountedPtr<RlsLbConfig> old_config = std::move(config_);
  config_ = args.config.TakeAsSubclass<RlsLbConfig>();
  if (GRPC_TRACE_FLAG_ENABLED(rls_lb) &&
      (old_config == nullptr ||
       old_config->child_policy_config() != config_->child_policy_config())) {
    LOG(INFO) << "[rlslb " << this << "] updated child policy config: "
              << JsonDump(config_->child_policy_config());
  }

  absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> old_addresses;
  if (args.addresses.ok()) {
    old_addresses = std::move(addresses_);
    addresses_ = std::move(args.addresses);
  } else {
    old_addresses = addresses_;
  }

  channel_args_ = std::move(args.args);

  bool update_child_policies =
      old_config == nullptr ||
      old_config->child_policy_config() != config_->child_policy_config() ||
      !EndpointsEqual(old_addresses, addresses_) || args.args != channel_args_;

  bool created_default_child = false;
  if (old_config == nullptr ||
      config_->default_target() != old_config->default_target()) {
    if (config_->default_target().empty()) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << this << "] unsetting default target";
      default_child_policy_.reset();
    } else if (auto it = child_policy_map_.find(config_->default_target());
               it == child_policy_map_.end()) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << this << "] creating new default target";
      default_child_policy_ = MakeRefCounted<ChildPolicyWrapper>(
          RefAsSubclass<RlsLb>(DEBUG_LOCATION, "ChildPolicyWrapper"),
          config_->default_target());
      created_default_child = true;
    } else {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << this << "] using existing child for default target";
      default_child_policy_ =
          it->second->Ref(DEBUG_LOCATION, "DefaultChildPolicy");
    }
  }

  std::vector<RefCountedPtr<ChildPolicyWrapper>>
      child_policy_wrappers_to_delete;
  OrphanablePtr<ChildPolicyHandler> child_policy_to_delete;
  {
    MutexLock lock(&mu_);

    if (old_config == nullptr ||
        config_->lookup_service() != old_config->lookup_service()) {
      rls_channel_ = MakeOrphanable<RlsChannel>(
          RefAsSubclass<RlsLb>(DEBUG_LOCATION, "RlsChannel"));
    }

    if (old_config == nullptr ||
        config_->cache_size_bytes() != old_config->cache_size_bytes()) {
      cache_.Resize(static_cast<size_t>(config_->cache_size_bytes()),
                    &child_policy_wrappers_to_delete);
    }

    if (update_child_policies) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << this << "] starting child policy updates";
      for (auto& [_, child] : child_policy_map_) {
        child->StartUpdate(&child_policy_to_delete);
      }
    } else if (created_default_child) {
      GRPC_TRACE_LOG(rls_lb, INFO)
          << "[rlslb " << this << "] starting default child policy update";
      default_child_policy_->StartUpdate(&child_policy_to_delete);
    }
  }

  std::vector<std::string> errors;
  if (update_child_policies) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << this << "] finishing child policy updates";
    for (auto& [name, child] : child_policy_map_) {
      absl::Status status = child->MaybeFinishUpdate();
      if (!status.ok()) {
        errors.emplace_back(
            absl::StrCat("target ", name, ": ", status.ToString()));
      }
    }
  } else if (created_default_child) {
    GRPC_TRACE_LOG(rls_lb, INFO)
        << "[rlslb " << this << "] finishing default child policy update";
    absl::Status status = default_child_policy_->MaybeFinishUpdate();
    if (!status.ok()) {
      errors.emplace_back(absl::StrCat("target ", config_->default_target(),
                                       ": ", status.ToString()));
    }
  }
  update_in_progress_ = false;

  if (registered_metric_callback_ == nullptr) {
    registered_metric_callback_ =
        channel_control_helper()->GetStatsPluginGroup().RegisterCallback(
            [this](CallbackMetricReporter& reporter) {
              MutexLock lock(&mu_);
              cache_.ReportMetricsLocked(reporter);
            },
            Duration::Seconds(5), kMetricCacheSize, kMetricCacheEntries);
  }

  UpdatePickerLocked();

  if (!errors.empty()) {
    return absl::UnavailableError(absl::StrCat(
        "errors from children: [", absl::StrJoin(errors, "; "), "]"));
  }
  return absl::OkStatus();
}

void RlsLb::ExitIdleLocked() {
  MutexLock lock(&mu_);
  for (auto& [_, child] : child_policy_map_) {
    child->ExitIdleLocked();
  }
}

void RlsLb::ResetBackoffLocked() {
  {
    MutexLock lock(&mu_);
    rls_channel_->ResetBackoff();
    cache_.ResetAllBackoff();
  }
  for (auto& [_, child] : child_policy_map_) {
    child->ResetBackoffLocked();
  }
}

void RlsLb::ShutdownLocked() {
  GRPC_TRACE_LOG(rls_lb, INFO) << "[rlslb " << this << "] policy shutdown";
  registered_metric_callback_.reset();
  RefCountedPtr<ChildPolicyWrapper> child_policy_to_delete;
  std::vector<RefCountedPtr<ChildPolicyWrapper>>
      child_policy_wrappers_to_delete;
  OrphanablePtr<RlsChannel> rls_channel_to_delete;
  {
    MutexLock lock(&mu_);
    is_shutdown_ = true;
    config_.reset(DEBUG_LOCATION, "ShutdownLocked");
    child_policy_wrappers_to_delete = cache_.Shutdown();
    request_map_.clear();
    rls_channel_to_delete = std::move(rls_channel_);
    child_policy_to_delete = std::move(default_child_policy_);
  }
  channel_args_ = ChannelArgs();
}

void RlsLb::UpdatePickerAsync() {
  work_serializer()->Run([self = RefAsSubclass<RlsLb>(
                              DEBUG_LOCATION, "UpdatePickerAsync")]() mutable {
    self->UpdatePickerLocked();
    self.reset(DEBUG_LOCATION, "UpdatePickerAsync");
  });
}

void RlsLb::UpdatePickerLocked() {

  if (update_in_progress_) return;
  GRPC_TRACE_LOG(rls_lb, INFO) << "[rlslb " << this << "] updating picker";
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  if (!child_policy_map_.empty()) {
    state = GRPC_CHANNEL_TRANSIENT_FAILURE;
    int num_idle = 0;
    int num_connecting = 0;
    {
      MutexLock lock(&mu_);
      if (is_shutdown_) return;
      for (auto& [_, child] : child_policy_map_) {
        grpc_connectivity_state child_state = child->connectivity_state();
        GRPC_TRACE_LOG(rls_lb, INFO)
            << "[rlslb " << this << "] target " << child->target()
            << " in state " << ConnectivityStateName(child_state);
        if (child_state == GRPC_CHANNEL_READY) {
          state = GRPC_CHANNEL_READY;
          break;
        } else if (child_state == GRPC_CHANNEL_CONNECTING) {
          ++num_connecting;
        } else if (child_state == GRPC_CHANNEL_IDLE) {
          ++num_idle;
        }
      }
      if (state != GRPC_CHANNEL_READY) {
        if (num_connecting > 0) {
          state = GRPC_CHANNEL_CONNECTING;
        } else if (num_idle > 0) {
          state = GRPC_CHANNEL_IDLE;
        }
      }
    }
  }
  GRPC_TRACE_LOG(rls_lb, INFO) << "[rlslb " << this << "] reporting state "
                               << ConnectivityStateName(state);
  absl::Status status;
  if (state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    status = absl::UnavailableError("no children available");
  }
  channel_control_helper()->UpdateState(
      state, status,
      MakeRefCounted<Picker>(RefAsSubclass<RlsLb>(DEBUG_LOCATION, "Picker")));
}

template <typename HandleType>
void RlsLb::MaybeExportPickCount(HandleType handle, absl::string_view target,
                                 absl::string_view lookup_service,
                                 const PickResult& pick_result) {
  absl::string_view pick_result_string = Match(
      pick_result.result,
      [](const LoadBalancingPolicy::PickResult::Complete&) {
        return "complete";
      },
      [](const LoadBalancingPolicy::PickResult::Queue&) { return ""; },
      [](const LoadBalancingPolicy::PickResult::Fail&) { return "fail"; },
      [](const LoadBalancingPolicy::PickResult::Drop&) { return "drop"; });
  if (pick_result_string.empty()) return;
  auto& stats_plugins = channel_control_helper()->GetStatsPluginGroup();
  stats_plugins.AddCounter(handle, 1,
                           {channel_control_helper()->GetTarget(),
                            lookup_service, target, pick_result_string},
                           {});
}

struct GrpcKeyBuilder {
  struct Name {
    std::string service;
    std::string method;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<Name>()
                                      .Field("service", &Name::service)
                                      .OptionalField("method", &Name::method)
                                      .Finish();
      return loader;
    }
  };

  struct NameMatcher {
    std::string key;
    std::vector<std::string> names;
    std::optional<bool> required_match;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<NameMatcher>()
              .Field("key", &NameMatcher::key)
              .Field("names", &NameMatcher::names)
              .OptionalField("requiredMatch", &NameMatcher::required_match)
              .Finish();
      return loader;
    }

    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {

      {
        ValidationErrors::ScopedField field(errors, ".key");
        if (!errors->FieldHasErrors() && key.empty()) {
          errors->AddError("must be non-empty");
        }
      }

      {
        ValidationErrors::ScopedField field(errors, ".names");
        if (!errors->FieldHasErrors() && names.empty()) {
          errors->AddError("must be non-empty");
        }

        for (size_t i = 0; i < names.size(); ++i) {
          ValidationErrors::ScopedField field(errors,
                                              absl::StrCat("[", i, "]"));
          if (!errors->FieldHasErrors() && names[i].empty()) {
            errors->AddError("must be non-empty");
          }
        }
      }

      {
        ValidationErrors::ScopedField field(errors, ".requiredMatch");
        if (required_match.has_value()) {
          errors->AddError("must not be present");
        }
      }
    }
  };

  struct ExtraKeys {
    std::optional<std::string> host_key;
    std::optional<std::string> service_key;
    std::optional<std::string> method_key;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader =
          JsonObjectLoader<ExtraKeys>()
              .OptionalField("host", &ExtraKeys::host_key)
              .OptionalField("service", &ExtraKeys::service_key)
              .OptionalField("method", &ExtraKeys::method_key)
              .Finish();
      return loader;
    }

    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {
      auto check_field = [&](const std::string& field_name,
                             std::optional<std::string>* struct_field) {
        ValidationErrors::ScopedField field(errors,
                                            absl::StrCat(".", field_name));
        if (struct_field->has_value() && (*struct_field)->empty()) {
          errors->AddError("must be non-empty if set");
        }
      };
      check_field("host", &host_key);
      check_field("service", &service_key);
      check_field("method", &method_key);
    }
  };

  std::vector<Name> names;
  std::vector<NameMatcher> headers;
  ExtraKeys extra_keys;
  std::map<std::string , std::string > constant_keys;

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader =
        JsonObjectLoader<GrpcKeyBuilder>()
            .Field("names", &GrpcKeyBuilder::names)
            .OptionalField("headers", &GrpcKeyBuilder::headers)
            .OptionalField("extraKeys", &GrpcKeyBuilder::extra_keys)
            .OptionalField("constantKeys", &GrpcKeyBuilder::constant_keys)
            .Finish();
    return loader;
  }

  void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {

    {
      ValidationErrors::ScopedField field(errors, ".names");
      if (!errors->FieldHasErrors() && names.empty()) {
        errors->AddError("must be non-empty");
      }
    }

    if (constant_keys.find("") != constant_keys.end()) {
      ValidationErrors::ScopedField field(errors, ".constantKeys[\"\"]");
      errors->AddError("key must be non-empty");
    }

    std::set<absl::string_view> keys_seen;
    auto duplicate_key_check_func = [&keys_seen, errors](
                                        const std::string& key,
                                        const std::string& field_name) {
      if (key.empty()) return;
      ValidationErrors::ScopedField field(errors, field_name);
      auto it = keys_seen.find(key);
      if (it != keys_seen.end()) {
        errors->AddError(absl::StrCat("duplicate key \"", key, "\""));
      } else {
        keys_seen.insert(key);
      }
    };
    for (size_t i = 0; i < headers.size(); ++i) {
      NameMatcher& header = headers[i];
      duplicate_key_check_func(header.key,
                               absl::StrCat(".headers[", i, "].key"));
    }
    for (const auto& [key, value] : constant_keys) {
      duplicate_key_check_func(key,
                               absl::StrCat(".constantKeys[\"", key, "\"]"));
    }
    if (extra_keys.host_key.has_value()) {
      duplicate_key_check_func(*extra_keys.host_key, ".extraKeys.host");
    }
    if (extra_keys.service_key.has_value()) {
      duplicate_key_check_func(*extra_keys.service_key, ".extraKeys.service");
    }
    if (extra_keys.method_key.has_value()) {
      duplicate_key_check_func(*extra_keys.method_key, ".extraKeys.method");
    }
  }
};

}

const JsonLoaderInterface* RlsLbConfig::RouteLookupConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<RouteLookupConfig>()
          // Note: Some fields require manual processing and are handled in

          .Field("lookupService", &RouteLookupConfig::lookup_service)
          .OptionalField("lookupServiceTimeout",
                         &RouteLookupConfig::lookup_service_timeout)
          .OptionalField("maxAge", &RouteLookupConfig::max_age)
          .OptionalField("staleAge", &RouteLookupConfig::stale_age)
          .Field("cacheSizeBytes", &RouteLookupConfig::cache_size_bytes)
          .OptionalField("defaultTarget", &RouteLookupConfig::default_target)
          .Finish();
  return loader;
}

void RlsLbConfig::RouteLookupConfig::JsonPostLoad(const Json& json,
                                                  const JsonArgs& args,
                                                  ValidationErrors* errors) {

  auto grpc_keybuilders = LoadJsonObjectField<std::vector<GrpcKeyBuilder>>(
      json.object(), args, "grpcKeybuilders", errors);
  if (grpc_keybuilders.has_value()) {
    ValidationErrors::ScopedField field(errors, ".grpcKeybuilders");
    for (size_t i = 0; i < grpc_keybuilders->size(); ++i) {
      ValidationErrors::ScopedField field(errors, absl::StrCat("[", i, "]"));
      auto& grpc_keybuilder = (*grpc_keybuilders)[i];

      RlsLbConfig::KeyBuilder key_builder;
      for (const auto& header : grpc_keybuilder.headers) {
        key_builder.header_keys.emplace(header.key, header.names);
      }
      if (grpc_keybuilder.extra_keys.host_key.has_value()) {
        key_builder.host_key = std::move(*grpc_keybuilder.extra_keys.host_key);
      }
      if (grpc_keybuilder.extra_keys.service_key.has_value()) {
        key_builder.service_key =
            std::move(*grpc_keybuilder.extra_keys.service_key);
      }
      if (grpc_keybuilder.extra_keys.method_key.has_value()) {
        key_builder.method_key =
            std::move(*grpc_keybuilder.extra_keys.method_key);
      }
      key_builder.constant_keys = std::move(grpc_keybuilder.constant_keys);

      for (const auto& name : grpc_keybuilder.names) {
        std::string path = absl::StrCat("/", name.service, "/", name.method);
        bool inserted = key_builder_map.emplace(path, key_builder).second;
        if (!inserted) {
          errors->AddError(absl::StrCat("duplicate entry for \"", path, "\""));
        }
      }
    }
  }

  {
    ValidationErrors::ScopedField field(errors, ".lookupService");
    if (!errors->FieldHasErrors() &&
        !CoreConfiguration::Get().resolver_registry().IsValidTarget(
            lookup_service)) {
      errors->AddError("must be valid gRPC target URI");
    }
  }

  const bool stale_age_set =
      json.object().find("staleAge") != json.object().end();
  const bool max_age_set = json.object().find("maxAge") != json.object().end();
  if (stale_age_set && !max_age_set) {
    ValidationErrors::ScopedField field(errors, ".maxAge");
    errors->AddError("must be set if staleAge is set");
  }

  if (stale_age > kMaxMaxAge) stale_age = kMaxMaxAge;

  if (!stale_age_set && max_age > kMaxMaxAge) max_age = kMaxMaxAge;

  if (stale_age >= max_age) stale_age = max_age;

  {
    ValidationErrors::ScopedField field(errors, ".cacheSizeBytes");
    if (!errors->FieldHasErrors() && cache_size_bytes <= 0) {
      errors->AddError("must be greater than 0");
    }
  }

  if (cache_size_bytes > kMaxCacheSizeBytes) {
    cache_size_bytes = kMaxCacheSizeBytes;
  }

  {
    ValidationErrors::ScopedField field(errors, ".defaultTarget");
    if (!errors->FieldHasErrors() &&
        json.object().find("defaultTarget") != json.object().end() &&
        default_target.empty()) {
      errors->AddError("must be non-empty if set");
    }
  }
}

const JsonLoaderInterface* RlsLbConfig::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<RlsLbConfig>()
          // Note: Some fields require manual processing and are handled in

          .Field("routeLookupConfig", &RlsLbConfig::route_lookup_config_)
          .Field("childPolicyConfigTargetFieldName",
                 &RlsLbConfig::child_policy_config_target_field_name_)
          .Finish();
  return loader;
}

void RlsLbConfig::JsonPostLoad(const Json& json, const JsonArgs&,
                               ValidationErrors* errors) {

  auto it = json.object().find("routeLookupChannelServiceConfig");
  if (it != json.object().end()) {
    rls_channel_service_config_ = JsonDump(it->second);
    ValidationErrors::ScopedField field(errors,
                                        ".routeLookupChannelServiceConfig");

    ServiceConfigImpl::Create(ChannelArgs(), it->second, errors);
  }

  {
    ValidationErrors::ScopedField field(errors,
                                        ".childPolicyConfigTargetFieldName");
    if (!errors->FieldHasErrors() &&
        child_policy_config_target_field_name_.empty()) {
      errors->AddError("must be non-empty");
    }
  }

  {
    ValidationErrors::ScopedField field(errors, ".childPolicy");
    auto it = json.object().find("childPolicy");
    if (it == json.object().end()) {
      errors->AddError("field not present");
    } else {

      std::string target = route_lookup_config_.default_target.empty()
                               ? kFakeTargetFieldValue
                               : route_lookup_config_.default_target;
      auto child_policy_config = InsertOrUpdateChildPolicyField(
          child_policy_config_target_field_name_, target, it->second, errors);
      if (child_policy_config.has_value()) {
        child_policy_config_ = std::move(*child_policy_config);

        auto parsed_config =
            CoreConfiguration::Get()
                .lb_policy_registry()
                .ParseLoadBalancingConfig(child_policy_config_);
        if (!parsed_config.ok()) {
          errors->AddError(parsed_config.status().message());
        } else {

          for (const Json& config : child_policy_config_.array()) {
            if (config.object().begin()->first == (*parsed_config)->name()) {
              child_policy_config_ = Json::FromArray({config});
              break;
            }
          }

          if (!route_lookup_config_.default_target.empty()) {
            default_child_policy_parsed_config_ = std::move(*parsed_config);
          }
        }
      }
    }
  }
}

namespace {

class RlsLbFactory final : public LoadBalancingPolicyFactory {
 public:
  absl::string_view name() const override { return RlsLbConfig::Name(); }

  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<RlsLb>(std::move(args));
  }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<RlsLbConfig>>(
        json, JsonArgs(), "errors validating RLS LB policy config");
  }
};

}

void RegisterRlsLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<RlsLbFactory>());
}

}
