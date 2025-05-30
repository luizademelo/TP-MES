
// Copyright 2015 gRPC authors.

#include "src/core/lib/transport/connectivity_state.h"

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

const char* ConnectivityStateName(grpc_connectivity_state state) {
  switch (state) {
    case GRPC_CHANNEL_IDLE:
      return "IDLE";
    case GRPC_CHANNEL_CONNECTING:
      return "CONNECTING";
    case GRPC_CHANNEL_READY:
      return "READY";
    case GRPC_CHANNEL_TRANSIENT_FAILURE:
      return "TRANSIENT_FAILURE";
    case GRPC_CHANNEL_SHUTDOWN:
      return "SHUTDOWN";
  }
  GPR_UNREACHABLE_CODE(return "UNKNOWN");
}

class AsyncConnectivityStateWatcherInterface::Notifier {
 public:
  Notifier(RefCountedPtr<AsyncConnectivityStateWatcherInterface> watcher,
           grpc_connectivity_state state, const absl::Status& status,
           const std::shared_ptr<WorkSerializer>& work_serializer)
      : watcher_(std::move(watcher)), state_(state), status_(status) {
    if (work_serializer != nullptr) {
      work_serializer->Run(
          [this]() { SendNotification(this, absl::OkStatus()); });
    } else {
      GRPC_CLOSURE_INIT(&closure_, SendNotification, this,
                        grpc_schedule_on_exec_ctx);
      ExecCtx::Run(DEBUG_LOCATION, &closure_, absl::OkStatus());
    }
  }

 private:
  static void SendNotification(void* arg, grpc_error_handle ) {
    Notifier* self = static_cast<Notifier*>(arg);
    GRPC_TRACE_LOG(connectivity_state, INFO)
        << "watcher " << self->watcher_.get()
        << ": delivering async notification for "
        << ConnectivityStateName(self->state_) << " ("
        << self->status_.ToString() << ")";
    self->watcher_->OnConnectivityStateChange(self->state_, self->status_);
    delete self;
  }

  RefCountedPtr<AsyncConnectivityStateWatcherInterface> watcher_;
  const grpc_connectivity_state state_;
  const absl::Status status_;
  grpc_closure closure_;
};

void AsyncConnectivityStateWatcherInterface::Notify(
    grpc_connectivity_state state, const absl::Status& status) {

  new Notifier(RefAsSubclass<AsyncConnectivityStateWatcherInterface>(), state,
               status, work_serializer_);
}

ConnectivityStateTracker::~ConnectivityStateTracker() {
  grpc_connectivity_state current_state =
      state_.load(std::memory_order_relaxed);
  if (current_state == GRPC_CHANNEL_SHUTDOWN) return;
  for (const auto& watcher : watchers_) {
    GRPC_TRACE_LOG(connectivity_state, INFO)
        << "ConnectivityStateTracker " << name_ << "[" << this
        << "]: notifying watcher " << watcher.get() << ": "
        << ConnectivityStateName(current_state) << " -> "
        << ConnectivityStateName(GRPC_CHANNEL_SHUTDOWN);
    watcher->Notify(GRPC_CHANNEL_SHUTDOWN, absl::Status());
  }
}

void ConnectivityStateTracker::AddWatcher(
    grpc_connectivity_state initial_state,
    OrphanablePtr<ConnectivityStateWatcherInterface> watcher) {
  GRPC_TRACE_LOG(connectivity_state, INFO)
      << "ConnectivityStateTracker " << name_ << "[" << this
      << "]: add watcher " << watcher.get();
  grpc_connectivity_state current_state =
      state_.load(std::memory_order_relaxed);
  if (initial_state != current_state) {
    GRPC_TRACE_LOG(connectivity_state, INFO)
        << "ConnectivityStateTracker " << name_ << "[" << this
        << "]: notifying watcher " << watcher.get() << ": "
        << ConnectivityStateName(initial_state) << " -> "
        << ConnectivityStateName(current_state);
    watcher->Notify(current_state, status_);
  }

  if (current_state != GRPC_CHANNEL_SHUTDOWN) {
    watchers_.insert(std::move(watcher));
  }
}

void ConnectivityStateTracker::RemoveWatcher(
    ConnectivityStateWatcherInterface* watcher) {
  GRPC_TRACE_LOG(connectivity_state, INFO)
      << "ConnectivityStateTracker " << name_ << "[" << this
      << "]: remove watcher " << watcher;
  watchers_.erase(watcher);
}

void ConnectivityStateTracker::SetState(grpc_connectivity_state state,
                                        const absl::Status& status,
                                        const char* reason) {
  grpc_connectivity_state current_state =
      state_.load(std::memory_order_relaxed);
  if (state == current_state) return;
  GRPC_TRACE_LOG(connectivity_state, INFO)
      << "ConnectivityStateTracker " << name_ << "[" << this
      << "]: " << ConnectivityStateName(current_state) << " -> "
      << ConnectivityStateName(state) << " (" << reason << ", "
      << status.ToString() << ")";
  state_.store(state, std::memory_order_relaxed);
  status_ = status;
  for (const auto& watcher : watchers_) {
    GRPC_TRACE_LOG(connectivity_state, INFO)
        << "ConnectivityStateTracker " << name_ << "[" << this
        << "]: notifying watcher " << watcher.get() << ": "
        << ConnectivityStateName(current_state) << " -> "
        << ConnectivityStateName(state);
    watcher->Notify(state, status);
  }

  if (state == GRPC_CHANNEL_SHUTDOWN) watchers_.clear();
}

grpc_connectivity_state ConnectivityStateTracker::state() const {
  grpc_connectivity_state state = state_.load(std::memory_order_relaxed);
  GRPC_TRACE_LOG(connectivity_state, INFO)
      << "ConnectivityStateTracker " << name_ << "[" << this
      << "]: get current state: " << ConnectivityStateName(state);
  return state;
}

}
