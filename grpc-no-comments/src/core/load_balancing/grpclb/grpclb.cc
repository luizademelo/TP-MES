
// Copyright 2016 gRPC authors.

#include "src/core/load_balancing/grpclb/grpclb.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <inttypes.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "absl/container/inlined_vector.h"
#include "absl/functional/function_ref.h"
#include "absl/log/check.h"
#include "absl/log/globals.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/grpclb/client_load_reporting_filter.h"
#include "src/core/load_balancing/grpclb/grpclb_balancer_addresses.h"
#include "src/core/load_balancing/grpclb/grpclb_client_stats.h"
#include "src/core/load_balancing/grpclb/load_balancer_api.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/resolver/resolver.h"
#include "src/core/util/backoff.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/string.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"
#include "src/core/util/validation_errors.h"
#include "src/core/util/work_serializer.h"
#include "upb/mem/arena.hpp"

#define GRPC_GRPCLB_INITIAL_CONNECT_BACKOFF_SECONDS 1
#define GRPC_GRPCLB_RECONNECT_BACKOFF_MULTIPLIER 1.6
#define GRPC_GRPCLB_RECONNECT_MAX_BACKOFF_SECONDS 120
#define GRPC_GRPCLB_RECONNECT_JITTER 0.2
#define GRPC_GRPCLB_DEFAULT_FALLBACK_TIMEOUT_MS 10000
#define GRPC_GRPCLB_DEFAULT_SUBCHANNEL_DELETION_DELAY_MS 10000

#define GRPC_ARG_GRPCLB_ENABLE_LOAD_REPORTING_FILTER \
  "grpc.internal.grpclb_enable_load_reporting_filter"

namespace grpc_core {

namespace {

using ::grpc_event_engine::experimental::EventEngine;

constexpr absl::string_view kGrpclb = "grpclb";

class GrpcLbConfig final : public LoadBalancingPolicy::Config {
 public:
  GrpcLbConfig() = default;

  GrpcLbConfig(const GrpcLbConfig&) = delete;
  GrpcLbConfig& operator=(const GrpcLbConfig&) = delete;

  GrpcLbConfig(GrpcLbConfig&& other) = delete;
  GrpcLbConfig& operator=(GrpcLbConfig&& other) = delete;

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader =
        JsonObjectLoader<GrpcLbConfig>()
            // Note: "childPolicy" field requires custom parsing, so

            .OptionalField("serviceName", &GrpcLbConfig::service_name_)
            .Finish();
    return loader;
  }

  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors) {
    ValidationErrors::ScopedField field(errors, ".childPolicy");
    Json child_policy_config_json_tmp;
    const Json* child_policy_config_json;
    auto it = json.object().find("childPolicy");
    if (it == json.object().end()) {
      child_policy_config_json_tmp = Json::FromArray({Json::FromObject({
          {"round_robin", Json::FromObject({})},
      })});
      child_policy_config_json = &child_policy_config_json_tmp;
    } else {
      child_policy_config_json = &it->second;
    }
    auto child_policy_config =
        CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
            *child_policy_config_json);
    if (!child_policy_config.ok()) {
      errors->AddError(child_policy_config.status().message());
      return;
    }
    child_policy_ = std::move(*child_policy_config);
  }

  absl::string_view name() const override { return kGrpclb; }

  RefCountedPtr<LoadBalancingPolicy::Config> child_policy() const {
    return child_policy_;
  }

  const std::string& service_name() const { return service_name_; }

 private:
  RefCountedPtr<LoadBalancingPolicy::Config> child_policy_;
  std::string service_name_;
};

class GrpcLb final : public LoadBalancingPolicy {
 public:
  explicit GrpcLb(Args args);

  absl::string_view name() const override { return kGrpclb; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ResetBackoffLocked() override;

 private:

  class BalancerCallState final
      : public InternallyRefCounted<BalancerCallState> {
   public:
    explicit BalancerCallState(
        RefCountedPtr<LoadBalancingPolicy> parent_grpclb_policy);
    ~BalancerCallState() override;

    void Orphan() override;

    void StartQuery();

    GrpcLbClientStats* client_stats() const { return client_stats_.get(); }

    bool seen_initial_response() const { return seen_initial_response_; }
    bool seen_serverlist() const { return seen_serverlist_; }

   private:
    GrpcLb* grpclb_policy() const {
      return static_cast<GrpcLb*>(grpclb_policy_.get());
    }

    void ScheduleNextClientLoadReportLocked();
    void SendClientLoadReportLocked();

    void MaybeSendClientLoadReportLocked();

    static void ClientLoadReportDone(void* arg, grpc_error_handle error);
    static void OnInitialRequestSent(void* arg, grpc_error_handle error);
    static void OnBalancerMessageReceived(void* arg, grpc_error_handle error);
    static void OnBalancerStatusReceived(void* arg, grpc_error_handle error);

    void ClientLoadReportDoneLocked(grpc_error_handle error);
    void OnInitialRequestSentLocked();
    void OnBalancerMessageReceivedLocked();
    void OnBalancerStatusReceivedLocked(grpc_error_handle error);

    RefCountedPtr<LoadBalancingPolicy> grpclb_policy_;

    grpc_call* lb_call_ = nullptr;

    grpc_metadata_array lb_initial_metadata_recv_;

    grpc_byte_buffer* send_message_payload_ = nullptr;
    grpc_closure lb_on_initial_request_sent_;

    grpc_byte_buffer* recv_message_payload_ = nullptr;
    grpc_closure lb_on_balancer_message_received_;
    bool seen_initial_response_ = false;
    bool seen_serverlist_ = false;

    grpc_closure lb_on_balancer_status_received_;
    grpc_metadata_array lb_trailing_metadata_recv_;
    grpc_status_code lb_call_status_;
    grpc_slice lb_call_status_details_;

    RefCountedPtr<GrpcLbClientStats> client_stats_;
    Duration client_stats_report_interval_;
    std::optional<EventEngine::TaskHandle> client_load_report_handle_;
    bool last_client_load_report_counters_were_zero_ = false;
    bool client_load_report_is_due_ = false;

    grpc_closure client_load_report_done_closure_;
  };

  class SubchannelWrapper final : public DelegatingSubchannel {
   public:
    SubchannelWrapper(RefCountedPtr<SubchannelInterface> subchannel,
                      RefCountedPtr<GrpcLb> lb_policy,
                      grpc_event_engine::experimental::Slice lb_token,
                      RefCountedPtr<GrpcLbClientStats> client_stats)
        : DelegatingSubchannel(std::move(subchannel)),
          lb_policy_(std::move(lb_policy)),
          lb_token_(std::move(lb_token)),
          client_stats_(std::move(client_stats)) {}

    const grpc_event_engine::experimental::Slice& lb_token() const {
      return lb_token_;
    }
    GrpcLbClientStats* client_stats() const { return client_stats_.get(); }

   private:
    void Orphaned() override {
      lb_policy_->work_serializer()->Run(
          [self = WeakRefAsSubclass<SubchannelWrapper>()]() {
            if (!self->lb_policy_->shutting_down_) {
              self->lb_policy_->CacheDeletedSubchannelLocked(
                  self->wrapped_subchannel());
            }
          });
    }

    RefCountedPtr<GrpcLb> lb_policy_;
    grpc_event_engine::experimental::Slice lb_token_;
    RefCountedPtr<GrpcLbClientStats> client_stats_;
  };

  class TokenAndClientStatsArg final
      : public RefCounted<TokenAndClientStatsArg> {
   public:
    TokenAndClientStatsArg(grpc_event_engine::experimental::Slice lb_token,
                           RefCountedPtr<GrpcLbClientStats> client_stats)
        : lb_token_(std::move(lb_token)),
          client_stats_(std::move(client_stats)) {}

    static absl::string_view ChannelArgName() {
      return GRPC_ARG_NO_SUBCHANNEL_PREFIX "grpclb_token_and_client_stats";
    }

    static int ChannelArgsCompare(const TokenAndClientStatsArg* a,
                                  const TokenAndClientStatsArg* b) {
      int r =
          a->lb_token_.as_string_view().compare(b->lb_token_.as_string_view());
      if (r != 0) return r;
      return QsortCompare(a->client_stats_.get(), b->client_stats_.get());
    }

    const grpc_event_engine::experimental::Slice& lb_token() const {
      return lb_token_;
    }
    RefCountedPtr<GrpcLbClientStats> client_stats() const {
      return client_stats_;
    }

   private:
    grpc_event_engine::experimental::Slice lb_token_;
    RefCountedPtr<GrpcLbClientStats> client_stats_;
  };

  class Serverlist final : public RefCounted<Serverlist> {
   public:

    explicit Serverlist(std::vector<GrpcLbServer> serverlist)
        : serverlist_(std::move(serverlist)) {}

    bool operator==(const Serverlist& other) const;

    const std::vector<GrpcLbServer>& serverlist() const { return serverlist_; }

    std::string AsText() const;

    std::shared_ptr<EndpointAddressesIterator> GetServerAddressList(
        GrpcLbClientStats* client_stats);

    bool ContainsAllDropEntries() const;

    // Note: This is called from the picker, NOT from inside the control

    const char* ShouldDrop();

   private:
    class AddressIterator;

    std::vector<GrpcLbServer> serverlist_;

    std::atomic<size_t> drop_index_{0};
  };

  class Picker final : public SubchannelPicker {
   public:
    Picker(RefCountedPtr<Serverlist> serverlist,
           RefCountedPtr<SubchannelPicker> child_picker,
           RefCountedPtr<GrpcLbClientStats> client_stats)
        : serverlist_(std::move(serverlist)),
          child_picker_(std::move(child_picker)),
          client_stats_(std::move(client_stats)) {}

    PickResult Pick(PickArgs args) override;

   private:

    class SubchannelCallTracker final : public SubchannelCallTrackerInterface {
     public:
      SubchannelCallTracker(
          RefCountedPtr<GrpcLbClientStats> client_stats,
          std::unique_ptr<SubchannelCallTrackerInterface> original_call_tracker)
          : client_stats_(std::move(client_stats)),
            original_call_tracker_(std::move(original_call_tracker)) {}

      void Start() override {
        if (original_call_tracker_ != nullptr) {
          original_call_tracker_->Start();
        }

        client_stats_.release();
      }

      void Finish(FinishArgs args) override {
        if (original_call_tracker_ != nullptr) {
          original_call_tracker_->Finish(args);
        }
      }

     private:
      RefCountedPtr<GrpcLbClientStats> client_stats_;
      std::unique_ptr<SubchannelCallTrackerInterface> original_call_tracker_;
    };

    RefCountedPtr<Serverlist> serverlist_;

    RefCountedPtr<SubchannelPicker> child_picker_;
    RefCountedPtr<GrpcLbClientStats> client_stats_;
  };

  class Helper final
      : public ParentOwningDelegatingChannelControlHelper<GrpcLb> {
   public:
    explicit Helper(RefCountedPtr<GrpcLb> parent)
        : ParentOwningDelegatingChannelControlHelper(std::move(parent)) {}

    RefCountedPtr<SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const ChannelArgs& per_address_args, const ChannelArgs& args) override;
    void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                     RefCountedPtr<SubchannelPicker> picker) override;
    void RequestReresolution() override;
  };

  class StateWatcher final : public AsyncConnectivityStateWatcherInterface {
   public:
    explicit StateWatcher(RefCountedPtr<GrpcLb> parent)
        : AsyncConnectivityStateWatcherInterface(parent->work_serializer()),
          parent_(std::move(parent)) {}

    ~StateWatcher() override { parent_.reset(DEBUG_LOCATION, "StateWatcher"); }

   private:
    void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                   const absl::Status& status) override {
      if (parent_->fallback_at_startup_checks_pending_ &&
          new_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {

        GRPC_TRACE_LOG(glb, INFO)
            << "[grpclb " << parent_.get()
            << "] balancer channel in state:TRANSIENT_FAILURE ("
            << status.ToString() << "); entering fallback mode";
        parent_->fallback_at_startup_checks_pending_ = false;
        parent_->channel_control_helper()->GetEventEngine()->Cancel(
            *parent_->lb_fallback_timer_handle_);
        parent_->fallback_mode_ = true;
        parent_->CreateOrUpdateChildPolicyLocked();

        parent_->CancelBalancerChannelConnectivityWatchLocked();
      }
    }

    RefCountedPtr<GrpcLb> parent_;
  };

  class NullLbTokenEndpointIterator;

  void ShutdownLocked() override;

  absl::Status UpdateBalancerChannelLocked();

  void CancelBalancerChannelConnectivityWatchLocked();

  void MaybeEnterFallbackModeAfterStartup();
  void OnFallbackTimerLocked();

  void StartBalancerCallLocked();
  void StartBalancerCallRetryTimerLocked();
  void OnBalancerCallRetryTimerLocked();

  ChannelArgs CreateChildPolicyArgsLocked(
      bool is_backend_from_grpclb_load_balancer);
  OrphanablePtr<LoadBalancingPolicy> CreateChildPolicyLocked(
      const ChannelArgs& args);
  void CreateOrUpdateChildPolicyLocked();

  void CacheDeletedSubchannelLocked(
      RefCountedPtr<SubchannelInterface> subchannel);
  void StartSubchannelCacheTimerLocked();
  void OnSubchannelCacheTimerLocked();

  RefCountedPtr<GrpcLbConfig> config_;

  ChannelArgs args_;

  bool shutting_down_ = false;

  RefCountedPtr<Channel> lb_channel_;
  StateWatcher* watcher_ = nullptr;

  RefCountedPtr<FakeResolverResponseGenerator> response_generator_;

  RefCountedPtr<channelz::ChannelNode> parent_channelz_node_;

  OrphanablePtr<BalancerCallState> lb_calld_;

  const Duration lb_call_timeout_;

  BackOff lb_call_backoff_;
  std::optional<EventEngine::TaskHandle> lb_call_retry_timer_handle_;

  RefCountedPtr<Serverlist> serverlist_;

  bool fallback_mode_ = false;

  absl::StatusOr<std::shared_ptr<NullLbTokenEndpointIterator>>
      fallback_backend_addresses_;

  std::string resolution_note_;

  const Duration fallback_at_startup_timeout_;
  bool fallback_at_startup_checks_pending_ = false;
  std::optional<EventEngine::TaskHandle> lb_fallback_timer_handle_;

  OrphanablePtr<LoadBalancingPolicy> child_policy_;

  bool child_policy_ready_ = false;

  const Duration subchannel_cache_interval_;
  std::map<Timestamp ,
           std::vector<RefCountedPtr<SubchannelInterface>>>
      cached_subchannels_;
  std::optional<EventEngine::TaskHandle> subchannel_cache_timer_handle_;
};

bool IsServerValid(const GrpcLbServer& server, size_t idx, bool log) {
  if (server.drop) return false;
  if (GPR_UNLIKELY(server.port >> 16 != 0)) {
    if (log) {
      LOG(ERROR) << "Invalid port '" << server.port << "' at index " << idx
                 << " of serverlist. Ignoring.";
    }
    return false;
  }
  if (GPR_UNLIKELY(server.ip_size != 4 && server.ip_size != 16)) {
    if (log) {
      LOG(ERROR) << "Expected IP to be 4 or 16 bytes, got " << server.ip_size
                 << " at index " << idx << " of serverlist. Ignoring";
    }
    return false;
  }
  return true;
}

void ParseServer(const GrpcLbServer& server, grpc_resolved_address* addr) {
  memset(addr, 0, sizeof(*addr));
  if (server.drop) return;
  const uint16_t netorder_port = grpc_htons(static_cast<uint16_t>(server.port));

  if (server.ip_size == 4) {
    addr->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in));
    grpc_sockaddr_in* addr4 = reinterpret_cast<grpc_sockaddr_in*>(&addr->addr);
    addr4->sin_family = GRPC_AF_INET;
    memcpy(&addr4->sin_addr, server.ip_addr, server.ip_size);
    addr4->sin_port = netorder_port;
  } else if (server.ip_size == 16) {
    addr->len = static_cast<socklen_t>(sizeof(grpc_sockaddr_in6));
    grpc_sockaddr_in6* addr6 =
        reinterpret_cast<grpc_sockaddr_in6*>(&addr->addr);
    addr6->sin6_family = GRPC_AF_INET6;
    memcpy(&addr6->sin6_addr, server.ip_addr, server.ip_size);
    addr6->sin6_port = netorder_port;
  }
}

class GrpcLb::Serverlist::AddressIterator final
    : public EndpointAddressesIterator {
 public:
  AddressIterator(RefCountedPtr<Serverlist> serverlist,
                  RefCountedPtr<GrpcLbClientStats> client_stats)
      : serverlist_(std::move(serverlist)),
        client_stats_(std::move(client_stats)) {}

  void ForEach(absl::FunctionRef<void(const EndpointAddresses&)> callback)
      const override {
    for (size_t i = 0; i < serverlist_->serverlist_.size(); ++i) {
      const GrpcLbServer& server = serverlist_->serverlist_[i];
      if (!IsServerValid(server, i, false)) continue;

      grpc_resolved_address addr;
      ParseServer(server, &addr);

      const size_t lb_token_length = strnlen(
          server.load_balance_token, GPR_ARRAY_SIZE(server.load_balance_token));
      auto lb_token = grpc_event_engine::experimental::Slice::FromCopiedBuffer(
          server.load_balance_token, lb_token_length);
      if (lb_token.empty()) {
        auto addr_uri = grpc_sockaddr_to_uri(&addr);
        GRPC_TRACE_LOG(glb, INFO)
            << "Missing LB token for backend address '"
            << (addr_uri.ok() ? *addr_uri : addr_uri.status().ToString())
            << "'. The empty token will be used instead";
      }

      callback(EndpointAddresses(
          addr, ChannelArgs().SetObject(MakeRefCounted<TokenAndClientStatsArg>(
                    std::move(lb_token), client_stats_))));
    }
  }

 private:
  RefCountedPtr<Serverlist> serverlist_;
  RefCountedPtr<GrpcLbClientStats> client_stats_;
};

bool GrpcLb::Serverlist::operator==(const Serverlist& other) const {
  return serverlist_ == other.serverlist_;
}

std::string GrpcLb::Serverlist::AsText() const {
  std::vector<std::string> entries;
  for (size_t i = 0; i < serverlist_.size(); ++i) {
    const GrpcLbServer& server = serverlist_[i];
    std::string ipport;
    if (server.drop) {
      ipport = "(drop)";
    } else {
      grpc_resolved_address addr;
      ParseServer(server, &addr);
      auto addr_str = grpc_sockaddr_to_string(&addr, false);
      ipport = addr_str.ok() ? *addr_str : addr_str.status().ToString();
    }
    entries.push_back(absl::StrFormat("  %" PRIuPTR ": %s token=%s\n", i,
                                      ipport, server.load_balance_token));
  }
  return absl::StrJoin(entries, "");
}

std::shared_ptr<EndpointAddressesIterator>
GrpcLb::Serverlist::GetServerAddressList(GrpcLbClientStats* client_stats) {
  RefCountedPtr<GrpcLbClientStats> stats;
  if (client_stats != nullptr) stats = client_stats->Ref();
  return std::make_shared<AddressIterator>(Ref(), std::move(stats));
}

bool GrpcLb::Serverlist::ContainsAllDropEntries() const {
  if (serverlist_.empty()) return false;
  for (const GrpcLbServer& server : serverlist_) {
    if (!server.drop) return false;
  }
  return true;
}

const char* GrpcLb::Serverlist::ShouldDrop() {
  if (serverlist_.empty()) return nullptr;
  size_t index = drop_index_.fetch_add(1, std::memory_order_relaxed);
  GrpcLbServer& server = serverlist_[index % serverlist_.size()];
  return server.drop ? server.load_balance_token : nullptr;
}

GrpcLb::PickResult GrpcLb::Picker::Pick(PickArgs args) {

  const char* drop_token =
      serverlist_ == nullptr ? nullptr : serverlist_->ShouldDrop();
  if (drop_token != nullptr) {

    if (client_stats_ != nullptr) {
      client_stats_->AddCallDropped(drop_token);
    }
    return PickResult::Drop(
        absl::UnavailableError("drop directed by grpclb balancer"));
  }

  PickResult result = child_picker_->Pick(args);

  auto* complete_pick = std::get_if<PickResult::Complete>(&result.result);
  if (complete_pick != nullptr) {
    const SubchannelWrapper* subchannel_wrapper =
        static_cast<SubchannelWrapper*>(complete_pick->subchannel.get());

    GrpcLbClientStats* client_stats = subchannel_wrapper->client_stats();
    if (client_stats != nullptr) {
      complete_pick->subchannel_call_tracker =
          std::make_unique<SubchannelCallTracker>(
              client_stats->Ref(),
              std::move(complete_pick->subchannel_call_tracker));

      complete_pick->metadata_mutations.Set(
          GrpcLbClientStatsMetadata::key(),
          grpc_event_engine::experimental::Slice(grpc_slice_from_static_buffer(
              reinterpret_cast<const char*>(client_stats), 0)));

      client_stats->AddCallStarted();
    }

    if (!subchannel_wrapper->lb_token().empty()) {
      complete_pick->metadata_mutations.Set(
          LbTokenMetadata::key(), subchannel_wrapper->lb_token().Ref());
    }

    complete_pick->subchannel = subchannel_wrapper->wrapped_subchannel();
  }
  return result;
}

RefCountedPtr<SubchannelInterface> GrpcLb::Helper::CreateSubchannel(
    const grpc_resolved_address& address, const ChannelArgs& per_address_args,
    const ChannelArgs& args) {
  if (parent()->shutting_down_) return nullptr;
  const auto* arg = per_address_args.GetObject<TokenAndClientStatsArg>();
  if (arg == nullptr) {
    auto addr_str = grpc_sockaddr_to_string(&address, false);
    Crash(
        absl::StrFormat("[grpclb %p] no TokenAndClientStatsArg for address %s",
                        parent(), addr_str.value_or("N/A").c_str()));
  }
  return MakeRefCounted<SubchannelWrapper>(
      parent()->channel_control_helper()->CreateSubchannel(
          address, per_address_args, args),
      parent()->RefAsSubclass<GrpcLb>(DEBUG_LOCATION, "SubchannelWrapper"),
      arg->lb_token().Ref(), arg->client_stats());
}

void GrpcLb::Helper::UpdateState(grpc_connectivity_state state,
                                 const absl::Status& status,
                                 RefCountedPtr<SubchannelPicker> picker) {
  if (parent()->shutting_down_) return;

  parent()->child_policy_ready_ = state == GRPC_CHANNEL_READY;

  parent()->MaybeEnterFallbackModeAfterStartup();

  RefCountedPtr<Serverlist> serverlist;
  if (state == GRPC_CHANNEL_READY ||
      (parent()->serverlist_ != nullptr &&
       parent()->serverlist_->ContainsAllDropEntries())) {
    serverlist = parent()->serverlist_;
  }
  RefCountedPtr<GrpcLbClientStats> client_stats;
  if (parent()->lb_calld_ != nullptr &&
      parent()->lb_calld_->client_stats() != nullptr) {
    client_stats = parent()->lb_calld_->client_stats()->Ref();
  }
  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << parent() << " helper " << this
      << "] state=" << ConnectivityStateName(state) << " (" << status.ToString()
      << ") wrapping child picker " << picker.get()
      << " (serverlist=" << serverlist.get()
      << ", client_stats=" << client_stats.get() << ")";
  parent()->channel_control_helper()->UpdateState(
      state, status,
      MakeRefCounted<Picker>(std::move(serverlist), std::move(picker),
                             std::move(client_stats)));
}

void GrpcLb::Helper::RequestReresolution() {
  if (parent()->shutting_down_) return;

  if (!parent()->fallback_mode_) return;
  parent()->channel_control_helper()->RequestReresolution();
}

GrpcLb::BalancerCallState::BalancerCallState(
    RefCountedPtr<LoadBalancingPolicy> parent_grpclb_policy)
    : InternallyRefCounted<BalancerCallState>(
          GRPC_TRACE_FLAG_ENABLED(glb) ? "BalancerCallState" : nullptr),
      grpclb_policy_(std::move(parent_grpclb_policy)) {
  CHECK(grpclb_policy_ != nullptr);
  CHECK(!grpclb_policy()->shutting_down_);

  GRPC_CLOSURE_INIT(&lb_on_initial_request_sent_, OnInitialRequestSent, this,
                    grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&lb_on_balancer_message_received_,
                    OnBalancerMessageReceived, this, grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&lb_on_balancer_status_received_, OnBalancerStatusReceived,
                    this, grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&client_load_report_done_closure_, ClientLoadReportDone,
                    this, grpc_schedule_on_exec_ctx);
  const Timestamp deadline =
      grpclb_policy()->lb_call_timeout_ == Duration::Zero()
          ? Timestamp::InfFuture()
          : Timestamp::Now() + grpclb_policy()->lb_call_timeout_;
  lb_call_ = grpclb_policy()->lb_channel_->CreateCall(
      nullptr, GRPC_PROPAGATE_DEFAULTS,
      nullptr, grpclb_policy_->interested_parties(),
      Slice::FromStaticString("/grpc.lb.v1.LoadBalancer/BalanceLoad"),
      std::nullopt, deadline, true);

  upb::Arena arena;
  grpc_slice request_payload_slice = GrpcLbRequestCreate(
      grpclb_policy()->config_->service_name().empty()
          ? grpclb_policy()->channel_control_helper()->GetAuthority()
          : grpclb_policy()->config_->service_name(),
      arena.ptr());
  send_message_payload_ =
      grpc_raw_byte_buffer_create(&request_payload_slice, 1);
  CSliceUnref(request_payload_slice);

  grpc_metadata_array_init(&lb_initial_metadata_recv_);
  grpc_metadata_array_init(&lb_trailing_metadata_recv_);
}

GrpcLb::BalancerCallState::~BalancerCallState() {
  CHECK_NE(lb_call_, nullptr);
  grpc_call_unref(lb_call_);
  grpc_metadata_array_destroy(&lb_initial_metadata_recv_);
  grpc_metadata_array_destroy(&lb_trailing_metadata_recv_);
  grpc_byte_buffer_destroy(send_message_payload_);
  grpc_byte_buffer_destroy(recv_message_payload_);
  CSliceUnref(lb_call_status_details_);
}

void GrpcLb::BalancerCallState::Orphan() {
  CHECK_NE(lb_call_, nullptr);

  grpc_call_cancel_internal(lb_call_);
  if (client_load_report_handle_.has_value() &&
      grpclb_policy()->channel_control_helper()->GetEventEngine()->Cancel(
          client_load_report_handle_.value())) {
    Unref(DEBUG_LOCATION, "client_load_report cancelled");
  }

}

void GrpcLb::BalancerCallState::StartQuery() {
  CHECK_NE(lb_call_, nullptr);
  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << grpclb_policy_.get() << "] lb_calld=" << this
      << ": Starting LB call " << lb_call_;

  grpc_call_error call_error;
  grpc_op ops[3];
  memset(ops, 0, sizeof(ops));

  grpc_op* op = ops;
  op->op = GRPC_OP_SEND_INITIAL_METADATA;
  op->data.send_initial_metadata.count = 0;
  op->flags = GRPC_INITIAL_METADATA_WAIT_FOR_READY |
              GRPC_INITIAL_METADATA_WAIT_FOR_READY_EXPLICITLY_SET;
  op->reserved = nullptr;
  op++;

  CHECK_NE(send_message_payload_, nullptr);
  op->op = GRPC_OP_SEND_MESSAGE;
  op->data.send_message.send_message = send_message_payload_;
  op->flags = 0;
  op->reserved = nullptr;
  op++;

  auto self = Ref(DEBUG_LOCATION, "on_initial_request_sent");
  self.release();
  call_error = grpc_call_start_batch_and_execute(lb_call_, ops,
                                                 static_cast<size_t>(op - ops),
                                                 &lb_on_initial_request_sent_);
  CHECK_EQ(call_error, GRPC_CALL_OK);

  op = ops;
  op->op = GRPC_OP_RECV_INITIAL_METADATA;
  op->data.recv_initial_metadata.recv_initial_metadata =
      &lb_initial_metadata_recv_;
  op->flags = 0;
  op->reserved = nullptr;
  op++;

  op->op = GRPC_OP_RECV_MESSAGE;
  op->data.recv_message.recv_message = &recv_message_payload_;
  op->flags = 0;
  op->reserved = nullptr;
  op++;

  self = Ref(DEBUG_LOCATION, "on_message_received");
  self.release();
  call_error = grpc_call_start_batch_and_execute(
      lb_call_, ops, static_cast<size_t>(op - ops),
      &lb_on_balancer_message_received_);
  CHECK_EQ(call_error, GRPC_CALL_OK);

  op = ops;
  op->op = GRPC_OP_RECV_STATUS_ON_CLIENT;
  op->data.recv_status_on_client.trailing_metadata =
      &lb_trailing_metadata_recv_;
  op->data.recv_status_on_client.status = &lb_call_status_;
  op->data.recv_status_on_client.status_details = &lb_call_status_details_;
  op->flags = 0;
  op->reserved = nullptr;
  op++;

  call_error = grpc_call_start_batch_and_execute(
      lb_call_, ops, static_cast<size_t>(op - ops),
      &lb_on_balancer_status_received_);
  CHECK_EQ(call_error, GRPC_CALL_OK);
}

void GrpcLb::BalancerCallState::ScheduleNextClientLoadReportLocked() {
  client_load_report_handle_ =
      grpclb_policy()->channel_control_helper()->GetEventEngine()->RunAfter(
          client_stats_report_interval_, [this] {
            ExecCtx exec_ctx;
            grpclb_policy()->work_serializer()->Run(
                [this] { MaybeSendClientLoadReportLocked(); });
          });
}

void GrpcLb::BalancerCallState::MaybeSendClientLoadReportLocked() {
  client_load_report_handle_.reset();
  if (this != grpclb_policy()->lb_calld_.get()) {
    Unref(DEBUG_LOCATION, "client_load_report");
    return;
  }

  if (send_message_payload_ == nullptr) {
    SendClientLoadReportLocked();
  } else {
    client_load_report_is_due_ = true;
  }
}

void GrpcLb::BalancerCallState::SendClientLoadReportLocked() {

  CHECK_EQ(send_message_payload_, nullptr);

  int64_t num_calls_started;
  int64_t num_calls_finished;
  int64_t num_calls_finished_with_client_failed_to_send;
  int64_t num_calls_finished_known_received;
  std::unique_ptr<GrpcLbClientStats::DroppedCallCounts> drop_token_counts;
  client_stats_->Get(&num_calls_started, &num_calls_finished,
                     &num_calls_finished_with_client_failed_to_send,
                     &num_calls_finished_known_received, &drop_token_counts);

  if (num_calls_started == 0 && num_calls_finished == 0 &&
      num_calls_finished_with_client_failed_to_send == 0 &&
      num_calls_finished_known_received == 0 &&
      (drop_token_counts == nullptr || drop_token_counts->empty())) {
    if (last_client_load_report_counters_were_zero_) {
      ScheduleNextClientLoadReportLocked();
      return;
    }
    last_client_load_report_counters_were_zero_ = true;
  } else {
    last_client_load_report_counters_were_zero_ = false;
  }

  upb::Arena arena;
  grpc_slice request_payload_slice = GrpcLbLoadReportRequestCreate(
      num_calls_started, num_calls_finished,
      num_calls_finished_with_client_failed_to_send,
      num_calls_finished_known_received, drop_token_counts.get(), arena.ptr());
  send_message_payload_ =
      grpc_raw_byte_buffer_create(&request_payload_slice, 1);
  CSliceUnref(request_payload_slice);

  grpc_op op;
  memset(&op, 0, sizeof(op));
  op.op = GRPC_OP_SEND_MESSAGE;
  op.data.send_message.send_message = send_message_payload_;
  grpc_call_error call_error = grpc_call_start_batch_and_execute(
      lb_call_, &op, 1, &client_load_report_done_closure_);
  if (GPR_UNLIKELY(call_error != GRPC_CALL_OK)) {
    LOG(ERROR) << "[grpclb " << grpclb_policy_.get() << "] lb_calld=" << this
               << " call_error=" << call_error << " sending client load report";
    CHECK_EQ(call_error, GRPC_CALL_OK);
  }
}

void GrpcLb::BalancerCallState::ClientLoadReportDone(void* arg,
                                                     grpc_error_handle error) {
  BalancerCallState* lb_calld = static_cast<BalancerCallState*>(arg);
  lb_calld->grpclb_policy()->work_serializer()->Run(
      [lb_calld, error]() { lb_calld->ClientLoadReportDoneLocked(error); });
}

void GrpcLb::BalancerCallState::ClientLoadReportDoneLocked(
    grpc_error_handle error) {
  grpc_byte_buffer_destroy(send_message_payload_);
  send_message_payload_ = nullptr;
  if (!error.ok() || this != grpclb_policy()->lb_calld_.get()) {
    Unref(DEBUG_LOCATION, "client_load_report");
    return;
  }
  ScheduleNextClientLoadReportLocked();
}

void GrpcLb::BalancerCallState::OnInitialRequestSent(
    void* arg, grpc_error_handle ) {
  BalancerCallState* lb_calld = static_cast<BalancerCallState*>(arg);
  lb_calld->grpclb_policy()->work_serializer()->Run(
      [lb_calld]() { lb_calld->OnInitialRequestSentLocked(); });
}

void GrpcLb::BalancerCallState::OnInitialRequestSentLocked() {
  grpc_byte_buffer_destroy(send_message_payload_);
  send_message_payload_ = nullptr;

  if (client_load_report_is_due_ && this == grpclb_policy()->lb_calld_.get()) {
    SendClientLoadReportLocked();
    client_load_report_is_due_ = false;
  }
  Unref(DEBUG_LOCATION, "on_initial_request_sent");
}

void GrpcLb::BalancerCallState::OnBalancerMessageReceived(
    void* arg, grpc_error_handle ) {
  BalancerCallState* lb_calld = static_cast<BalancerCallState*>(arg);
  lb_calld->grpclb_policy()->work_serializer()->Run(
      [lb_calld]() { lb_calld->OnBalancerMessageReceivedLocked(); });
}

void GrpcLb::BalancerCallState::OnBalancerMessageReceivedLocked() {

  if (this != grpclb_policy()->lb_calld_.get() ||
      recv_message_payload_ == nullptr) {
    Unref(DEBUG_LOCATION, "on_message_received");
    return;
  }
  grpc_byte_buffer_reader bbr;
  grpc_byte_buffer_reader_init(&bbr, recv_message_payload_);
  grpc_slice response_slice = grpc_byte_buffer_reader_readall(&bbr);
  grpc_byte_buffer_reader_destroy(&bbr);
  grpc_byte_buffer_destroy(recv_message_payload_);
  recv_message_payload_ = nullptr;
  GrpcLbResponse response;
  upb::Arena arena;
  if (!GrpcLbResponseParse(response_slice, arena.ptr(), &response) ||
      (response.type == response.INITIAL && seen_initial_response_)) {
    if (absl::MinLogLevel() <= absl::LogSeverityAtLeast::kError) {
      char* response_slice_str =
          grpc_dump_slice(response_slice, GPR_DUMP_ASCII | GPR_DUMP_HEX);
      LOG(ERROR) << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
                 << ": Invalid LB response received: '" << response_slice_str
                 << "'. Ignoring.";
      gpr_free(response_slice_str);
    }
  } else {
    switch (response.type) {
      case response.INITIAL: {
        if (response.client_stats_report_interval != Duration::Zero()) {
          client_stats_report_interval_ = std::max(
              Duration::Seconds(1), response.client_stats_report_interval);
          GRPC_TRACE_LOG(glb, INFO)
              << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
              << ": Received initial LB response message; client load "
                 "reporting interval = "
              << client_stats_report_interval_.millis() << " milliseconds";
        } else {
          GRPC_TRACE_LOG(glb, INFO)
              << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
              << ": Received initial LB response message; client load "
                 "reporting NOT enabled";
        }
        seen_initial_response_ = true;
        break;
      }
      case response.SERVERLIST: {
        CHECK_NE(lb_call_, nullptr);
        auto serverlist_wrapper =
            MakeRefCounted<Serverlist>(std::move(response.serverlist));
        GRPC_TRACE_LOG(glb, INFO)
            << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
            << ": Serverlist with " << serverlist_wrapper->serverlist().size()
            << " servers received:\n"
            << serverlist_wrapper->AsText();
        seen_serverlist_ = true;

        if (client_stats_report_interval_ > Duration::Zero() &&
            client_stats_ == nullptr) {
          client_stats_ = MakeRefCounted<GrpcLbClientStats>();

          Ref(DEBUG_LOCATION, "client_load_report").release();
          ScheduleNextClientLoadReportLocked();
        }

        if (grpclb_policy()->serverlist_ != nullptr &&
            *grpclb_policy()->serverlist_ == *serverlist_wrapper) {
          GRPC_TRACE_LOG(glb, INFO)
              << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
              << ": Incoming server list identical to current, "
                 "ignoring.";
        } else {

          if (grpclb_policy()->fallback_mode_) {
            LOG(INFO) << "[grpclb " << grpclb_policy()
                      << "] Received response from balancer; exiting fallback "
                         "mode";
            grpclb_policy()->fallback_mode_ = false;
          }
          if (grpclb_policy()->fallback_at_startup_checks_pending_) {
            grpclb_policy()->fallback_at_startup_checks_pending_ = false;
            grpclb_policy()->channel_control_helper()->GetEventEngine()->Cancel(
                *grpclb_policy()->lb_fallback_timer_handle_);
            grpclb_policy()->CancelBalancerChannelConnectivityWatchLocked();
          }

          grpclb_policy()->serverlist_ = std::move(serverlist_wrapper);
          grpclb_policy()->CreateOrUpdateChildPolicyLocked();
        }
        break;
      }
      case response.FALLBACK: {
        if (!grpclb_policy()->fallback_mode_) {
          LOG(INFO) << "[grpclb " << grpclb_policy()
                    << "] Entering fallback mode as requested by balancer";
          if (grpclb_policy()->fallback_at_startup_checks_pending_) {
            grpclb_policy()->fallback_at_startup_checks_pending_ = false;
            grpclb_policy()->channel_control_helper()->GetEventEngine()->Cancel(
                *grpclb_policy()->lb_fallback_timer_handle_);
            grpclb_policy()->CancelBalancerChannelConnectivityWatchLocked();
          }
          grpclb_policy()->fallback_mode_ = true;
          grpclb_policy()->CreateOrUpdateChildPolicyLocked();

          grpclb_policy()->serverlist_.reset();
        }
        break;
      }
    }
  }
  CSliceUnref(response_slice);
  if (!grpclb_policy()->shutting_down_) {

    grpc_op op;
    memset(&op, 0, sizeof(op));
    op.op = GRPC_OP_RECV_MESSAGE;
    op.data.recv_message.recv_message = &recv_message_payload_;
    op.flags = 0;
    op.reserved = nullptr;

    const grpc_call_error call_error = grpc_call_start_batch_and_execute(
        lb_call_, &op, 1, &lb_on_balancer_message_received_);
    CHECK_EQ(call_error, GRPC_CALL_OK);
  } else {
    Unref(DEBUG_LOCATION, "on_message_received+grpclb_shutdown");
  }
}

void GrpcLb::BalancerCallState::OnBalancerStatusReceived(
    void* arg, grpc_error_handle error) {
  BalancerCallState* lb_calld = static_cast<BalancerCallState*>(arg);
  lb_calld->grpclb_policy()->work_serializer()->Run(
      [lb_calld, error]() { lb_calld->OnBalancerStatusReceivedLocked(error); });
}

void GrpcLb::BalancerCallState::OnBalancerStatusReceivedLocked(
    grpc_error_handle error) {
  CHECK_NE(lb_call_, nullptr);
  if (GRPC_TRACE_FLAG_ENABLED(glb)) {
    char* status_details = grpc_slice_to_c_string(lb_call_status_details_);
    LOG(INFO) << "[grpclb " << grpclb_policy() << "] lb_calld=" << this
              << ": Status from LB server received. Status = "
              << lb_call_status_ << ", details = '" << status_details
              << "', (lb_call: " << lb_call_ << "), error '"
              << StatusToString(error) << "'";
    gpr_free(status_details);
  }

  if (this == grpclb_policy()->lb_calld_.get()) {

    grpclb_policy()->lb_calld_.reset();
    if (grpclb_policy()->fallback_at_startup_checks_pending_) {
      CHECK(!seen_serverlist_);
      LOG(INFO) << "[grpclb " << grpclb_policy()
                << "] Balancer call finished without receiving serverlist; "
                   "entering fallback mode";
      grpclb_policy()->fallback_at_startup_checks_pending_ = false;
      grpclb_policy()->channel_control_helper()->GetEventEngine()->Cancel(
          *grpclb_policy()->lb_fallback_timer_handle_);
      grpclb_policy()->CancelBalancerChannelConnectivityWatchLocked();
      grpclb_policy()->fallback_mode_ = true;
      grpclb_policy()->CreateOrUpdateChildPolicyLocked();
    } else {

      grpclb_policy()->MaybeEnterFallbackModeAfterStartup();
    }
    CHECK(!grpclb_policy()->shutting_down_);
    grpclb_policy()->channel_control_helper()->RequestReresolution();
    if (seen_initial_response_) {

      grpclb_policy()->lb_call_backoff_.Reset();
      grpclb_policy()->StartBalancerCallLocked();
    } else {

      grpclb_policy()->StartBalancerCallRetryTimerLocked();
    }
  }
  Unref(DEBUG_LOCATION, "lb_call_ended");
}

EndpointAddressesList ExtractBalancerAddresses(const ChannelArgs& args) {
  const EndpointAddressesList* endpoints =
      FindGrpclbBalancerAddressesInChannelArgs(args);
  if (endpoints != nullptr) return *endpoints;
  return EndpointAddressesList();
}

ChannelArgs BuildBalancerChannelArgs(
    FakeResolverResponseGenerator* response_generator,
    const ChannelArgs& args) {
  ChannelArgs grpclb_channel_args;
  const grpc_channel_args* lb_channel_specific_args =
      args.GetPointer<grpc_channel_args>(
          GRPC_ARG_EXPERIMENTAL_GRPCLB_CHANNEL_ARGS);
  if (lb_channel_specific_args != nullptr) {
    grpclb_channel_args = ChannelArgs::FromC(lb_channel_specific_args);
  } else {

    grpclb_channel_args =
        args

            .Remove(GRPC_ARG_LB_POLICY_NAME)

            .Remove(GRPC_ARG_SERVICE_CONFIG)

            .Remove(GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR)

            .Remove(GRPC_ARG_DEFAULT_AUTHORITY)

            .Remove(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG)

            .Remove(GRPC_ARG_CHANNELZ_CHANNEL_NODE)

            .Remove(GRPC_ARG_CHANNEL_CREDENTIALS);
  }
  return grpclb_channel_args

      .Set(GRPC_ARG_ADDRESS_IS_GRPCLB_LOAD_BALANCER, 1)

      .Set(GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL, 1)

      .SetObject(response_generator->Ref());
}

GrpcLb::GrpcLb(Args args)
    : LoadBalancingPolicy(std::move(args)),
      response_generator_(MakeRefCounted<FakeResolverResponseGenerator>()),
      lb_call_timeout_(std::max(
          Duration::Zero(),
          channel_args()
              .GetDurationFromIntMillis(GRPC_ARG_GRPCLB_CALL_TIMEOUT_MS)
              .value_or(Duration::Zero()))),
      lb_call_backoff_(
          BackOff::Options()
              .set_initial_backoff(Duration::Seconds(
                  GRPC_GRPCLB_INITIAL_CONNECT_BACKOFF_SECONDS))
              .set_multiplier(GRPC_GRPCLB_RECONNECT_BACKOFF_MULTIPLIER)
              .set_jitter(GRPC_GRPCLB_RECONNECT_JITTER)
              .set_max_backoff(Duration::Seconds(
                  GRPC_GRPCLB_RECONNECT_MAX_BACKOFF_SECONDS))),
      fallback_at_startup_timeout_(std::max(
          Duration::Zero(),
          channel_args()
              .GetDurationFromIntMillis(GRPC_ARG_GRPCLB_FALLBACK_TIMEOUT_MS)
              .value_or(Duration::Milliseconds(
                  GRPC_GRPCLB_DEFAULT_FALLBACK_TIMEOUT_MS)))),
      subchannel_cache_interval_(std::max(
          Duration::Zero(),
          channel_args()
              .GetDurationFromIntMillis(
                  GRPC_ARG_GRPCLB_SUBCHANNEL_CACHE_INTERVAL_MS)
              .value_or(Duration::Milliseconds(
                  GRPC_GRPCLB_DEFAULT_SUBCHANNEL_DELETION_DELAY_MS)))) {
  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << this << "] Will use '"
      << std::string(channel_control_helper()->GetAuthority())
      << "' as the server name for LB request.";
}

void GrpcLb::ShutdownLocked() {
  shutting_down_ = true;
  lb_calld_.reset();
  if (subchannel_cache_timer_handle_.has_value()) {
    channel_control_helper()->GetEventEngine()->Cancel(
        *subchannel_cache_timer_handle_);
    subchannel_cache_timer_handle_.reset();
  }
  cached_subchannels_.clear();
  if (lb_call_retry_timer_handle_.has_value()) {
    channel_control_helper()->GetEventEngine()->Cancel(
        *lb_call_retry_timer_handle_);
  }
  if (fallback_at_startup_checks_pending_) {
    fallback_at_startup_checks_pending_ = false;
    channel_control_helper()->GetEventEngine()->Cancel(
        *lb_fallback_timer_handle_);
    CancelBalancerChannelConnectivityWatchLocked();
  }
  if (child_policy_ != nullptr) {
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     interested_parties());
    child_policy_.reset();
  }

  if (lb_channel_ != nullptr) {
    if (parent_channelz_node_ != nullptr) {
      channelz::ChannelNode* child_channelz_node = lb_channel_->channelz_node();
      CHECK_NE(child_channelz_node, nullptr);
      child_channelz_node->RemoveParent(parent_channelz_node_.get());
    }
    lb_channel_.reset();
  }
}

void GrpcLb::ResetBackoffLocked() {
  if (lb_channel_ != nullptr) {
    lb_channel_->ResetConnectionBackoff();
  }
  if (child_policy_ != nullptr) {
    child_policy_->ResetBackoffLocked();
  }
}

class GrpcLb::NullLbTokenEndpointIterator final
    : public EndpointAddressesIterator {
 public:
  explicit NullLbTokenEndpointIterator(
      std::shared_ptr<EndpointAddressesIterator> parent_it)
      : parent_it_(std::move(parent_it)) {}

  void ForEach(absl::FunctionRef<void(const EndpointAddresses&)> callback)
      const override {
    parent_it_->ForEach([&](const EndpointAddresses& endpoint) {
      GRPC_TRACE_LOG(glb, INFO)
          << "[grpclb " << this
          << "] fallback address: " << endpoint.ToString();
      callback(EndpointAddresses(endpoint.addresses(),
                                 endpoint.args().SetObject(empty_token_)));
    });
  }

 private:
  std::shared_ptr<EndpointAddressesIterator> parent_it_;
  RefCountedPtr<TokenAndClientStatsArg> empty_token_ =
      MakeRefCounted<TokenAndClientStatsArg>(
          grpc_event_engine::experimental::Slice(), nullptr);
};

absl::Status GrpcLb::UpdateLocked(UpdateArgs args) {
  GRPC_TRACE_LOG(glb, INFO) << "[grpclb " << this << "] received update";
  const bool is_initial_update = lb_channel_ == nullptr;
  config_ = args.config.TakeAsSubclass<GrpcLbConfig>();
  CHECK(config_ != nullptr);
  args_ = std::move(args.args);

  if (!args.addresses.ok()) {
    fallback_backend_addresses_ = args.addresses.status();
  } else {
    fallback_backend_addresses_ = std::make_shared<NullLbTokenEndpointIterator>(
        std::move(*args.addresses));
  }
  resolution_note_ = std::move(args.resolution_note);

  absl::Status status = UpdateBalancerChannelLocked();

  if (child_policy_ != nullptr) CreateOrUpdateChildPolicyLocked();

  if (is_initial_update) {
    fallback_at_startup_checks_pending_ = true;

    lb_fallback_timer_handle_ =
        channel_control_helper()->GetEventEngine()->RunAfter(
            fallback_at_startup_timeout_,
            [self = RefAsSubclass<GrpcLb>(DEBUG_LOCATION,
                                          "on_fallback_timer")]() mutable {
              ExecCtx exec_ctx;
              auto self_ptr = self.get();
              self_ptr->work_serializer()->Run([self = std::move(self)]() {
                self->OnFallbackTimerLocked();
              });
            });

    watcher_ =
        new StateWatcher(RefAsSubclass<GrpcLb>(DEBUG_LOCATION, "StateWatcher"));
    lb_channel_->AddConnectivityWatcher(
        GRPC_CHANNEL_IDLE,
        OrphanablePtr<AsyncConnectivityStateWatcherInterface>(watcher_));

    StartBalancerCallLocked();
  }
  return status;
}

absl::Status GrpcLb::UpdateBalancerChannelLocked() {

  EndpointAddressesList balancer_addresses = ExtractBalancerAddresses(args_);
  if (GRPC_TRACE_FLAG_ENABLED(glb)) {
    for (const auto& endpoint : balancer_addresses) {
      LOG(INFO) << "[grpclb " << this
                << "] balancer address: " << endpoint.ToString();
    }
  }
  absl::Status status;
  if (balancer_addresses.empty()) {
    status = absl::UnavailableError("balancer address list must be non-empty");
  }

  auto channel_credentials = channel_control_helper()->GetChannelCredentials();

  ChannelArgs lb_channel_args =
      BuildBalancerChannelArgs(response_generator_.get(), args_);

  if (lb_channel_ == nullptr) {
    std::string uri_str =
        absl::StrCat("fake:///", channel_control_helper()->GetAuthority());
    lb_channel_.reset(Channel::FromC(
        grpc_channel_create(uri_str.c_str(), channel_credentials.get(),
                            lb_channel_args.ToC().get())));
    CHECK(lb_channel_ != nullptr);

    channelz::ChannelNode* child_channelz_node = lb_channel_->channelz_node();
    auto parent_channelz_node = args_.GetObjectRef<channelz::ChannelNode>();
    if (child_channelz_node != nullptr && parent_channelz_node != nullptr) {
      child_channelz_node->AddParent(parent_channelz_node.get());
      parent_channelz_node_ = std::move(parent_channelz_node);
    }
  }

  Resolver::Result result;
  result.addresses = std::move(balancer_addresses);

  result.args = lb_channel_args.SetObject(std::move(channel_credentials));
  response_generator_->SetResponseAsync(std::move(result));

  return status;
}

void GrpcLb::CancelBalancerChannelConnectivityWatchLocked() {
  lb_channel_->RemoveConnectivityWatcher(watcher_);
}

void GrpcLb::StartBalancerCallLocked() {
  CHECK(lb_channel_ != nullptr);
  if (shutting_down_) return;

  CHECK(lb_calld_ == nullptr);
  lb_calld_ = MakeOrphanable<BalancerCallState>(Ref());
  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << this
      << "] Query for backends (lb_channel: " << lb_channel_.get()
      << ", lb_calld: " << lb_calld_.get() << ")";
  lb_calld_->StartQuery();
}

void GrpcLb::StartBalancerCallRetryTimerLocked() {
  Duration delay = lb_call_backoff_.NextAttemptDelay();
  if (GRPC_TRACE_FLAG_ENABLED(glb)) {
    LOG(INFO) << "[grpclb " << this << "] Connection to LB server lost...";
    if (delay > Duration::Zero()) {
      LOG(INFO) << "[grpclb " << this << "] ... retry_timer_active in "
                << delay.millis() << "ms.";
    } else {
      LOG(INFO) << "[grpclb " << this
                << "] ... retry_timer_active immediately.";
    }
  }
  lb_call_retry_timer_handle_ =
      channel_control_helper()->GetEventEngine()->RunAfter(
          delay,
          [self = RefAsSubclass<GrpcLb>(
               DEBUG_LOCATION, "on_balancer_call_retry_timer")]() mutable {
            ExecCtx exec_ctx;
            auto self_ptr = self.get();
            self_ptr->work_serializer()->Run([self = std::move(self)]() {
              self->OnBalancerCallRetryTimerLocked();
            });
          });
}

void GrpcLb::OnBalancerCallRetryTimerLocked() {
  lb_call_retry_timer_handle_.reset();
  if (!shutting_down_ && lb_calld_ == nullptr) {
    GRPC_TRACE_LOG(glb, INFO)
        << "[grpclb " << this << "] Restarting call to LB server";
    StartBalancerCallLocked();
  }
}

void GrpcLb::MaybeEnterFallbackModeAfterStartup() {

  if (!fallback_mode_ && !fallback_at_startup_checks_pending_ &&
      (lb_calld_ == nullptr || !lb_calld_->seen_serverlist()) &&
      !child_policy_ready_) {
    LOG(INFO) << "[grpclb " << this
              << "] lost contact with balancer and backends from most recent "
                 "serverlist; entering fallback mode";
    fallback_mode_ = true;
    CreateOrUpdateChildPolicyLocked();
  }
}

void GrpcLb::OnFallbackTimerLocked() {

  if (fallback_at_startup_checks_pending_ && !shutting_down_) {
    LOG(INFO) << "[grpclb " << this
              << "] No response from balancer after fallback timeout; "
                 "entering fallback mode";
    fallback_at_startup_checks_pending_ = false;
    CancelBalancerChannelConnectivityWatchLocked();
    fallback_mode_ = true;
    CreateOrUpdateChildPolicyLocked();
  }
}

ChannelArgs GrpcLb::CreateChildPolicyArgsLocked(
    bool is_backend_from_grpclb_load_balancer) {
  ChannelArgs r =
      args_
          .Set(GRPC_ARG_ADDRESS_IS_BACKEND_FROM_GRPCLB_LOAD_BALANCER,
               is_backend_from_grpclb_load_balancer)
          .Set(GRPC_ARG_GRPCLB_ENABLE_LOAD_REPORTING_FILTER, 1);
  if (is_backend_from_grpclb_load_balancer) {
    r = r.Set(GRPC_ARG_INHIBIT_HEALTH_CHECKING, 1);
  }
  return r;
}

OrphanablePtr<LoadBalancingPolicy> GrpcLb::CreateChildPolicyLocked(
    const ChannelArgs& args) {
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer = work_serializer();
  lb_policy_args.args = args;
  lb_policy_args.channel_control_helper =
      std::make_unique<Helper>(RefAsSubclass<GrpcLb>(DEBUG_LOCATION, "Helper"));
  OrphanablePtr<LoadBalancingPolicy> lb_policy =
      MakeOrphanable<ChildPolicyHandler>(std::move(lb_policy_args), &glb_trace);
  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << this << "] Created new child policy handler ("
      << lb_policy.get() << ")";

  grpc_pollset_set_add_pollset_set(lb_policy->interested_parties(),
                                   interested_parties());
  return lb_policy;
}

bool EndpointIteratorIsEmpty(const EndpointAddressesIterator& endpoints) {
  bool empty = true;
  endpoints.ForEach([&](const EndpointAddresses&) { empty = false; });
  return empty;
}

void GrpcLb::CreateOrUpdateChildPolicyLocked() {
  if (shutting_down_) return;

  UpdateArgs update_args;
  bool is_backend_from_grpclb_load_balancer = false;
  if (fallback_mode_) {

    update_args.addresses = fallback_backend_addresses_;
    if (fallback_backend_addresses_.ok() &&
        EndpointIteratorIsEmpty(**fallback_backend_addresses_)) {
      update_args.resolution_note = absl::StrCat(
          "grpclb in fallback mode without any fallback addresses: ",
          resolution_note_);
    }
  } else {
    update_args.addresses = serverlist_->GetServerAddressList(
        lb_calld_ == nullptr ? nullptr : lb_calld_->client_stats());
    is_backend_from_grpclb_load_balancer = true;
    if (update_args.addresses.ok() &&
        EndpointIteratorIsEmpty(**update_args.addresses)) {
      update_args.resolution_note = "empty serverlist from grpclb balancer";
    }
  }
  update_args.args =
      CreateChildPolicyArgsLocked(is_backend_from_grpclb_load_balancer);
  CHECK(update_args.args != ChannelArgs());
  update_args.config = config_->child_policy();

  if (child_policy_ == nullptr) {
    child_policy_ = CreateChildPolicyLocked(update_args.args);
  }

  GRPC_TRACE_LOG(glb, INFO)
      << "[grpclb " << this << "] Updating child policy handler "
      << child_policy_.get();

  (void)child_policy_->UpdateLocked(std::move(update_args));
}

void GrpcLb::CacheDeletedSubchannelLocked(
    RefCountedPtr<SubchannelInterface> subchannel) {
  Timestamp deletion_time = Timestamp::Now() + subchannel_cache_interval_;
  cached_subchannels_[deletion_time].push_back(std::move(subchannel));
  if (!subchannel_cache_timer_handle_.has_value()) {
    StartSubchannelCacheTimerLocked();
  }
}

void GrpcLb::StartSubchannelCacheTimerLocked() {
  CHECK(!cached_subchannels_.empty());
  subchannel_cache_timer_handle_ =
      channel_control_helper()->GetEventEngine()->RunAfter(
          cached_subchannels_.begin()->first - Timestamp::Now(),
          [self = RefAsSubclass<GrpcLb>(DEBUG_LOCATION,
                                        "OnSubchannelCacheTimer")]() mutable {
            ExecCtx exec_ctx;
            auto* self_ptr = self.get();
            self_ptr->work_serializer()->Run(
                [self = std::move(self)]() mutable {
                  self->OnSubchannelCacheTimerLocked();
                });
          });
}

void GrpcLb::OnSubchannelCacheTimerLocked() {
  if (subchannel_cache_timer_handle_.has_value()) {
    subchannel_cache_timer_handle_.reset();
    auto it = cached_subchannels_.begin();
    if (it != cached_subchannels_.end()) {
      GRPC_TRACE_LOG(glb, INFO)
          << "[grpclb " << this << "] removing " << it->second.size()
          << " subchannels from cache";
      cached_subchannels_.erase(it);
    }
    if (!cached_subchannels_.empty()) {
      StartSubchannelCacheTimerLocked();
      return;
    }
  }
}

class GrpcLbFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<GrpcLb>(std::move(args));
  }

  absl::string_view name() const override { return kGrpclb; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<GrpcLbConfig>>(
        json, JsonArgs(), "errors validating grpclb LB policy config");
  }
};

}

void RegisterGrpcLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<GrpcLbFactory>());
  builder->channel_init()
      ->RegisterFilter<ClientLoadReportingFilter>(GRPC_CLIENT_SUBCHANNEL)
      .IfChannelArg(GRPC_ARG_GRPCLB_ENABLE_LOAD_REPORTING_FILTER, false);
}

}
