Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Includes necessary gRPC core headers
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <string.h>

// Standard C++ includes
#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <variant>
#include <vector>

// ABSL (Abseil) includes for utilities and logging
#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/string_view.h"

// gRPC core internal headers
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/credentials/transport/xds/xds_credentials.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/server/server.h"
#include "src/core/server/server_config_selector.h"
#include "src/core/server/server_config_selector_filter.h"
#include "src/core/server/xds_channel_stack_modifier.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/host_port.h"
#include "src/core/util/match.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/uri.h"

// XDS related headers
#include "src/core/xds/grpc/certificate_provider_store.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_certificate_provider.h"
#include "src/core/xds/grpc/xds_client_grpc.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/grpc/xds_http_filter_registry.h"
#include "src/core/xds/grpc/xds_listener.h"
#include "src/core/xds/grpc/xds_listener_parser.h"
#include "src/core/xds/grpc/xds_route_config.h"
#include "src/core/xds/grpc/xds_route_config_parser.h"
#include "src/core/xds/grpc/xds_routing.h"
#include "src/core/xds/xds_client/xds_client.h"

namespace grpc_core {
namespace {

// Alias for XdsClient's ReadDelayHandle
using ReadDelayHandle = XdsClient::ReadDelayHandle;

// Main class for fetching XDS server configuration
class XdsServerConfigFetcher final : public ServerConfigFetcher {
 public:
  // Constructor taking XDS client and status notifier
  XdsServerConfigFetcher(RefCountedPtr<GrpcXdsClient> xds_client,
                         grpc_server_xds_status_notifier notifier);

  // Destructor that resets the XDS client
  ~XdsServerConfigFetcher() override {
    xds_client_.reset(DEBUG_LOCATION, "XdsServerConfigFetcher");
  }

  // Starts watching for configuration changes for a listening address
  void StartWatch(
      std::string listening_address,
      std::unique_ptr<ServerConfigFetcher::WatcherInterface> watcher) override;

  // Cancels an existing watch
  void CancelWatch(ServerConfigFetcher::WatcherInterface* watcher) override;

  // Returns the pollset set the XDS client is interested in
  grpc_pollset_set* interested_parties() override {
    return xds_client_->interested_parties();
  }

 private:
  // Forward declaration of ListenerWatcher class
  class ListenerWatcher;

  // XDS client instance
  RefCountedPtr<GrpcXdsClient> xds_client_;
  // Callback for notifying serving status changes
  const grpc_server_xds_status_notifier serving_status_notifier_;
  // Mutex for thread safety
  Mutex mu_;
  // Map of watchers to their corresponding ListenerWatchers
  std::map<ServerConfigFetcher::WatcherInterface*, ListenerWatcher*>
      listener_watchers_ ABSL_GUARDED_BY(mu_);
};

// Watcher for XDS listener resources
class XdsServerConfigFetcher::ListenerWatcher final
    : public XdsListenerResourceType::WatcherInterface {
 public:
  // Constructor
  ListenerWatcher(RefCountedPtr<GrpcXdsClient> xds_client,
                  std::unique_ptr<ServerConfigFetcher::WatcherInterface>
                      server_config_watcher,
                  grpc_server_xds_status_notifier serving_status_notifier,
                  std::string listening_address);

  // Destructor
  ~ListenerWatcher() override {
    xds_client_.reset(DEBUG_LOCATION, "ListenerWatcher");
  }

  // Called when the listener resource changes
  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsListenerResource>> listener,
      RefCountedPtr<ReadDelayHandle> read_delay_handle) override;

  // Called when there's an ambient error
  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<ReadDelayHandle> read_delay_handle) override;

  // Returns the listening address being watched
  const std::string& listening_address() const { return listening_address_; }

 private:
  // Forward declaration of FilterChainMatchManager
  class FilterChainMatchManager;

  // Handles fatal errors
  void OnFatalError(absl::Status status) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  // Called when a pending filter chain match manager is ready
  void PendingFilterChainMatchManagerReady(
      FilterChainMatchManager* filter_chain_match_manager) {
    MutexLock lock(&mu_);
    PendingFilterChainMatchManagerReadyLocked(filter_chain_match_manager);
  }
  
  // Thread-safe version of PendingFilterChainMatchManagerReady
  void PendingFilterChainMatchManagerReadyLocked(
      FilterChainMatchManager* filter_chain_match_manager)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  // XDS client instance
  RefCountedPtr<GrpcXdsClient> xds_client_;
  // Watcher for server configuration updates
  const std::unique_ptr<ServerConfigFetcher::WatcherInterface>
      server_config_watcher_;
  // Callback for serving status notifications
  const grpc_server_xds_status_notifier serving_status_notifier_;
  // The address being listened on
  const std::string listening_address_;
  // Mutex for thread safety
  Mutex mu_;
  // Current active filter chain match manager
  RefCountedPtr<FilterChainMatchManager> filter_chain_match_manager_
      ABSL_GUARDED_BY(mu_);
  // Pending filter chain match manager being initialized
  RefCountedPtr<FilterChainMatchManager> pending_filter_chain_match_manager_
      ABSL_GUARDED_BY(mu_);
};

// Manages filter chain matching for connections
class XdsServerConfigFetcher::ListenerWatcher::FilterChainMatchManager final
    : public ServerConfigFetcher::ConnectionManager {
 public:
  // Constructor
  FilterChainMatchManager(
      RefCountedPtr<GrpcXdsClient> xds_client,
      XdsListenerResource::FilterChainMap filter_chain_map,
      std::optional<XdsListenerResource::FilterChainData> default_filter_chain);

  // Destructor
  ~FilterChainMatchManager() override {
    xds_client_.reset(DEBUG_LOCATION, "FilterChainMatchManager");
  }

  // Updates channel args for a new connection based on filter chain matching
  absl::StatusOr<ChannelArgs> UpdateChannelArgsForConnection(
      const ChannelArgs& args, grpc_endpoint* tcp) override;

  // Starts RDS watches for all referenced route configuration names
  void StartRdsWatch(RefCountedPtr<ListenerWatcher> listener_watcher)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ListenerWatcher::mu_);

  // Returns the filter chain map
  const XdsListenerResource::FilterChainMap& filter_chain_map() const {
    return filter_chain_map_;
  }

  // Returns the default filter chain if set
  const std::optional<XdsListenerResource::FilterChainData>&
  default_filter_chain() const {
    return default_filter_chain_;
  }

 private:
  // Watcher for RDS updates
  class RouteConfigWatcher;
  
  // State for RDS updates
  struct RdsUpdateState {
    RouteConfigWatcher* watcher;
    std::optional<absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>>
        rds_update;
  };

  // Config selector implementations
  class XdsServerConfigSelector;
  class StaticXdsServerConfigSelectorProvider;
  class DynamicXdsServerConfigSelectorProvider;

  // Creates or gets an XDS certificate provider for a filter chain
  absl::StatusOr<RefCountedPtr<XdsCertificateProvider>>
  CreateOrGetXdsCertificateProviderFromFilterChainData(
      const XdsListenerResource::FilterChainData* filter_chain);
  
  // Called when the manager is orphaned
  void Orphaned() override;

  // Handles RDS updates
  void OnRouteConfigChanged(
      const std::string& resource_name,
      absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
          route_config);
  
  // Handles ambient errors from RDS watches
  void OnAmbientError(const std::string& resource_name, absl::Status status);

  // XDS client instance
  RefCountedPtr<GrpcXdsClient> xds_client_;

  // Parent listener watcher
  RefCountedPtr<ListenerWatcher> listener_watcher_;

  // Filter chain configuration
  XdsListenerResource::FilterChainMap filter_chain_map_;
  // Default filter chain if no match is found
  std::optional<XdsListenerResource::FilterChainData> default_filter_chain_;
  // Mutex for thread safety
  Mutex mu_;
  // Counter for pending RDS fetches
  size_t rds_resources_yet_to_fetch_ ABSL_GUARDED_BY(mu_) = 0;
  // Map of RDS resource names to their state
  std::map<std::string , RdsUpdateState> rds_map_
      ABSL_GUARDED_BY(mu_);
  // Cache of certificate providers
  std::map<const XdsListenerResource::FilterChainData*,
           RefCountedPtr<XdsCertificateProvider>>
      certificate_providers_map_ ABSL_GUARDED_BY(mu_);
};

// Watcher for RDS updates
class XdsServerConfigFetcher::ListenerWatcher::FilterChainMatchManager::
    RouteConfigWatcher final
    : public XdsRouteConfigResourceType::WatcherInterface {
 public:
  // Constructor
  RouteConfigWatcher(
      std::string resource_name,
      WeakRefCountedPtr<FilterChainMatchManager> filter_chain_match_manager)
      : resource_name_(std::move(resource_name)),
        filter_chain_match_manager_(std::move(filter_chain_match_manager)) {}

  // Called when the route configuration changes
  void OnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
          route_config,
      RefCountedPtr<ReadDelayHandle> ) override {
    filter_chain_match_manager_->OnRouteConfigChanged(resource_name_,
                                                      std::move(route_config));
  }

  // Called when there's an ambient error
  void OnAmbientError(
      absl::Status status,
      RefCountedPtr<ReadDelayHandle> ) override {
    filter_chain_match_manager_->OnAmbientError(resource_name_,
                                                std::move(status));
  }

 private:
  // The RDS resource name being watched
  std::string resource_name_;
  // Weak reference to parent filter chain match manager
  WeakRefCountedPtr<FilterChainMatchManager> filter_chain_match_manager_;
};

// Server config selector implementation for XDS
class XdsServerConfigFetcher::ListenerWatcher::FilterChainMatchManager::
    XdsServerConfigSelector final : public ServerConfigSelector {
 public:
  // Factory method to create a config selector
  static absl::StatusOr<RefCountedPtr<XdsServerConfigSelector>> Create(
      const XdsHttpFilterRegistry& http_filter_registry,
      std::shared_ptr<const XdsRouteConfigResource> rds_update,
      const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
          http_filters);
  
  // Destructor
  ~XdsServerConfigSelector() override = default;

  // Gets the call configuration based on request metadata
  absl::StatusOr<CallConfig> GetCallConfig(
      grpc_metadata_batch* metadata) override;

 private:
  // Represents a virtual host and its routes
  struct VirtualHost {
    // Represents a route within a virtual host
    struct Route {
      // Whether the route action is unsupported
      bool unsupported_action;

      // Route matchers
      XdsRouteConfigResource::Route::Matchers matchers;
      // Method configuration for the route
      RefCountedPtr<ServiceConfig> method_config;
    };

    // Iterator for route list
    class RouteListIterator final : public XdsRouting::RouteListIterator {
     public:
      explicit RouteListIterator(const std::vector<Route>* routes)
          : routes_(routes) {}

      size_t Size() const override { return routes_->size(); }

      const XdsRouteConfigResource::Route::Matchers& GetMatchersForRoute(
          size_t index) const override {
        return (*routes_)[index].matchers;
      }

     private:
      const std::vector<Route>* routes_;
    };

    // Domains for this virtual host
    std::vector<std::string> domains;
    // Routes within this virtual host
    std::vector<Route> routes;
  };

  // Iterator for virtual host list
  class VirtualHostListIterator final
      : public XdsRouting::VirtualHostListIterator {
   public:
    explicit VirtualHostListIterator(
        const std::vector<VirtualHost>* virtual_hosts)
        : virtual_hosts_(virtual_hosts) {}

    size_t Size() const override { return virtual_hosts_->size(); }

    const std::vector<std::string>& GetDomainsForVirtualHost(
        size_t index) const override {
      return (*virtual_hosts_)[index].domains;
    }

   private:
    const std::vector<VirtualHost>* virtual_hosts_;
  };

  // List of virtual hosts
  std::vector<VirtualHost> virtual_hosts_;
};

// Provider for static route configurations
class XdsServerConfigFetcher::ListenerWatcher::FilterChainMatchManager::
    StaticXdsServerConfigSelectorProvider final
    : public ServerConfigSelectorProvider {
 public:
  // Constructor with static route configuration
  StaticXdsServerConfigSelectorProvider(
      RefCountedPtr<GrpcXdsClient> xds_client,
      absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
          static_resource,
      std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>
          http_filters)
      : xds_client_(std::move(xds_client)),
        static_resource_(std::move(static_resource)),
        http_filters_(std::move(http_filters)) {}

  // Destructor
  ~StaticXdsServerConfigSelectorProvider() override {
    xds_client_.reset(DEBUG_LOCATION, "StaticXdsServerConfigSelectorProvider");
  }

  // Starts watching for configuration changes
  absl::StatusOr<RefCountedPtr<ServerConfigSelector>> Watch(
      std::unique_ptr<ServerConfigSelectorProvider::ServerConfigSelectorWatcher>
          watcher) override {
    CHECK(watcher_ == nullptr);
    watcher_ = std::move(watcher);
    if (!static_resource_.ok()) {
      return static_resource_.status();
    }
    return XdsServerConfigSelector::Create(
        static_cast<const GrpcXdsBootstrap&>(xds_client_->bootstrap())
            .http_filter_registry(),
        static_resource_.value(), http_filters_);
  }

  // Cancels the watch
  void CancelWatch() override { watcher_.reset(); }

 private:
  // Called when orphaned
  void Orphaned() override {}

  // XDS client instance
  RefCountedPtr<GrpcXdsClient> xds_client_;
  // Static route configuration
  absl::StatusOr<std::shared_ptr<const XdsRouteConfigResource>>
      static_resource_;

  // HTTP filters
  std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>
      http_filters_;
  // Watcher for configuration updates
  std::unique_ptr<ServerConfigSelectorProvider::ServerConfig