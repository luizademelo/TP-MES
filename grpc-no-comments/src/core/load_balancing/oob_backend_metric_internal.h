
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_OOB_BACKEND_METRIC_INTERNAL_H
#define GRPC_SRC_CORE_LOAD_BALANCING_OOB_BACKEND_METRIC_INTERNAL_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <set>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/client_channel/subchannel_interface_internal.h"
#include "src/core/client_channel/subchannel_stream_client.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/oob_backend_metric.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

class OrcaWatcher;

class OrcaProducer final : public Subchannel::DataProducerInterface {
 public:
  void Start(RefCountedPtr<Subchannel> subchannel);

  static UniqueTypeName Type() {
    static UniqueTypeName::Factory kFactory("orca");
    return kFactory.Create();
  }

  UniqueTypeName type() const override { return Type(); }

  void AddWatcher(OrcaWatcher* watcher);
  void RemoveWatcher(OrcaWatcher* watcher);

 private:
  class ConnectivityWatcher;
  class OrcaStreamEventHandler;

  void Orphaned() override;

  Duration GetMinIntervalLocked() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  void MaybeStartStreamLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  void OnConnectivityStateChange(grpc_connectivity_state state);

  void NotifyWatchers(const BackendMetricData& backend_metric_data);

  RefCountedPtr<Subchannel> subchannel_;
  RefCountedPtr<ConnectedSubchannel> connected_subchannel_;
  ConnectivityWatcher* connectivity_watcher_;
  Mutex mu_;
  std::set<OrcaWatcher*> watchers_ ABSL_GUARDED_BY(mu_);
  Duration report_interval_ ABSL_GUARDED_BY(mu_) = Duration::Infinity();
  OrphanablePtr<SubchannelStreamClient> stream_client_ ABSL_GUARDED_BY(mu_);
};

class OrcaWatcher final : public InternalSubchannelDataWatcherInterface {
 public:
  OrcaWatcher(Duration report_interval,
              std::unique_ptr<OobBackendMetricWatcher> watcher)
      : report_interval_(report_interval), watcher_(std::move(watcher)) {}
  ~OrcaWatcher() override;

  Duration report_interval() const { return report_interval_; }
  OobBackendMetricWatcher* watcher() const { return watcher_.get(); }

  UniqueTypeName type() const override { return OrcaProducer::Type(); }

  void SetSubchannel(Subchannel* subchannel) override;

 private:
  const Duration report_interval_;
  std::unique_ptr<OobBackendMetricWatcher> watcher_;
  RefCountedPtr<OrcaProducer> producer_;
};

}

#endif
