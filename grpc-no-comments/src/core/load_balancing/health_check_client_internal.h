
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_HEALTH_CHECK_CLIENT_INTERNAL_H
#define GRPC_SRC_CORE_LOAD_BALANCING_HEALTH_CHECK_CLIENT_INTERNAL_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/client_channel/subchannel_interface_internal.h"
#include "src/core/client_channel/subchannel_stream_client.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

class HealthWatcher;

class HealthProducer final : public Subchannel::DataProducerInterface {
 public:
  HealthProducer() : interested_parties_(grpc_pollset_set_create()) {}
  ~HealthProducer() override { grpc_pollset_set_destroy(interested_parties_); }

  void Start(RefCountedPtr<Subchannel> subchannel);

  static UniqueTypeName Type() {
    static UniqueTypeName::Factory kFactory("health_check");
    return kFactory.Create();
  }

  UniqueTypeName type() const override { return Type(); }

  void AddWatcher(HealthWatcher* watcher,
                  const std::optional<std::string>& health_check_service_name);
  void RemoveWatcher(
      HealthWatcher* watcher,
      const std::optional<std::string>& health_check_service_name);

 private:
  class ConnectivityWatcher;

  class HealthChecker final : public InternallyRefCounted<HealthChecker> {
   public:
    HealthChecker(WeakRefCountedPtr<HealthProducer> producer,
                  absl::string_view health_check_service_name);

    void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

    void AddWatcherLocked(HealthWatcher* watcher)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&HealthProducer::mu_);

    bool RemoveWatcherLocked(HealthWatcher* watcher)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&HealthProducer::mu_);

    void OnConnectivityStateChangeLocked(grpc_connectivity_state state,
                                         const absl::Status& status)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&HealthProducer::mu_);

   private:
    class HealthStreamEventHandler;

    void StartHealthStreamLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&HealthProducer::mu_);

    void NotifyWatchersLocked(grpc_connectivity_state state,
                              absl::Status status)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&HealthProducer::mu_);

    void OnHealthWatchStatusChange(grpc_connectivity_state state,
                                   const absl::Status& status);

    WeakRefCountedPtr<HealthProducer> producer_;
    absl::string_view health_check_service_name_;
    std::shared_ptr<WorkSerializer> work_serializer_ =
        std::make_shared<WorkSerializer>(
            producer_->subchannel_->event_engine());

    std::optional<grpc_connectivity_state> state_
        ABSL_GUARDED_BY(&HealthProducer::mu_);
    absl::Status status_ ABSL_GUARDED_BY(&HealthProducer::mu_);
    OrphanablePtr<SubchannelStreamClient> stream_client_
        ABSL_GUARDED_BY(&HealthProducer::mu_);
    std::set<HealthWatcher*> watchers_ ABSL_GUARDED_BY(&HealthProducer::mu_);
  };

  void OnConnectivityStateChange(grpc_connectivity_state state,
                                 const absl::Status& status);
  void Orphaned() override;

  RefCountedPtr<Subchannel> subchannel_;
  ConnectivityWatcher* connectivity_watcher_;
  grpc_pollset_set* interested_parties_;

  Mutex mu_;
  std::optional<grpc_connectivity_state> state_ ABSL_GUARDED_BY(&mu_);
  absl::Status status_ ABSL_GUARDED_BY(&mu_);
  RefCountedPtr<ConnectedSubchannel> connected_subchannel_
      ABSL_GUARDED_BY(&mu_);
  std::map<std::string ,
           OrphanablePtr<HealthChecker>>
      health_checkers_ ABSL_GUARDED_BY(&mu_);
  std::set<HealthWatcher*> non_health_watchers_ ABSL_GUARDED_BY(&mu_);
};

class HealthWatcher final : public InternalSubchannelDataWatcherInterface {
 public:
  HealthWatcher(
      std::shared_ptr<WorkSerializer> work_serializer,
      std::optional<std::string> health_check_service_name,
      std::unique_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
          watcher)
      : work_serializer_(std::move(work_serializer)),
        health_check_service_name_(std::move(health_check_service_name)),
        watcher_(std::move(watcher)) {}
  ~HealthWatcher() override;

  UniqueTypeName type() const override { return HealthProducer::Type(); }

  void SetSubchannel(Subchannel* subchannel) override;

  std::shared_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
  TakeWatcher() {
    return std::move(watcher_);
  }
  void SetWatcher(
      std::shared_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
          watcher) {
    watcher_ = std::move(watcher);
  }

  void Notify(grpc_connectivity_state state, absl::Status status);

  grpc_pollset_set* interested_parties() const {
    return watcher_->interested_parties();
  }

 private:
  std::shared_ptr<WorkSerializer> work_serializer_;
  std::optional<std::string> health_check_service_name_;
  std::shared_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
      watcher_;
  RefCountedPtr<HealthProducer> producer_;
};

}

#endif
