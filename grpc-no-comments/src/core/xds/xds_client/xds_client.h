
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_CLIENT_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_CLIENT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "envoy/admin/v3/config_dump_shared.upb.h"
#include "envoy/service/status/v3/csds.upb.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"
#include "src/core/xds/xds_client/xds_api.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "src/core/xds/xds_client/xds_locality.h"
#include "src/core/xds/xds_client/xds_metrics.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "src/core/xds/xds_client/xds_transport.h"
#include "upb/reflection/def.hpp"

namespace grpc_core {

namespace testing {
class XdsClientTestPeer;
}

class XdsClient : public DualRefCounted<XdsClient> {
 public:

  static constexpr absl::string_view kOldStyleAuthority = "#old";

  class ReadDelayHandle : public RefCounted<ReadDelayHandle> {
   public:
    static RefCountedPtr<ReadDelayHandle> NoWait() { return nullptr; }
  };

  // Note: Most callers will not use this API directly but rather via a

  class ResourceWatcherInterface : public RefCounted<ResourceWatcherInterface> {
   public:
    virtual void OnGenericResourceChanged(
        absl::StatusOr<std::shared_ptr<const XdsResourceType::ResourceData>>
            resource,
        RefCountedPtr<ReadDelayHandle> read_delay_handle)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&work_serializer_) = 0;
    virtual void OnAmbientError(
        absl::Status status, RefCountedPtr<ReadDelayHandle> read_delay_handle)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&work_serializer_) = 0;
  };

  XdsClient(
      std::shared_ptr<XdsBootstrap> bootstrap,
      RefCountedPtr<XdsTransportFactory> transport_factory,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine,
      std::unique_ptr<XdsMetricsReporter> metrics_reporter,
      std::string user_agent_name, std::string user_agent_version,

      Duration resource_request_timeout = Duration::Zero());
  ~XdsClient() override;

  // Note: Most callers will not use this API directly but rather via a

  void WatchResource(const XdsResourceType* type, absl::string_view name,
                     RefCountedPtr<ResourceWatcherInterface> watcher);
  void CancelResourceWatch(const XdsResourceType* type,
                           absl::string_view listener_name,
                           ResourceWatcherInterface* watcher,
                           bool delay_unsubscription = false);

  virtual void ResetBackoff();

  const XdsBootstrap& bootstrap() const {
    return *bootstrap_;
  }

  XdsTransportFactory* transport_factory() const {
    return transport_factory_.get();
  }

  grpc_event_engine::experimental::EventEngine* engine() {
    return engine_.get();
  }

 protected:
  void Orphaned() override;

  Mutex* mu() ABSL_LOCK_RETURNED(&mu_) { return &mu_; }

  void DumpClientConfig(std::set<std::string>* string_pool, upb_Arena* arena,
                        envoy_service_status_v3_ClientConfig* client_config)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  struct ResourceCountLabels {
    absl::string_view xds_authority;
    absl::string_view resource_type;
    absl::string_view cache_state;
  };
  void ReportResourceCounts(
      absl::FunctionRef<void(const ResourceCountLabels&, uint64_t)> func)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  void ReportServerConnections(
      absl::FunctionRef<void(absl::string_view , bool)> func)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

 private:
  friend testing::XdsClientTestPeer;

  struct XdsResourceKey {
    std::string id;
    std::vector<URI::QueryParam> query_params;

    bool operator<(const XdsResourceKey& other) const {
      int c = id.compare(other.id);
      if (c != 0) return c < 0;
      return query_params < other.query_params;
    }
  };

  struct AuthorityState;

  struct XdsResourceName {
    std::string authority;
    XdsResourceKey key;
  };

  class XdsChannel final : public DualRefCounted<XdsChannel> {
   public:
    template <typename T>
    class RetryableCall;

    class AdsCall;

    XdsChannel(WeakRefCountedPtr<XdsClient> xds_client,
               const XdsBootstrap::XdsServer& server);
    ~XdsChannel() override;

    XdsClient* xds_client() const { return xds_client_.get(); }

    void ResetBackoff();

    const absl::Status& status() const { return status_; }

    void SubscribeLocked(const XdsResourceType* type,
                         const XdsResourceName& name)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&XdsClient::mu_);
    void UnsubscribeLocked(const XdsResourceType* type,
                           const XdsResourceName& name,
                           bool delay_unsubscription)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&XdsClient::mu_);

    absl::string_view server_uri() const {
      return server_.target()->server_uri();
    }

   private:
    class ConnectivityFailureWatcher;

    bool MaybeFallbackLocked(const std::string& authority,
                             XdsClient::AuthorityState& authority_state)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&XdsClient::mu_);
    void SetHealthyLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&XdsClient::mu_);
    void Orphaned() override;

    void OnConnectivityFailure(absl::Status status);

    void SetChannelStatusLocked(absl::Status status)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&XdsClient::mu_);

    WeakRefCountedPtr<XdsClient> xds_client_;

    const XdsBootstrap::XdsServer& server_;

    RefCountedPtr<XdsTransportFactory::XdsTransport> transport_;
    RefCountedPtr<XdsTransportFactory::XdsTransport::ConnectivityFailureWatcher>
        failure_watcher_;

    bool shutting_down_ = false;

    OrphanablePtr<RetryableCall<AdsCall>> ads_call_;

    std::map<const XdsResourceType*, std::string >
        resource_type_version_map_;

    absl::Status status_;
  };

  using WatcherSet =
      absl::flat_hash_set<RefCountedPtr<ResourceWatcherInterface>,
                          RefCountedPtrHash<ResourceWatcherInterface>,
                          RefCountedPtrEq<ResourceWatcherInterface>>;

  class ResourceState {
   public:

    enum ClientResourceStatus {

      REQUESTED = 1,

      DOES_NOT_EXIST,

      ACKED,

      NACKED,

      RECEIVED_ERROR,

      TIMEOUT,
    };
    static_assert(static_cast<ClientResourceStatus>(envoy_admin_v3_REQUESTED) ==
                  ClientResourceStatus::REQUESTED);
    static_assert(
        static_cast<ClientResourceStatus>(envoy_admin_v3_DOES_NOT_EXIST) ==
        ClientResourceStatus::DOES_NOT_EXIST);
    static_assert(static_cast<ClientResourceStatus>(envoy_admin_v3_ACKED) ==
                  ClientResourceStatus::ACKED);
    static_assert(static_cast<ClientResourceStatus>(envoy_admin_v3_NACKED) ==
                  ClientResourceStatus::NACKED);
    static_assert(
        static_cast<ClientResourceStatus>(envoy_admin_v3_RECEIVED_ERROR) ==
        ClientResourceStatus::RECEIVED_ERROR);
    static_assert(static_cast<ClientResourceStatus>(envoy_admin_v3_TIMEOUT) ==
                  ClientResourceStatus::TIMEOUT);

    void AddWatcher(RefCountedPtr<ResourceWatcherInterface> watcher) {
      watchers_.insert(std::move(watcher));
    }
    void RemoveWatcher(ResourceWatcherInterface* watcher) {
      watchers_.erase(watcher);
    }
    bool HasWatchers() const { return !watchers_.empty(); }
    const WatcherSet& watchers() const { return watchers_; }

    void SetAcked(std::shared_ptr<const XdsResourceType::ResourceData> resource,
                  std::string serialized_proto, std::string version,
                  Timestamp update_time);
    void SetNacked(const std::string& version, absl::string_view details,
                   Timestamp update_time, bool drop_cached_resource);
    void SetReceivedError(const std::string& version, absl::Status status,
                          Timestamp update_time, bool drop_cached_resource);
    void SetDoesNotExistOnLdsOrCdsDeletion(const std::string& version,
                                           Timestamp update_time,
                                           bool drop_cached_resource);
    void SetDoesNotExistOnTimeout();
    void SetTimeout(const std::string& details);

    ClientResourceStatus client_status() const { return client_status_; }
    absl::string_view CacheStateString() const;

    bool HasResource() const { return resource_ != nullptr; }
    std::shared_ptr<const XdsResourceType::ResourceData> resource() const {
      return resource_;
    }

    const absl::Status& failed_status() const { return failed_status_; }

    void FillGenericXdsConfig(
        upb_StringView type_url, upb_StringView resource_name, upb_Arena* arena,
        envoy_service_status_v3_ClientConfig_GenericXdsConfig* entry) const;

   private:
    WatcherSet watchers_;

    std::shared_ptr<const XdsResourceType::ResourceData> resource_;

    ClientResourceStatus client_status_ = REQUESTED;

    std::string serialized_proto_;

    Timestamp update_time_;

    std::string version_;

    absl::Status failed_status_;

    std::string failed_version_;

    Timestamp failed_update_time_;
  };

  struct AuthorityState {
    std::vector<RefCountedPtr<XdsChannel>> xds_channels;
    std::map<const XdsResourceType*, std::map<XdsResourceKey, ResourceState>>
        type_map;
  };

  absl::Status AppendNodeToStatus(const absl::Status& status) const;

  void NotifyWatchersOnResourceChanged(
      absl::StatusOr<std::shared_ptr<const XdsResourceType::ResourceData>>
          resource,
      WatcherSet watchers, RefCountedPtr<ReadDelayHandle> read_delay_handle);

  void NotifyWatchersOnAmbientError(
      absl::Status status, WatcherSet watchers,
      RefCountedPtr<ReadDelayHandle> read_delay_handle);

  void NotifyWatchersOnError(const ResourceState& resource_state,
                             RefCountedPtr<ReadDelayHandle> read_delay_handle,

                             WatcherSet watchers = {},

                             absl::Status status = absl::OkStatus());

  void MaybeRegisterResourceTypeLocked(const XdsResourceType* resource_type)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  const XdsResourceType* GetResourceTypeLocked(absl::string_view resource_type)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  bool HasUncachedResources(const AuthorityState& authority_state);

  void MaybeRemoveUnsubscribedCacheEntriesForTypeLocked(
      XdsChannel* xds_channel, const XdsResourceType* type)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  absl::StatusOr<XdsResourceName> ParseXdsResourceName(
      absl::string_view name, const XdsResourceType* type);
  static std::string ConstructFullXdsResourceName(
      absl::string_view authority, absl::string_view resource_type,
      const XdsResourceKey& key);

  RefCountedPtr<XdsChannel> GetOrCreateXdsChannelLocked(
      const XdsBootstrap::XdsServer& server, const char* reason)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  std::shared_ptr<XdsBootstrap> bootstrap_;
  const std::string user_agent_name_;
  const std::string user_agent_version_;
  RefCountedPtr<XdsTransportFactory> transport_factory_;
  const Duration request_timeout_;
  const bool xds_federation_enabled_;
  WorkSerializer work_serializer_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine_;
  std::unique_ptr<XdsMetricsReporter> metrics_reporter_;

  Mutex mu_;

  std::map<absl::string_view , const XdsResourceType*>
      resource_types_ ABSL_GUARDED_BY(mu_);
  upb::DefPool def_pool_ ABSL_GUARDED_BY(mu_);

  std::map<std::string , XdsChannel*> xds_channel_map_
      ABSL_GUARDED_BY(mu_);

  std::map<std::string , AuthorityState> authority_state_map_
      ABSL_GUARDED_BY(mu_);

  WatcherSet invalid_watchers_ ABSL_GUARDED_BY(mu_);

  bool shutting_down_ ABSL_GUARDED_BY(mu_) = false;
};

}

#endif
