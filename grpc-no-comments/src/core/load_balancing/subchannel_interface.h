
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_SUBCHANNEL_INTERFACE_H
#define GRPC_SRC_CORE_LOAD_BALANCING_SUBCHANNEL_INTERFACE_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class SubchannelInterface : public DualRefCounted<SubchannelInterface> {
 public:
  class ConnectivityStateWatcherInterface {
   public:
    virtual ~ConnectivityStateWatcherInterface() = default;

    virtual void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                           absl::Status status) = 0;

    virtual grpc_pollset_set* interested_parties() = 0;
  };

  class DataWatcherInterface {
   public:
    virtual ~DataWatcherInterface() = default;
  };

  explicit SubchannelInterface(const char* trace = nullptr)
      : DualRefCounted<SubchannelInterface>(trace) {}

  ~SubchannelInterface() override = default;

  virtual void WatchConnectivityState(
      std::unique_ptr<ConnectivityStateWatcherInterface> watcher) = 0;

  virtual void CancelConnectivityStateWatch(
      ConnectivityStateWatcherInterface* watcher) = 0;

  virtual void RequestConnection() = 0;

  virtual void ResetBackoff() = 0;

  virtual void AddDataWatcher(
      std::unique_ptr<DataWatcherInterface> watcher) = 0;

  virtual void CancelDataWatcher(DataWatcherInterface* watcher) = 0;

  virtual std::string address() const = 0;

 protected:
  void Orphaned() override {}
};

class DelegatingSubchannel : public SubchannelInterface {
 public:
  explicit DelegatingSubchannel(RefCountedPtr<SubchannelInterface> subchannel)
      : wrapped_subchannel_(std::move(subchannel)) {}

  RefCountedPtr<SubchannelInterface> wrapped_subchannel() const {
    return wrapped_subchannel_;
  }

  void WatchConnectivityState(
      std::unique_ptr<ConnectivityStateWatcherInterface> watcher) override {
    return wrapped_subchannel_->WatchConnectivityState(std::move(watcher));
  }
  void CancelConnectivityStateWatch(
      ConnectivityStateWatcherInterface* watcher) override {
    return wrapped_subchannel_->CancelConnectivityStateWatch(watcher);
  }
  void RequestConnection() override {
    wrapped_subchannel_->RequestConnection();
  }
  void ResetBackoff() override { wrapped_subchannel_->ResetBackoff(); }
  void AddDataWatcher(std::unique_ptr<DataWatcherInterface> watcher) override {
    wrapped_subchannel_->AddDataWatcher(std::move(watcher));
  }
  void CancelDataWatcher(DataWatcherInterface* watcher) override {
    wrapped_subchannel_->CancelDataWatcher(watcher);
  }

  std::string address() const override {
    return wrapped_subchannel_->address();
  }

 private:
  RefCountedPtr<SubchannelInterface> wrapped_subchannel_;
};

}

#endif
