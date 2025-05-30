
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_CONNECTIVITY_STATE_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_CONNECTIVITY_STATE_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <map>
#include <memory>
#include <utility>

#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

const char* ConnectivityStateName(grpc_connectivity_state state);

// Note: Most callers will want to use

class ConnectivityStateWatcherInterface
    : public InternallyRefCounted<ConnectivityStateWatcherInterface> {
 public:
  ~ConnectivityStateWatcherInterface() override = default;

  virtual void Notify(grpc_connectivity_state new_state,
                      const absl::Status& status) = 0;

  void Orphan() override { Unref(); }
};

class AsyncConnectivityStateWatcherInterface
    : public ConnectivityStateWatcherInterface {
 public:
  ~AsyncConnectivityStateWatcherInterface() override = default;

  void Notify(grpc_connectivity_state new_state,
              const absl::Status& status) final;

 protected:
  class Notifier;

  explicit AsyncConnectivityStateWatcherInterface(
      std::shared_ptr<WorkSerializer> work_serializer = nullptr)
      : work_serializer_(std::move(work_serializer)) {}

  virtual void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                         const absl::Status& status) = 0;

 private:
  std::shared_ptr<WorkSerializer> work_serializer_;
};

class ConnectivityStateTracker {
 public:
  explicit ConnectivityStateTracker(
      const char* name, grpc_connectivity_state state = GRPC_CHANNEL_IDLE,
      const absl::Status& status = absl::Status())
      : name_(name), state_(state), status_(status) {}

  ~ConnectivityStateTracker();

  void AddWatcher(grpc_connectivity_state initial_state,
                  OrphanablePtr<ConnectivityStateWatcherInterface> watcher);

  void RemoveWatcher(ConnectivityStateWatcherInterface* watcher);

  void SetState(grpc_connectivity_state state, const absl::Status& status,
                const char* reason);

  grpc_connectivity_state state() const;

  absl::Status status() const { return status_; }

  size_t NumWatchers() const { return watchers_.size(); }

 private:
  const char* name_;
  std::atomic<grpc_connectivity_state> state_{grpc_connectivity_state()};
  absl::Status status_;
  absl::flat_hash_set<OrphanablePtr<ConnectivityStateWatcherInterface>>
      watchers_;
};

}

#endif
