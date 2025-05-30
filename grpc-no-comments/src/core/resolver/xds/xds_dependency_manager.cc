
// Copyright 2019 gRPC authors.

#include "src/core/resolver/xds/xds_dependency_manager.h"

#include <set>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "src/core/config/core_configuration.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/resolver/fake/fake_resolver.h"
#include "src/core/util/match.h"
#include "src/core/xds/grpc/xds_cluster_parser.h"
#include "src/core/xds/grpc/xds_endpoint_parser.h"
#include "src/core/xds/grpc/xds_listener_parser.h"
#include "src/core/xds/grpc/xds_route_config_parser.h"
#include "src/core/xds/grpc/xds_routing.h"

namespace grpc_core {

namespace {

constexpr int kMaxXdsAggregateClusterRecursionDepth = 16;

}

class XdsDependencyManager::ListenerWatcher final
    : public XdsListenerResourceType::WatcherInterface {
 public:
  explicit ListenerWatcher(RefCountedPtr<XdsDependencyManager> dependency_mgr)
      : dependency_mgr_(std::move(dependency_mgr)) {}

  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsListenerResource>> listener,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [dependency_mgr = dependency_mgr_, listener = std::move(listener),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          dependency_mgr->OnListenerUpdate(std::move(listener));
        },
        DEBUG_LOCATION);
  }

  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [dependency_mgr = dependency_mgr_, status = std::move(status),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          dependency_mgr->OnListenerAmbientError(std::move(status));
        });
  }

 private:
  RefCountedPtr<XdsDependencyManager> dependency_mgr_;
};

class XdsDependencyManager::RouteConfigWatcher final
    : public XdsRouteConfigResourceType::WatcherInterface {
 public:
  RouteConfigWatcher(RefCountedPtr<XdsDependencyManager> dependency_mgr,
                     std::string name)
      : dependency_mgr_(std::move(dependency_mgr)), name_(std::move(name)) {}

  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
          route_config,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<RouteConfigWatcher>(),
         route_config = std::move(route_config),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnRouteConfigUpdate(self->name_,
                                                     std::move(route_config));
        });
  }

  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<RouteConfigWatcher>(), status = std::move(status),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnRouteConfigAmbientError(self->name_,
                                                           std::move(status));
        });
  }

 private:
  RefCountedPtr<XdsDependencyManager> dependency_mgr_;
  std::string name_;
};

class XdsDependencyManager::ClusterWatcher final
    : public XdsClusterResourceType::WatcherInterface {
 public:
  ClusterWatcher(RefCountedPtr<XdsDependencyManager> dependency_mgr,
                 absl::string_view name)
      : dependency_mgr_(std::move(dependency_mgr)), name_(name) {}

  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsClusterResource>> cluster,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<ClusterWatcher>(), cluster = std::move(cluster),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnClusterUpdate(self->name_,
                                                 std::move(cluster));
        });
  }

  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<ClusterWatcher>(), status = std::move(status),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnClusterAmbientError(self->name_,
                                                       std::move(status));
        });
  }

 private:
  RefCountedPtr<XdsDependencyManager> dependency_mgr_;
  std::string name_;
};

class XdsDependencyManager::EndpointWatcher final
    : public XdsEndpointResourceType::WatcherInterface {
 public:
  EndpointWatcher(RefCountedPtr<XdsDependencyManager> dependency_mgr,
                  absl::string_view name)
      : dependency_mgr_(std::move(dependency_mgr)), name_(name) {}

  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsEndpointResource>> endpoint,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<EndpointWatcher>(),
         endpoint = std::move(endpoint),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnEndpointUpdate(self->name_,
                                                  std::move(endpoint));
        },
        DEBUG_LOCATION);
  }

  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<XdsClient::ReadDelayHandle> read_delay_handle) override {
    dependency_mgr_->work_serializer_->Run(
        [self = RefAsSubclass<EndpointWatcher>(), status = std::move(status),
         read_delay_handle = std::move(read_delay_handle)]() mutable {
          self->dependency_mgr_->OnEndpointAmbientError(self->name_,
                                                        std::move(status));
        });
  }

 private:
  RefCountedPtr<XdsDependencyManager> dependency_mgr_;
  std::string name_;
};

class XdsDependencyManager::DnsResultHandler final
    : public Resolver::ResultHandler {
 public:
  DnsResultHandler(RefCountedPtr<XdsDependencyManager> dependency_mgr,
                   std::string name)
      : dependency_mgr_(std::move(dependency_mgr)), name_(std::move(name)) {}

  void ReportResult(Resolver::Result result) override {
    dependency_mgr_->work_serializer_->Run(
        [dependency_mgr = dependency_mgr_, name = name_,
         result = std::move(result)]() mutable {
          dependency_mgr->OnDnsResult(name, std::move(result));
        });
  }

 private:
  RefCountedPtr<XdsDependencyManager> dependency_mgr_;
  std::string name_;
};

void XdsDependencyManager::ClusterSubscription::Orphaned() {
  dependency_mgr_->work_serializer_->Run([self = WeakRef()]() {
    self->dependency_mgr_->OnClusterSubscriptionUnref(self->cluster_name_,
                                                      self.get());
  });
}

XdsDependencyManager::XdsDependencyManager(
    RefCountedPtr<GrpcXdsClient> xds_client,
    std::shared_ptr<WorkSerializer> work_serializer,
    std::unique_ptr<Watcher> watcher, std::string data_plane_authority,
    std::string listener_resource_name, ChannelArgs args,
    grpc_pollset_set* interested_parties)
    : xds_client_(std::move(xds_client)),
      work_serializer_(std::move(work_serializer)),
      watcher_(std::move(watcher)),
      data_plane_authority_(std::move(data_plane_authority)),
      listener_resource_name_(std::move(listener_resource_name)),
      args_(std::move(args)),
      interested_parties_(interested_parties) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this << "] starting watch for listener "
      << listener_resource_name_;
  auto listener_watcher = MakeRefCounted<ListenerWatcher>(Ref());
  listener_watcher_ = listener_watcher.get();
  XdsListenerResourceType::StartWatch(
      xds_client_.get(), listener_resource_name_, std::move(listener_watcher));
}

void XdsDependencyManager::Orphan() {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this << "] shutting down";
  if (listener_watcher_ != nullptr) {
    XdsListenerResourceType::CancelWatch(
        xds_client_.get(), listener_resource_name_, listener_watcher_,
        false);
  }
  if (route_config_watcher_ != nullptr) {
    XdsRouteConfigResourceType::CancelWatch(
        xds_client_.get(), route_config_name_, route_config_watcher_,
        false);
  }
  for (const auto& [name, cluster_state] : cluster_watchers_) {
    XdsClusterResourceType::CancelWatch(xds_client_.get(), name,
                                        cluster_state.watcher,
                                        false);
  }
  for (const auto& [name, endpoint_state] : endpoint_watchers_) {
    XdsEndpointResourceType::CancelWatch(xds_client_.get(), name,
                                         endpoint_state.watcher,
                                         false);
  }
  cluster_subscriptions_.clear();
  xds_client_.reset();
  for (auto& [_, dns_state] : dns_resolvers_) {
    dns_state.resolver.reset();
  }
  Unref();
}

void XdsDependencyManager::RequestReresolution() {
  for (const auto& [_, dns_state] : dns_resolvers_) {
    dns_state.resolver->RequestReresolutionLocked();
  }
}

void XdsDependencyManager::ResetBackoff() {
  for (const auto& [_, dns_state] : dns_resolvers_) {
    dns_state.resolver->ResetBackoffLocked();
  }
}

void XdsDependencyManager::OnListenerUpdate(
    absl::StatusOr<std::shared_ptr<const XdsListenerResource>> listener) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this << "] received Listener update";
  if (xds_client_ == nullptr) return;
  if (!listener.ok()) {
    current_listener_.reset();
    return ReportError("LDS", listener_resource_name_,
                       listener.status().message());
  }
  const auto* hcm = std::get_if<XdsListenerResource::HttpConnectionManager>(
      &(*listener)->listener);
  if (hcm == nullptr) {
    current_listener_.reset();
    return ReportError("LDS", listener_resource_name_, "not an API listener");
  }
  current_listener_ = *std::move(listener);
  lds_resolution_note_.clear();
  Match(
      hcm->route_config,

      [&](const std::string& rds_name) {

        if (route_config_name_ != rds_name) {

          if (route_config_watcher_ != nullptr) {
            XdsRouteConfigResourceType::CancelWatch(
                xds_client_.get(), route_config_name_, route_config_watcher_,
                true);
            route_config_watcher_ = nullptr;
          }

          route_config_name_ = rds_name;
          GRPC_TRACE_LOG(xds_resolver, INFO)
              << "[XdsDependencyManager " << this
              << "] starting watch for route config " << route_config_name_;
          auto watcher =
              MakeRefCounted<RouteConfigWatcher>(Ref(), route_config_name_);
          route_config_watcher_ = watcher.get();
          XdsRouteConfigResourceType::StartWatch(
              xds_client_.get(), route_config_name_, std::move(watcher));
        } else {

          MaybeReportUpdate();
        }
      },

      [&](const std::shared_ptr<const XdsRouteConfigResource>& route_config) {

        if (route_config_watcher_ != nullptr) {
          XdsRouteConfigResourceType::CancelWatch(
              xds_client_.get(), route_config_name_, route_config_watcher_);
          route_config_watcher_ = nullptr;
          route_config_name_.clear();
        }
        OnRouteConfigUpdate("", route_config);
      });
}

void XdsDependencyManager::OnListenerAmbientError(absl::Status status) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this
      << "] received Listener error: " << listener_resource_name_ << ": "
      << status;
  if (xds_client_ == nullptr) return;
  if (status.ok()) {
    lds_resolution_note_.clear();
  } else {
    lds_resolution_note_ = absl::StrCat(
        "LDS resource ", listener_resource_name_, ": ", status.message());
  }
  MaybeReportUpdate();
}

namespace {

class XdsVirtualHostListIterator final
    : public XdsRouting::VirtualHostListIterator {
 public:
  explicit XdsVirtualHostListIterator(
      const std::vector<XdsRouteConfigResource::VirtualHost>* virtual_hosts)
      : virtual_hosts_(virtual_hosts) {}

  size_t Size() const override { return virtual_hosts_->size(); }

  const std::vector<std::string>& GetDomainsForVirtualHost(
      size_t index) const override {
    return (*virtual_hosts_)[index].domains;
  }

 private:
  const std::vector<XdsRouteConfigResource::VirtualHost>* virtual_hosts_;
};

absl::flat_hash_set<absl::string_view> GetClustersFromVirtualHost(
    const XdsRouteConfigResource::VirtualHost& virtual_host) {
  absl::flat_hash_set<absl::string_view> clusters;
  for (auto& route : virtual_host.routes) {
    auto* route_action =
        std::get_if<XdsRouteConfigResource::Route::RouteAction>(&route.action);
    if (route_action == nullptr) continue;
    Match(
        route_action->action,

        [&](const XdsRouteConfigResource::Route::RouteAction::ClusterName&
                cluster_name) { clusters.insert(cluster_name.cluster_name); },

        [&](const std::vector<
            XdsRouteConfigResource::Route::RouteAction::ClusterWeight>&
                weighted_clusters) {
          for (const auto& weighted_cluster : weighted_clusters) {
            clusters.insert(weighted_cluster.name);
          }
        },

        [&](const XdsRouteConfigResource::Route::RouteAction::
                ClusterSpecifierPluginName&) {

        });
  }
  return clusters;
}

}

void XdsDependencyManager::OnRouteConfigUpdate(
    const std::string& name,
    absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
        route_config) {
  GRPC_TRACE_LOG(xds_resolver, INFO) << "[XdsDependencyManager " << this
                                     << "] received RouteConfig update for "
                                     << (name.empty() ? "<inline>" : name);
  if (xds_client_ == nullptr) return;
  if (!route_config.ok()) {
    current_virtual_host_ = nullptr;
    ReportError(route_config_name_.empty() ? "LDS" : "RDS",
                route_config_name_.empty() ? listener_resource_name_
                                           : route_config_name_,
                route_config.status().message());
    return;
  }

  if (name.empty()) {
    if (!route_config_name_.empty()) return;
  } else {
    if (name != route_config_name_) return;
  }

  auto vhost_index = XdsRouting::FindVirtualHostForDomain(
      XdsVirtualHostListIterator(&(*route_config)->virtual_hosts),
      data_plane_authority_);
  if (!vhost_index.has_value()) {
    current_virtual_host_ = nullptr;
    ReportError(route_config_name_.empty() ? "LDS" : "RDS",
                route_config_name_.empty() ? listener_resource_name_
                                           : route_config_name_,
                absl::StrCat("could not find VirtualHost for ",
                             data_plane_authority_, " in RouteConfiguration"));
    return;
  }

  current_route_config_ = std::move(*route_config);
  current_virtual_host_ = &current_route_config_->virtual_hosts[*vhost_index];
  clusters_from_route_config_ =
      GetClustersFromVirtualHost(*current_virtual_host_);
  rds_resolution_note_.clear();
  MaybeReportUpdate();
}

void XdsDependencyManager::OnRouteConfigAmbientError(std::string resource_name,
                                                     absl::Status status) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this
      << "] received RouteConfig error: " << resource_name << ": " << status;
  if (xds_client_ == nullptr) return;
  if (status.ok()) {
    rds_resolution_note_.clear();
  } else {
    rds_resolution_note_ =
        absl::StrCat("RDS resource ", resource_name, ": ", status.message());
  }
  MaybeReportUpdate();
}

void XdsDependencyManager::OnClusterUpdate(
    const std::string& name,
    absl::StatusOr<std::shared_ptr<const XdsClusterResource>> cluster) {
  GRPC_TRACE_LOG(xds_resolver, INFO) << "[XdsDependencyManager " << this
                                     << "] received Cluster update: " << name;
  if (xds_client_ == nullptr) return;
  if (!cluster.ok()) {
    cluster = absl::UnavailableError(
        absl::StrCat("CDS resource ", name, ": ", cluster.status().message()));
  }
  auto it = cluster_watchers_.find(name);
  if (it == cluster_watchers_.end()) return;
  it->second.update = std::move(cluster);
  it->second.resolution_note.clear();
  MaybeReportUpdate();
}

void XdsDependencyManager::OnClusterAmbientError(const std::string& name,
                                                 absl::Status status) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this
      << "] received Cluster error: " << name << " " << status;
  if (xds_client_ == nullptr) return;
  auto it = cluster_watchers_.find(name);
  if (it == cluster_watchers_.end()) return;
  auto& cluster_watcher = it->second;
  if (status.ok()) {
    cluster_watcher.resolution_note.clear();
  } else {
    cluster_watcher.resolution_note =
        absl::StrCat("CDS resource ", name, ": ", status.message());
  }
  MaybeReportUpdate();
}

void XdsDependencyManager::OnEndpointUpdate(
    const std::string& name,
    absl::StatusOr<std::shared_ptr<const XdsEndpointResource>> endpoint) {
  GRPC_TRACE_LOG(xds_resolver, INFO) << "[XdsDependencyManager " << this
                                     << "] received Endpoint update: " << name;
  if (xds_client_ == nullptr) return;
  auto it = endpoint_watchers_.find(name);
  if (it == endpoint_watchers_.end()) return;
  auto& endpoint_watcher = it->second;
  if (!endpoint.ok()) {
    endpoint_watcher.update.endpoints.reset();
    endpoint_watcher.update.resolution_note =
        absl::StrCat("EDS resource ", name, ": ", endpoint.status().message());
  } else {
    if ((*endpoint)->priorities.empty()) {
      endpoint_watcher.update.resolution_note =
          absl::StrCat("EDS resource ", name, ": contains no localities");
    } else {
      std::set<absl::string_view> empty_localities;
      for (const auto& priority : (*endpoint)->priorities) {
        for (const auto& [name, locality] : priority.localities) {
          if (locality.endpoints.empty()) {
            empty_localities.insert(
                name->human_readable_string().as_string_view());
          }
        }
      }
      if (!empty_localities.empty()) {
        endpoint_watcher.update.resolution_note = absl::StrCat(
            "EDS resource ", name, ": contains empty localities: [",
            absl::StrJoin(empty_localities, "; "), "]");
      } else {
        endpoint_watcher.update.resolution_note.clear();
      }
    }
    endpoint_watcher.update.endpoints = std::move(*endpoint);
  }
  MaybeReportUpdate();
}

void XdsDependencyManager::OnEndpointAmbientError(const std::string& name,
                                                  absl::Status status) {
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this
      << "] received Endpoint error: " << name << " " << status;
  if (xds_client_ == nullptr) return;
  auto it = endpoint_watchers_.find(name);
  if (it == endpoint_watchers_.end()) return;
  auto& endpoint_watcher = it->second;
  if (status.ok()) {
    endpoint_watcher.update.resolution_note.clear();
  } else {
    endpoint_watcher.update.resolution_note =
        absl::StrCat("EDS resource ", name, ": ", status.message());
  }
  MaybeReportUpdate();
}

void XdsDependencyManager::OnDnsResult(const std::string& dns_name,
                                       Resolver::Result result) {
  GRPC_TRACE_LOG(xds_resolver, INFO) << "[XdsDependencyManager " << this
                                     << "] received DNS update: " << dns_name;
  if (xds_client_ == nullptr) return;
  auto it = dns_resolvers_.find(dns_name);
  if (it == dns_resolvers_.end()) return;
  PopulateDnsUpdate(dns_name, std::move(result), &it->second);
  MaybeReportUpdate();
}

void XdsDependencyManager::PopulateDnsUpdate(const std::string& dns_name,
                                             Resolver::Result result,
                                             DnsState* dns_state) {

  XdsEndpointResource::Priority::Locality locality;
  locality.name = MakeRefCounted<XdsLocalityName>("", "", "");
  locality.lb_weight = 1;
  if (result.addresses.ok()) {
    std::vector<grpc_resolved_address> addresses;
    ChannelArgs address_args = result.addresses->front().args();
    for (const auto& address : *result.addresses) {
      CHECK_EQ(address.addresses().size(), 1UL);
      addresses.emplace_back(address.addresses().front());
      CHECK_EQ(address_args, address.args());
    }
    locality.endpoints.emplace_back(
        std::move(addresses),
        address_args.Set(GRPC_ARG_ADDRESS_NAME, dns_name));
    dns_state->update.resolution_note = std::move(result.resolution_note);
  } else if (result.resolution_note.empty()) {
    dns_state->update.resolution_note =
        absl::StrCat("DNS resolution failed for ", dns_name, ": ",
                     result.addresses.status().ToString());
  }
  XdsEndpointResource::Priority priority;
  priority.localities.emplace(locality.name.get(), std::move(locality));
  auto resource = std::make_shared<XdsEndpointResource>();
  resource->priorities.emplace_back(std::move(priority));
  dns_state->update.endpoints = std::move(resource);
}

std::string XdsDependencyManager::GenerateResolutionNoteForCluster(
    absl::string_view cluster_resolution_note,
    absl::string_view endpoint_resolution_note) const {
  std::array<absl::string_view, 4> notes = {
      lds_resolution_note_, rds_resolution_note_, cluster_resolution_note,
      endpoint_resolution_note};
  std::vector<absl::string_view> resolution_notes;
  for (const auto& note : notes) {
    if (!note.empty()) resolution_notes.push_back(note);
  }
  std::string node_id_buffer;
  if (resolution_notes.empty()) {
    const XdsBootstrap::Node* node =
        DownCast<const GrpcXdsBootstrap&>(xds_client_->bootstrap()).node();
    if (node != nullptr) {
      node_id_buffer = absl::StrCat("xDS node ID:", node->id());
      resolution_notes.push_back(node_id_buffer);
    }
  }
  return absl::StrJoin(resolution_notes, "; ");
}

bool XdsDependencyManager::PopulateClusterConfigMap(
    absl::string_view name, int depth,
    absl::flat_hash_map<std::string, absl::StatusOr<XdsConfig::ClusterConfig>>*
        cluster_config_map,
    std::set<absl::string_view>* eds_resources_seen,
    std::set<absl::string_view>* dns_names_seen,
    absl::StatusOr<std::vector<absl::string_view>>* leaf_clusters) {
  if (depth > 0) CHECK_NE(leaf_clusters, nullptr);
  if (depth == kMaxXdsAggregateClusterRecursionDepth) {
    *leaf_clusters =
        absl::UnavailableError("aggregate cluster graph exceeds max depth");
    return true;
  }

  auto [it, inserted] = cluster_config_map->emplace(
      name, absl::InternalError("cluster data not yet available"));
  if (!inserted) return true;
  auto& cluster_config = it->second;
  auto& state = cluster_watchers_[name];

  if (state.watcher == nullptr) {
    auto watcher = MakeRefCounted<ClusterWatcher>(Ref(), name);
    GRPC_TRACE_LOG(xds_resolver, INFO)
        << "[XdsDependencyManager " << this << "] starting watch for cluster "
        << name;
    state.watcher = watcher.get();
    XdsClusterResourceType::StartWatch(xds_client_.get(), name,
                                       std::move(watcher));
    return false;
  }

  if (!state.update.ok()) {
    cluster_config = state.update.status();
    return true;
  }

  if (*state.update == nullptr) return false;

  return Match(
      (*state.update)->type,

      [&](const XdsClusterResource::Eds& eds) {
        absl::string_view eds_resource_name =
            eds.eds_service_name.empty() ? name : eds.eds_service_name;
        eds_resources_seen->insert(eds_resource_name);

        auto& eds_state = endpoint_watchers_[eds_resource_name];
        if (eds_state.watcher == nullptr) {
          GRPC_TRACE_LOG(xds_resolver, INFO)
              << "[XdsDependencyManager " << this
              << "] starting watch for endpoint " << eds_resource_name;
          auto watcher =
              MakeRefCounted<EndpointWatcher>(Ref(), eds_resource_name);
          eds_state.watcher = watcher.get();
          XdsEndpointResourceType::StartWatch(
              xds_client_.get(), eds_resource_name, std::move(watcher));
          return false;
        }

        if (eds_state.update.endpoints == nullptr &&
            eds_state.update.resolution_note.empty()) {
          return false;
        }

        cluster_config.emplace(
            *state.update, eds_state.update.endpoints,
            GenerateResolutionNoteForCluster(state.resolution_note,
                                             eds_state.update.resolution_note));
        if (leaf_clusters != nullptr) (*leaf_clusters)->push_back(name);
        return true;
      },

      [&](const XdsClusterResource::LogicalDns& logical_dns) {
        dns_names_seen->insert(logical_dns.hostname);

        auto& dns_state = dns_resolvers_[logical_dns.hostname];
        if (dns_state.resolver == nullptr) {
          GRPC_TRACE_LOG(xds_resolver, INFO)
              << "[XdsDependencyManager " << this
              << "] starting DNS resolver for " << logical_dns.hostname;
          auto* fake_resolver_response_generator = args_.GetPointer<
              FakeResolverResponseGenerator>(
              GRPC_ARG_XDS_LOGICAL_DNS_CLUSTER_FAKE_RESOLVER_RESPONSE_GENERATOR);
          ChannelArgs args = args_;
          std::string target;
          if (fake_resolver_response_generator != nullptr) {
            target = absl::StrCat("fake:", logical_dns.hostname);
            args = args.SetObject(fake_resolver_response_generator->Ref());
          } else {
            target = absl::StrCat("dns:", logical_dns.hostname);
          }
          dns_state.resolver =
              CoreConfiguration::Get().resolver_registry().CreateResolver(
                  target, args, interested_parties_, work_serializer_,
                  std::make_unique<DnsResultHandler>(Ref(),
                                                     logical_dns.hostname));
          if (dns_state.resolver == nullptr) {
            Resolver::Result result;
            result.addresses.emplace();
            result.resolution_note = absl::StrCat(
                "failed to create DNS resolver for ", logical_dns.hostname);
            PopulateDnsUpdate(logical_dns.hostname, std::move(result),
                              &dns_state);
          } else {
            dns_state.resolver->StartLocked();
            return false;
          }
        }

        if (dns_state.update.endpoints == nullptr &&
            dns_state.update.resolution_note.empty()) {
          return false;
        }

        cluster_config.emplace(
            *state.update, dns_state.update.endpoints,
            GenerateResolutionNoteForCluster(state.resolution_note,
                                             dns_state.update.resolution_note));
        if (leaf_clusters != nullptr) (*leaf_clusters)->push_back(name);
        return true;
      },

      [&](const XdsClusterResource::Aggregate& aggregate) {

        auto cluster_resource = *state.update;

        absl::StatusOr<std::vector<absl::string_view>> child_leaf_clusters;
        child_leaf_clusters.emplace();
        bool have_all_resources = true;
        for (const std::string& child_name :
             aggregate.prioritized_cluster_names) {
          have_all_resources &= PopulateClusterConfigMap(
              child_name, depth + 1, cluster_config_map, eds_resources_seen,
              dns_names_seen, &child_leaf_clusters);
          if (!child_leaf_clusters.ok()) break;
        }

        auto& aggregate_cluster_config = (*cluster_config_map)[name];

        if (!child_leaf_clusters.ok()) {
          aggregate_cluster_config = child_leaf_clusters.status();
          if (leaf_clusters != nullptr) {
            *leaf_clusters = child_leaf_clusters.status();
          }
          return true;
        }

        if (leaf_clusters != nullptr) {
          (*leaf_clusters)
              ->insert((*leaf_clusters)->end(), child_leaf_clusters->begin(),
                       child_leaf_clusters->end());
        }

        if (have_all_resources && child_leaf_clusters->empty()) {
          aggregate_cluster_config = absl::UnavailableError(
              absl::StrCat("aggregate cluster dependency graph for ", name,
                           " has no leaf clusters"));
          return true;
        }

        aggregate_cluster_config.emplace(std::move(cluster_resource),
                                         std::move(*child_leaf_clusters));
        return have_all_resources;
      });
}

RefCountedPtr<XdsDependencyManager::ClusterSubscription>
XdsDependencyManager::GetClusterSubscription(absl::string_view cluster_name) {
  auto it = cluster_subscriptions_.find(cluster_name);
  if (it != cluster_subscriptions_.end()) {
    auto subscription = it->second->RefIfNonZero();
    if (subscription != nullptr) return subscription;
  }
  auto subscription = MakeRefCounted<ClusterSubscription>(cluster_name, Ref());
  cluster_subscriptions_.emplace(subscription->cluster_name(),
                                 subscription->WeakRef());

  if (!clusters_from_route_config_.contains(cluster_name)) {
    MaybeReportUpdate();
  }
  return subscription;
}

void XdsDependencyManager::OnClusterSubscriptionUnref(
    absl::string_view cluster_name, ClusterSubscription* subscription) {
  auto it = cluster_subscriptions_.find(cluster_name);

  if (it == cluster_subscriptions_.end()) return;

  if (it->second != subscription) return;

  cluster_subscriptions_.erase(it);

  if (!clusters_from_route_config_.contains(cluster_name)) {
    MaybeReportUpdate();
  }
}

void XdsDependencyManager::MaybeReportUpdate() {

  if (current_listener_ == nullptr || current_virtual_host_ == nullptr) return;
  auto config = MakeRefCounted<XdsConfig>();
  config->listener = current_listener_;
  config->route_config = current_route_config_;
  config->virtual_host = current_virtual_host_;

  std::set<absl::string_view> clusters_to_watch;
  for (const absl::string_view& cluster : clusters_from_route_config_) {
    clusters_to_watch.insert(cluster);
  }
  for (const auto& [name, _] : cluster_subscriptions_) {
    clusters_to_watch.insert(name);
  }

  std::set<absl::string_view> eds_resources_seen;
  std::set<absl::string_view> dns_names_seen;
  bool have_all_resources = true;
  for (const absl::string_view& cluster : clusters_to_watch) {
    have_all_resources &= PopulateClusterConfigMap(
        cluster, 0, &config->clusters, &eds_resources_seen, &dns_names_seen);
  }

  for (auto it = cluster_watchers_.begin(); it != cluster_watchers_.end();) {
    auto& [cluster_name, cluster_watcher] = *it;
    if (config->clusters.contains(cluster_name)) {
      ++it;
      continue;
    }
    GRPC_TRACE_LOG(xds_resolver, INFO)
        << "[XdsDependencyManager " << this << "] cancelling watch for cluster "
        << cluster_name;
    XdsClusterResourceType::CancelWatch(xds_client_.get(), cluster_name,
                                        cluster_watcher.watcher,
                                        false);
    cluster_watchers_.erase(it++);
  }

  for (auto it = endpoint_watchers_.begin(); it != endpoint_watchers_.end();) {
    auto& [eds_resource_name, endpoint_watcher] = *it;
    if (eds_resources_seen.find(eds_resource_name) !=
        eds_resources_seen.end()) {
      ++it;
      continue;
    }
    GRPC_TRACE_LOG(xds_resolver, INFO)
        << "[XdsDependencyManager " << this
        << "] cancelling watch for EDS resource " << eds_resource_name;
    XdsEndpointResourceType::CancelWatch(xds_client_.get(), eds_resource_name,
                                         endpoint_watcher.watcher,
                                         false);
    endpoint_watchers_.erase(it++);
  }

  for (auto it = dns_resolvers_.begin(); it != dns_resolvers_.end();) {
    const std::string& dns_name = it->first;
    if (dns_names_seen.find(dns_name) != dns_names_seen.end()) {
      ++it;
      continue;
    }
    GRPC_TRACE_LOG(xds_resolver, INFO)
        << "[XdsDependencyManager " << this
        << "] shutting down DNS resolver for " << dns_name;
    dns_resolvers_.erase(it++);
  }

  if (!have_all_resources) {
    GRPC_TRACE_LOG(xds_resolver, INFO)
        << "[XdsDependencyManager " << this
        << "] missing data -- NOT returning config";
    return;
  }
  GRPC_TRACE_LOG(xds_resolver, INFO)
      << "[XdsDependencyManager " << this
      << "] returning config: " << config->ToString();
  watcher_->OnUpdate(std::move(config));
}

void XdsDependencyManager::ReportError(absl::string_view resource_type,
                                       absl::string_view resource_name,
                                       absl::string_view error) {
  watcher_->OnUpdate(absl::UnavailableError(
      absl::StrCat(resource_type, " resource ", resource_name, ": ", error)));
}

}
