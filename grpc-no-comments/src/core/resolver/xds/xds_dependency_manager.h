
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_XDS_XDS_DEPENDENCY_MANAGER_H
#define GRPC_SRC_CORE_RESOLVER_XDS_XDS_DEPENDENCY_MANAGER_H

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/strings/string_view.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/xds/xds_config.h"
#include "src/core/util/ref_counted.h"
#include "src/core/xds/grpc/xds_client_grpc.h"
#include "src/core/xds/grpc/xds_cluster.h"
#include "src/core/xds/grpc/xds_endpoint.h"
#include "src/core/xds/grpc/xds_listener.h"
#include "src/core/xds/grpc/xds_route_config.h"

namespace grpc_core {

class XdsDependencyManager final : public RefCounted<XdsDependencyManager>,
                                   public Orphanable {
 public:
  class Watcher {
   public:
    virtual ~Watcher() = default;

    virtual void OnUpdate(
        absl::StatusOr<RefCountedPtr<const XdsConfig>> config) = 0;
  };

  class ClusterSubscription final : public DualRefCounted<ClusterSubscription> {
   public:
    ClusterSubscription(absl::string_view cluster_name,
                        RefCountedPtr<XdsDependencyManager> dependency_mgr)
        : cluster_name_(cluster_name),
          dependency_mgr_(std::move(dependency_mgr)) {}

    absl::string_view cluster_name() const { return cluster_name_; }

   private:
    void Orphaned() override;

    std::string cluster_name_;
    RefCountedPtr<XdsDependencyManager> dependency_mgr_;
  };

  XdsDependencyManager(RefCountedPtr<GrpcXdsClient> xds_client,
                       std::shared_ptr<WorkSerializer> work_serializer,
                       std::unique_ptr<Watcher> watcher,
                       std::string data_plane_authority,
                       std::string listener_resource_name, ChannelArgs args,
                       grpc_pollset_set* interested_parties);

  void Orphan() override;

  RefCountedPtr<ClusterSubscription> GetClusterSubscription(
      absl::string_view cluster_name);

  void RequestReresolution();

  void ResetBackoff();

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_dependency_manager";
  }
  static int ChannelArgsCompare(const XdsDependencyManager* a,
                                const XdsDependencyManager* b) {
    return QsortCompare(a, b);
  }

 private:
  class ListenerWatcher;
  class RouteConfigWatcher;
  class ClusterWatcher;
  class EndpointWatcher;

  class DnsResultHandler;

  struct ClusterWatcherState {

    ClusterWatcher* watcher = nullptr;

    absl::StatusOr<std::shared_ptr<const XdsClusterResource>> update = nullptr;

    std::string resolution_note;
  };

  struct EndpointConfig {

    std::shared_ptr<const XdsEndpointResource> endpoints;
    std::string resolution_note;
  };

  struct EndpointWatcherState {

    EndpointWatcher* watcher = nullptr;

    EndpointConfig update;
  };

  struct DnsState {
    OrphanablePtr<Resolver> resolver;

    EndpointConfig update;
  };

  void OnListenerUpdate(
      absl::StatusOr<std::shared_ptr<const XdsListenerResource>> listener);
  void OnListenerAmbientError(absl::Status status);

  void OnRouteConfigUpdate(
      const std::string& name,
      absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
          route_config);
  void OnRouteConfigAmbientError(std::string name, absl::Status status);

  void OnClusterUpdate(
      const std::string& name,
      absl::StatusOr<std::shared_ptr<const XdsClusterResource>> cluster);
  void OnClusterAmbientError(const std::string& name, absl::Status status);

  void OnEndpointUpdate(
      const std::string& name,
      absl::StatusOr<std::shared_ptr<const XdsEndpointResource>> endpoint);
  void OnEndpointAmbientError(const std::string& name, absl::Status status);

  void OnDnsResult(const std::string& dns_name, Resolver::Result result);
  void PopulateDnsUpdate(const std::string& dns_name, Resolver::Result result,
                         DnsState* dns_state);

  std::string GenerateResolutionNoteForCluster(
      absl::string_view cluster_resolution_note,
      absl::string_view endpoint_resolution_note) const;

  bool PopulateClusterConfigMap(
      absl::string_view name, int depth,
      absl::flat_hash_map<std::string,
                          absl::StatusOr<XdsConfig::ClusterConfig>>*
          cluster_config_map,
      std::set<absl::string_view>* eds_resources_seen,
      std::set<absl::string_view>* dns_names_seen,
      absl::StatusOr<std::vector<absl::string_view>>* leaf_clusters = nullptr);

  void OnClusterSubscriptionUnref(absl::string_view cluster_name,
                                  ClusterSubscription* subscription);

  void MaybeReportUpdate();

  void ReportError(absl::string_view resource_type,
                   absl::string_view resource_name, absl::string_view error);

  RefCountedPtr<GrpcXdsClient> xds_client_;
  std::shared_ptr<WorkSerializer> work_serializer_;
  std::unique_ptr<Watcher> watcher_;
  const std::string data_plane_authority_;
  const std::string listener_resource_name_;
  ChannelArgs args_;
  grpc_pollset_set* interested_parties_;

  ListenerWatcher* listener_watcher_ = nullptr;
  std::shared_ptr<const XdsListenerResource> current_listener_;
  std::string route_config_name_;
  std::string lds_resolution_note_;

  RouteConfigWatcher* route_config_watcher_ = nullptr;
  std::shared_ptr<const XdsRouteConfigResource> current_route_config_;
  const XdsRouteConfigResource::VirtualHost* current_virtual_host_ = nullptr;
  absl::flat_hash_set<absl::string_view> clusters_from_route_config_;
  std::string rds_resolution_note_;

  absl::flat_hash_map<std::string, ClusterWatcherState> cluster_watchers_;
  absl::flat_hash_map<absl::string_view, WeakRefCountedPtr<ClusterSubscription>>
      cluster_subscriptions_;

  absl::flat_hash_map<std::string, EndpointWatcherState> endpoint_watchers_;
  absl::flat_hash_map<std::string, DnsState> dns_resolvers_;
};

}

#endif
