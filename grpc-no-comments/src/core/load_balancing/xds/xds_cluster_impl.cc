
// Copyright 2018 gRPC authors.

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/xds/xds_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/xds/xds_config.h"
#include "src/core/resolver/xds/xds_resolver_attributes.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/match.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/ref_counted_string.h"
#include "src/core/util/sync.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_client_grpc.h"
#include "src/core/xds/grpc/xds_endpoint.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "src/core/xds/xds_client/xds_locality.h"

namespace grpc_core {

namespace {

class CircuitBreakerCallCounterMap final {
 public:
  using Key =
      std::pair<std::string , std::string >;

  class CallCounter final : public RefCounted<CallCounter> {
   public:
    explicit CallCounter(Key key) : key_(std::move(key)) {}
    ~CallCounter() override;

    uint32_t Load() {
      return concurrent_requests_.load(std::memory_order_seq_cst);
    }
    uint32_t Increment() { return concurrent_requests_.fetch_add(1); }
    void Decrement() { concurrent_requests_.fetch_sub(1); }

   private:
    Key key_;
    std::atomic<uint32_t> concurrent_requests_{0};
  };

  RefCountedPtr<CallCounter> GetOrCreate(const std::string& cluster,
                                         const std::string& eds_service_name);

 private:
  Mutex mu_;
  std::map<Key, CallCounter*> map_ ABSL_GUARDED_BY(mu_);
};

CircuitBreakerCallCounterMap* const g_call_counter_map =
    new CircuitBreakerCallCounterMap;

RefCountedPtr<CircuitBreakerCallCounterMap::CallCounter>
CircuitBreakerCallCounterMap::GetOrCreate(const std::string& cluster,
                                          const std::string& eds_service_name) {
  Key key(cluster, eds_service_name);
  RefCountedPtr<CallCounter> result;
  MutexLock lock(&mu_);
  auto it = map_.find(key);
  if (it == map_.end()) {
    it = map_.insert({key, nullptr}).first;
  } else {
    result = it->second->RefIfNonZero();
  }
  if (result == nullptr) {
    result = MakeRefCounted<CallCounter>(std::move(key));
    it->second = result.get();
  }
  return result;
}

CircuitBreakerCallCounterMap::CallCounter::~CallCounter() {
  MutexLock lock(&g_call_counter_map->mu_);
  auto it = g_call_counter_map->map_.find(key_);
  if (it != g_call_counter_map->map_.end() && it->second == this) {
    g_call_counter_map->map_.erase(it);
  }
}

constexpr absl::string_view kXdsClusterImpl = "xds_cluster_impl_experimental";

class XdsClusterImplLbConfig final : public LoadBalancingPolicy::Config {
 public:
  XdsClusterImplLbConfig() = default;

  XdsClusterImplLbConfig(const XdsClusterImplLbConfig&) = delete;
  XdsClusterImplLbConfig& operator=(const XdsClusterImplLbConfig&) = delete;

  XdsClusterImplLbConfig(XdsClusterImplLbConfig&& other) = delete;
  XdsClusterImplLbConfig& operator=(XdsClusterImplLbConfig&& other) = delete;

  absl::string_view name() const override { return kXdsClusterImpl; }

  const std::string& cluster_name() const { return cluster_name_; }
  RefCountedPtr<LoadBalancingPolicy::Config> child_policy() const {
    return child_policy_;
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  void JsonPostLoad(const Json& json, const JsonArgs& args,
                    ValidationErrors* errors);

 private:
  std::string cluster_name_;
  RefCountedPtr<LoadBalancingPolicy::Config> child_policy_;
};

class XdsClusterImplLb final : public LoadBalancingPolicy {
 public:
  XdsClusterImplLb(RefCountedPtr<GrpcXdsClient> xds_client, Args args);

  absl::string_view name() const override { return kXdsClusterImpl; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:
  class StatsSubchannelWrapper final : public DelegatingSubchannel {
   public:

    using LocalityData = std::variant<
        RefCountedStringValue ,
        RefCountedPtr<LrsClient::ClusterLocalityStats> >;

    StatsSubchannelWrapper(
        RefCountedPtr<SubchannelInterface> wrapped_subchannel,
        LocalityData locality_data, absl::string_view hostname)
        : DelegatingSubchannel(std::move(wrapped_subchannel)),
          locality_data_(std::move(locality_data)),
          hostname_(grpc_event_engine::experimental::Slice::FromCopiedString(
              hostname)) {}

    RefCountedStringValue locality() const {
      return Match(
          locality_data_,
          [](RefCountedStringValue locality) { return locality; },
          [](const RefCountedPtr<LrsClient::ClusterLocalityStats>&
                 locality_stats) {
            return locality_stats->locality_name()->human_readable_string();
          });
    }

    LrsClient::ClusterLocalityStats* locality_stats() const {
      return Match(
          locality_data_,
          [](const RefCountedStringValue&) {
            return static_cast<LrsClient::ClusterLocalityStats*>(nullptr);
          },
          [](const RefCountedPtr<LrsClient::ClusterLocalityStats>&
                 locality_stats) { return locality_stats.get(); });
    }

    const grpc_event_engine::experimental::Slice& hostname() const {
      return hostname_;
    }

   private:
    LocalityData locality_data_;
    grpc_event_engine::experimental::Slice hostname_;
  };

  class Picker final : public SubchannelPicker {
   public:
    Picker(XdsClusterImplLb* xds_cluster_impl_lb,
           RefCountedPtr<SubchannelPicker> picker);

    PickResult Pick(PickArgs args) override;

   private:
    class SubchannelCallTracker;

    RefCountedPtr<CircuitBreakerCallCounterMap::CallCounter> call_counter_;
    uint32_t max_concurrent_requests_;
    RefCountedStringValue service_telemetry_label_;
    RefCountedStringValue namespace_telemetry_label_;
    RefCountedPtr<XdsEndpointResource::DropConfig> drop_config_;
    RefCountedPtr<LrsClient::ClusterDropStats> drop_stats_;
    RefCountedPtr<SubchannelPicker> picker_;
  };

  class Helper final
      : public ParentOwningDelegatingChannelControlHelper<XdsClusterImplLb> {
   public:
    explicit Helper(RefCountedPtr<XdsClusterImplLb> xds_cluster_impl_policy)
        : ParentOwningDelegatingChannelControlHelper(
              std::move(xds_cluster_impl_policy)) {}

    RefCountedPtr<SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const ChannelArgs& per_address_args, const ChannelArgs& args) override;
    void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                     RefCountedPtr<SubchannelPicker> picker) override;
  };

  ~XdsClusterImplLb() override;

  void ShutdownLocked() override;

  void ResetState();
  void ReportTransientFailure(absl::Status status);

  OrphanablePtr<LoadBalancingPolicy> CreateChildPolicyLocked(
      const ChannelArgs& args);
  absl::Status UpdateChildPolicyLocked(
      absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> addresses,
      std::string resolution_note, const ChannelArgs& args);

  absl::StatusOr<RefCountedPtr<XdsCertificateProvider>>
  MaybeCreateCertificateProviderLocked(
      const XdsClusterResource& cluster_resource) const;

  void MaybeUpdatePickerLocked();

  RefCountedPtr<XdsClusterImplLbConfig> config_;
  std::shared_ptr<const XdsClusterResource> cluster_resource_;
  RefCountedStringValue service_telemetry_label_;
  RefCountedStringValue namespace_telemetry_label_;
  RefCountedPtr<XdsEndpointResource::DropConfig> drop_config_;

  RefCountedPtr<CircuitBreakerCallCounterMap::CallCounter> call_counter_;

  bool shutting_down_ = false;

  RefCountedPtr<GrpcXdsClient> xds_client_;

  RefCountedPtr<LrsClient::ClusterDropStats> drop_stats_;

  OrphanablePtr<LoadBalancingPolicy> child_policy_;

  grpc_connectivity_state state_ = GRPC_CHANNEL_IDLE;
  absl::Status status_;
  RefCountedPtr<SubchannelPicker> picker_;
};

class XdsClusterImplLb::Picker::SubchannelCallTracker final
    : public LoadBalancingPolicy::SubchannelCallTrackerInterface {
 public:
  SubchannelCallTracker(
      std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>
          original_subchannel_call_tracker,
      RefCountedPtr<LrsClient::ClusterLocalityStats> locality_stats,
      RefCountedPtr<CircuitBreakerCallCounterMap::CallCounter> call_counter)
      : original_subchannel_call_tracker_(
            std::move(original_subchannel_call_tracker)),
        locality_stats_(std::move(locality_stats)),
        call_counter_(std::move(call_counter)) {}

  ~SubchannelCallTracker() override {
    locality_stats_.reset(DEBUG_LOCATION, "SubchannelCallTracker");
    call_counter_.reset(DEBUG_LOCATION, "SubchannelCallTracker");
#ifndef NDEBUG
    DCHECK(!started_);
#endif
  }

  void Start() override {

    call_counter_->Increment();

    if (locality_stats_ != nullptr) {
      locality_stats_->AddCallStarted();
    }

    if (original_subchannel_call_tracker_ != nullptr) {
      original_subchannel_call_tracker_->Start();
    }
#ifndef NDEBUG
    started_ = true;
#endif
  }

  void Finish(FinishArgs args) override {

    if (original_subchannel_call_tracker_ != nullptr) {
      original_subchannel_call_tracker_->Finish(args);
    }

    if (locality_stats_ != nullptr) {
      locality_stats_->AddCallFinished(
          args.backend_metric_accessor->GetBackendMetricData(),
          !args.status.ok());
    }

    call_counter_->Decrement();
#ifndef NDEBUG
    started_ = false;
#endif
  }

 private:
  std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>
      original_subchannel_call_tracker_;
  RefCountedPtr<LrsClient::ClusterLocalityStats> locality_stats_;
  RefCountedPtr<CircuitBreakerCallCounterMap::CallCounter> call_counter_;
#ifndef NDEBUG
  bool started_ = false;
#endif
};

XdsClusterImplLb::Picker::Picker(XdsClusterImplLb* xds_cluster_impl_lb,
                                 RefCountedPtr<SubchannelPicker> picker)
    : call_counter_(xds_cluster_impl_lb->call_counter_),
      max_concurrent_requests_(
          xds_cluster_impl_lb->cluster_resource_->max_concurrent_requests),
      service_telemetry_label_(xds_cluster_impl_lb->service_telemetry_label_),
      namespace_telemetry_label_(
          xds_cluster_impl_lb->namespace_telemetry_label_),
      drop_config_(xds_cluster_impl_lb->drop_config_),
      drop_stats_(xds_cluster_impl_lb->drop_stats_),
      picker_(std::move(picker)) {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << xds_cluster_impl_lb
      << "] constructed new picker " << this;
}

LoadBalancingPolicy::PickResult XdsClusterImplLb::Picker::Pick(
    LoadBalancingPolicy::PickArgs args) {
  auto* call_state = static_cast<ClientChannelLbCallState*>(args.call_state);
  auto* call_attempt_tracer = call_state->GetCallAttemptTracer();
  if (call_attempt_tracer != nullptr) {
    call_attempt_tracer->SetOptionalLabel(
        ClientCallTracer::CallAttemptTracer::OptionalLabelKey::kXdsServiceName,
        service_telemetry_label_);
    call_attempt_tracer->SetOptionalLabel(
        ClientCallTracer::CallAttemptTracer::OptionalLabelKey::
            kXdsServiceNamespace,
        namespace_telemetry_label_);
  }

  const std::string* drop_category;
  if (drop_config_ != nullptr && drop_config_->ShouldDrop(&drop_category)) {
    if (drop_stats_ != nullptr) drop_stats_->AddCallDropped(*drop_category);
    return PickResult::Drop(absl::UnavailableError(
        absl::StrCat("EDS-configured drop: ", *drop_category)));
  }

  // Note: We check the value here, but we don't actually increment the

  if (call_counter_->Load() >= max_concurrent_requests_) {
    if (drop_stats_ != nullptr) drop_stats_->AddUncategorizedDrops();
    return PickResult::Drop(absl::UnavailableError("circuit breaker drop"));
  }

  if (picker_ == nullptr) {
    return PickResult::Fail(absl::InternalError(
        "xds_cluster_impl picker not given any child picker"));
  }

  PickResult result = picker_->Pick(args);
  auto* complete_pick = std::get_if<PickResult::Complete>(&result.result);
  if (complete_pick != nullptr) {
    auto* subchannel_wrapper =
        static_cast<StatsSubchannelWrapper*>(complete_pick->subchannel.get());

    if (call_attempt_tracer != nullptr) {
      call_attempt_tracer->SetOptionalLabel(
          ClientCallTracer::CallAttemptTracer::OptionalLabelKey::kLocality,
          subchannel_wrapper->locality());
    }

    RefCountedPtr<LrsClient::ClusterLocalityStats> locality_stats;
    if (subchannel_wrapper->locality_stats() != nullptr) {
      locality_stats = subchannel_wrapper->locality_stats()->Ref(
          DEBUG_LOCATION, "SubchannelCallTracker");
    }

    if (!subchannel_wrapper->hostname().empty()) {
      auto* route_state_attribute =
          call_state->GetCallAttribute<XdsRouteStateAttribute>();
      if (route_state_attribute != nullptr) {
        auto* route_action =
            std::get_if<XdsRouteConfigResource::Route::RouteAction>(
                &route_state_attribute->route().action);
        if (route_action != nullptr && route_action->auto_host_rewrite) {
          complete_pick->authority_override =
              subchannel_wrapper->hostname().Ref();
        }
      }
    }

    complete_pick->subchannel = subchannel_wrapper->wrapped_subchannel();

    complete_pick->subchannel_call_tracker =
        std::make_unique<SubchannelCallTracker>(
            std::move(complete_pick->subchannel_call_tracker),
            std::move(locality_stats),
            call_counter_->Ref(DEBUG_LOCATION, "SubchannelCallTracker"));
  } else {

  }
  return result;
}

XdsClusterImplLb::XdsClusterImplLb(RefCountedPtr<GrpcXdsClient> xds_client,
                                   Args args)
    : LoadBalancingPolicy(std::move(args)), xds_client_(std::move(xds_client)) {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this << "] created -- using xds client "
      << xds_client_.get();
}

XdsClusterImplLb::~XdsClusterImplLb() {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this
      << "] destroying xds_cluster_impl LB policy";
}

void XdsClusterImplLb::ShutdownLocked() {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this << "] shutting down";
  shutting_down_ = true;
  ResetState();
  xds_client_.reset(DEBUG_LOCATION, "XdsClusterImpl");
}

void XdsClusterImplLb::ResetState() {

  if (child_policy_ != nullptr) {
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     interested_parties());
    child_policy_.reset();
  }

  picker_.reset();
  drop_stats_.reset();
}

void XdsClusterImplLb::ReportTransientFailure(absl::Status status) {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this
      << "] reporting TRANSIENT_FAILURE: " << status;
  ResetState();
  channel_control_helper()->UpdateState(
      GRPC_CHANNEL_TRANSIENT_FAILURE, status,
      MakeRefCounted<TransientFailurePicker>(status));
}

void XdsClusterImplLb::ExitIdleLocked() {
  if (child_policy_ != nullptr) child_policy_->ExitIdleLocked();
}

void XdsClusterImplLb::ResetBackoffLocked() {

  if (child_policy_ != nullptr) child_policy_->ResetBackoffLocked();
}

std::string GetEdsResourceName(const XdsClusterResource& cluster_resource) {
  auto* eds = std::get_if<XdsClusterResource::Eds>(&cluster_resource.type);
  if (eds == nullptr) return "";
  return eds->eds_service_name;
}

absl::Status XdsClusterImplLb::UpdateLocked(UpdateArgs args) {
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this << "] Received update";

  auto new_config = args.config.TakeAsSubclass<XdsClusterImplLbConfig>();

  if (config_ != nullptr) {
    CHECK(config_->cluster_name() == new_config->cluster_name());
  }

  auto new_xds_config = args.args.GetObjectRef<XdsConfig>();
  if (new_xds_config == nullptr) {

    absl::Status status = absl::InternalError(
        "xDS config not passed to xds_cluster_impl LB policy");
    ReportTransientFailure(status);
    return status;
  }
  auto it = new_xds_config->clusters.find(new_config->cluster_name());
  if (it == new_xds_config->clusters.end() || !it->second.ok() ||
      it->second->cluster == nullptr) {

    absl::Status status = absl::InternalError(absl::StrCat(
        "xDS config has no entry for cluster ", new_config->cluster_name()));
    ReportTransientFailure(status);
    return status;
  }
  auto& new_cluster_config = *it->second;
  auto* endpoint_config = std::get_if<XdsConfig::ClusterConfig::EndpointConfig>(
      &new_cluster_config.children);
  if (endpoint_config == nullptr) {

    absl::Status status = absl::InternalError(
        absl::StrCat("cluster config for ", new_config->cluster_name(),
                     " has no endpoint config"));
    ReportTransientFailure(status);
    return status;
  }
  auto xds_cert_provider =
      MaybeCreateCertificateProviderLocked(*new_cluster_config.cluster);
  if (!xds_cert_provider.ok()) {

    ReportTransientFailure(xds_cert_provider.status());
    return xds_cert_provider.status();
  }
  if (*xds_cert_provider != nullptr) {
    args.args = args.args.SetObject(std::move(*xds_cert_provider));
  }

  std::string new_eds_service_name =
      GetEdsResourceName(*new_cluster_config.cluster);
  std::string old_eds_service_name =
      cluster_resource_ == nullptr ? ""
                                   : GetEdsResourceName(*cluster_resource_);

  // Note: We need a drop stats object whenever load reporting is enabled,

  if (new_cluster_config.cluster->lrs_load_reporting_server == nullptr) {
    drop_stats_.reset();
  } else if (cluster_resource_ == nullptr ||
             old_eds_service_name != new_eds_service_name ||
             !LrsServersEqual(
                 cluster_resource_->lrs_load_reporting_server,
                 new_cluster_config.cluster->lrs_load_reporting_server)) {
    drop_stats_ = xds_client_->lrs_client().AddClusterDropStats(
        new_cluster_config.cluster->lrs_load_reporting_server,
        new_config->cluster_name(), new_eds_service_name);
    if (drop_stats_ == nullptr) {
      LOG(ERROR)
          << "[xds_cluster_impl_lb " << this
          << "] Failed to get cluster drop stats for LRS server "
          << new_cluster_config.cluster->lrs_load_reporting_server->server_uri()
          << ", cluster " << new_config->cluster_name() << ", EDS service name "
          << new_eds_service_name
          << ", load reporting for drops will not be done.";
    }
  }

  if (cluster_resource_ == nullptr ||
      old_eds_service_name != new_eds_service_name) {
    call_counter_ = g_call_counter_map->GetOrCreate(new_config->cluster_name(),
                                                    new_eds_service_name);
  }

  config_ = std::move(new_config);
  cluster_resource_ = new_cluster_config.cluster;
  const XdsMetadataValue* metadata_value =
      cluster_resource_->metadata.Find("com.google.csm.telemetry_labels");
  if (metadata_value != nullptr &&
      metadata_value->type() == XdsStructMetadataValue::Type()) {
    const Json::Object& json_object =
        DownCast<const XdsStructMetadataValue*>(metadata_value)
            ->json()
            .object();
    auto it = json_object.find("service_name");
    if (it != json_object.end() && it->second.type() == Json::Type::kString) {
      service_telemetry_label_ = RefCountedStringValue(it->second.string());
    }
    it = json_object.find("service_namespace");
    if (it != json_object.end() && it->second.type() == Json::Type::kString) {
      namespace_telemetry_label_ = RefCountedStringValue(it->second.string());
    }
  }
  drop_config_ = endpoint_config->endpoints != nullptr
                     ? endpoint_config->endpoints->drop_config
                     : nullptr;

  MaybeUpdatePickerLocked();

  return UpdateChildPolicyLocked(std::move(args.addresses),
                                 std::move(args.resolution_note), args.args);
}

absl::StatusOr<RefCountedPtr<XdsCertificateProvider>>
XdsClusterImplLb::MaybeCreateCertificateProviderLocked(
    const XdsClusterResource& cluster_resource) const {

  auto channel_credentials = channel_control_helper()->GetChannelCredentials();
  if (channel_credentials == nullptr ||
      channel_credentials->type() != XdsCredentials::Type()) {
    return nullptr;
  }

  absl::string_view root_cert_name;
  RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider;
  bool use_system_root_certs = false;
  absl::Status status = Match(
      cluster_resource.common_tls_context.certificate_validation_context
          .ca_certs,
      [](const std::monostate&) {

        return absl::OkStatus();
      },
      [&](const CommonTlsContext::CertificateProviderPluginInstance&
              cert_provider) {
        root_cert_name = cert_provider.certificate_name;
        root_cert_provider =
            xds_client_->certificate_provider_store()
                .CreateOrGetCertificateProvider(cert_provider.instance_name);
        if (root_cert_provider == nullptr) {
          return absl::InternalError(
              absl::StrCat("Certificate provider instance name: \"",
                           cert_provider.instance_name, "\" not recognized."));
        }
        return absl::OkStatus();
      },
      [&](const CommonTlsContext::CertificateValidationContext::
              SystemRootCerts&) {
        use_system_root_certs = true;
        return absl::OkStatus();
      });
  if (!status.ok()) return status;

  absl::string_view identity_provider_instance_name =
      cluster_resource.common_tls_context.tls_certificate_provider_instance
          .instance_name;
  absl::string_view identity_cert_name =
      cluster_resource.common_tls_context.tls_certificate_provider_instance
          .certificate_name;
  RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider;
  if (!identity_provider_instance_name.empty()) {
    identity_cert_provider =
        xds_client_->certificate_provider_store()
            .CreateOrGetCertificateProvider(identity_provider_instance_name);
    if (identity_cert_provider == nullptr) {
      return absl::InternalError(
          absl::StrCat("Certificate provider instance name: \"",
                       identity_provider_instance_name, "\" not recognized."));
    }
  }

  const std::vector<StringMatcher>& san_matchers =
      cluster_resource.common_tls_context.certificate_validation_context
          .match_subject_alt_names;

  return MakeRefCounted<XdsCertificateProvider>(
      std::move(root_cert_provider), root_cert_name, use_system_root_certs,
      std::move(identity_cert_provider), identity_cert_name, san_matchers);
}

void XdsClusterImplLb::MaybeUpdatePickerLocked() {

  if (drop_config_ != nullptr && drop_config_->drop_all()) {
    auto drop_picker = MakeRefCounted<Picker>(this, picker_);
    GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
        << "[xds_cluster_impl_lb " << this
        << "] updating connectivity (drop all): state=READY picker="
        << drop_picker.get();
    channel_control_helper()->UpdateState(GRPC_CHANNEL_READY, absl::Status(),
                                          std::move(drop_picker));
    return;
  }

  if (picker_ != nullptr) {
    auto drop_picker = MakeRefCounted<Picker>(this, picker_);
    GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
        << "[xds_cluster_impl_lb " << this
        << "] updating connectivity: state=" << ConnectivityStateName(state_)
        << " status=(" << status_ << ") picker=" << drop_picker.get();
    channel_control_helper()->UpdateState(state_, status_,
                                          std::move(drop_picker));
  }
}

OrphanablePtr<LoadBalancingPolicy> XdsClusterImplLb::CreateChildPolicyLocked(
    const ChannelArgs& args) {
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer = work_serializer();
  lb_policy_args.args = args;
  lb_policy_args.channel_control_helper = std::make_unique<Helper>(
      RefAsSubclass<XdsClusterImplLb>(DEBUG_LOCATION, "Helper"));
  OrphanablePtr<LoadBalancingPolicy> lb_policy =
      MakeOrphanable<ChildPolicyHandler>(std::move(lb_policy_args),
                                         &xds_cluster_impl_lb_trace);
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this
      << "] Created new child policy handler " << lb_policy.get();

  grpc_pollset_set_add_pollset_set(lb_policy->interested_parties(),
                                   interested_parties());
  return lb_policy;
}

absl::Status XdsClusterImplLb::UpdateChildPolicyLocked(
    absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> addresses,
    std::string resolution_note, const ChannelArgs& args) {

  if (child_policy_ == nullptr) {
    child_policy_ = CreateChildPolicyLocked(args);
  }

  UpdateArgs update_args;
  update_args.addresses = std::move(addresses);
  update_args.resolution_note = std::move(resolution_note);
  update_args.config = config_->child_policy();
  update_args.args =
      args.Set(GRPC_ARG_XDS_CLUSTER_NAME, config_->cluster_name());

  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << this << "] Updating child policy handler "
      << child_policy_.get();
  return child_policy_->UpdateLocked(std::move(update_args));
}

RefCountedPtr<SubchannelInterface> XdsClusterImplLb::Helper::CreateSubchannel(
    const grpc_resolved_address& address, const ChannelArgs& per_address_args,
    const ChannelArgs& args) {
  if (parent()->shutting_down_) return nullptr;

  auto locality_name = per_address_args.GetObjectRef<XdsLocalityName>();
  RefCountedPtr<LrsClient::ClusterLocalityStats> locality_stats;
  if (parent()->cluster_resource_->lrs_load_reporting_server != nullptr) {
    locality_stats =
        parent()->xds_client_->lrs_client().AddClusterLocalityStats(
            parent()->cluster_resource_->lrs_load_reporting_server,
            parent()->config_->cluster_name(),
            GetEdsResourceName(*parent()->cluster_resource_), locality_name,
            parent()->cluster_resource_->lrs_backend_metric_propagation);
    if (locality_stats == nullptr) {
      LOG(ERROR)
          << "[xds_cluster_impl_lb " << parent()
          << "] Failed to get locality stats object for LRS server "
          << parent()
                 ->cluster_resource_->lrs_load_reporting_server->server_uri()
          << ", cluster " << parent()->config_->cluster_name()
          << ", EDS service name "
          << GetEdsResourceName(*parent()->cluster_resource_)
          << "; load reports will not be generated";
    }
  }
  StatsSubchannelWrapper::LocalityData locality_data;
  if (locality_stats != nullptr) {
    locality_data = std::move(locality_stats);
  } else {
    locality_data = locality_name->human_readable_string();
  }
  return MakeRefCounted<StatsSubchannelWrapper>(
      parent()->channel_control_helper()->CreateSubchannel(
          address, per_address_args, args),
      std::move(locality_data),
      per_address_args.GetString(GRPC_ARG_ADDRESS_NAME).value_or(""));
}

void XdsClusterImplLb::Helper::UpdateState(
    grpc_connectivity_state state, const absl::Status& status,
    RefCountedPtr<SubchannelPicker> picker) {
  if (parent()->shutting_down_) return;
  GRPC_TRACE_LOG(xds_cluster_impl_lb, INFO)
      << "[xds_cluster_impl_lb " << parent()
      << "] child connectivity state update: state="
      << ConnectivityStateName(state) << " (" << status
      << ") picker=" << picker.get();

  parent()->state_ = state;
  parent()->status_ = status;
  parent()->picker_ = std::move(picker);

  parent()->MaybeUpdatePickerLocked();
}

const JsonLoaderInterface* XdsClusterImplLbConfig::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<XdsClusterImplLbConfig>()
          // Note: Some fields require custom processing, so they are

          .Field("clusterName", &XdsClusterImplLbConfig::cluster_name_)
          .Finish();
  return loader;
}

void XdsClusterImplLbConfig::JsonPostLoad(const Json& json, const JsonArgs&,
                                          ValidationErrors* errors) {

  ValidationErrors::ScopedField field(errors, ".childPolicy");
  auto it = json.object().find("childPolicy");
  if (it == json.object().end()) {
    errors->AddError("field not present");
  } else if (auto lb_config = CoreConfiguration::Get()
                                  .lb_policy_registry()
                                  .ParseLoadBalancingConfig(it->second);
             !lb_config.ok()) {
    errors->AddError(lb_config.status().message());
  } else {
    child_policy_ = std::move(*lb_config);
  }
}

class XdsClusterImplLbFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    auto xds_client = args.args.GetObjectRef<GrpcXdsClient>(DEBUG_LOCATION,
                                                            "XdsClusterImplLb");
    if (xds_client == nullptr) {
      LOG(ERROR) << "XdsClient not present in channel args -- cannot "
                    "instantiate xds_cluster_impl LB policy";
      return nullptr;
    }
    return MakeOrphanable<XdsClusterImplLb>(std::move(xds_client),
                                            std::move(args));
  }

  absl::string_view name() const override { return kXdsClusterImpl; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<XdsClusterImplLbConfig>>(
        json, JsonArgs(),
        "errors validating xds_cluster_impl LB policy config");
  }
};

}

void RegisterXdsClusterImplLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<XdsClusterImplLbFactory>());
}

}
