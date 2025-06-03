Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Client channel implementation for gRPC

#include "src/core/client_channel/client_channel.h"

// Standard includes
#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/json.h>
#include <grpc/support/metrics.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <limits.h>

// STL includes
#include <algorithm>
#include <functional>
#include <new>
#include <optional>
#include <set>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// Abseil includes
#include "absl/cleanup/cleanup.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/cord.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"

// Internal gRPC includes
#include "src/core/call/call_spine.h"
#include "src/core/call/client_call.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/status_util.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/client_channel/client_channel_service_config.h"
#include "src/core/client_channel/config_selector.h"
#include "src/core/client_channel/dynamic_filters.h"
#include "src/core/client_channel/global_subchannel_pool.h"
#include "src/core/client_channel/local_subchannel_pool.h"
#include "src/core/client_channel/retry_interceptor.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/client_channel/subchannel_interface_internal.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/ext/filters/channel_idle/legacy_channel_idle_filter.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/exec_ctx_wakeup_scheduler.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/sync.h"
#include "src/core/util/useful.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

using grpc_event_engine::experimental::EventEngine;

using internal::ClientChannelMethodParsedConfig;

// ResolverResultHandler implementation for ClientChannel
class ClientChannel::ResolverResultHandler : public Resolver::ResultHandler {
 public:
  explicit ResolverResultHandler(
      WeakRefCountedPtr<ClientChannel> client_channel)
      : client_channel_(std::move(client_channel)) {}

  ~ResolverResultHandler() override {
    GRPC_TRACE_LOG(client_channel, INFO)
        << "client_channel=" << client_channel_.get()
        << ": resolver shutdown complete";
  }

  // Called when resolver result changes
  void ReportResult(Resolver::Result result) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_) {
    client_channel_->OnResolverResultChangedLocked(std::move(result));
  }

 private:
  WeakRefCountedPtr<ClientChannel> client_channel_;
};

// Wrapper around Subchannel that adds ClientChannel-specific functionality
class ClientChannel::SubchannelWrapper
    : public SubchannelInterfaceWithCallDestination {
 public:
  SubchannelWrapper(WeakRefCountedPtr<ClientChannel> client_channel,
                    RefCountedPtr<Subchannel> subchannel);
  ~SubchannelWrapper() override;

  void Orphaned() override;
  void WatchConnectivityState(
      std::unique_ptr<ConnectivityStateWatcherInterface> watcher) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_);
  void CancelConnectivityStateWatch(
      ConnectivityStateWatcherInterface* watcher) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_);

  RefCountedPtr<UnstartedCallDestination> call_destination() override {
    return subchannel_->call_destination();
  }

  void RequestConnection() override { subchannel_->RequestConnection(); }

  void ResetBackoff() override { subchannel_->ResetBackoff(); }

  void AddDataWatcher(std::unique_ptr<DataWatcherInterface> watcher) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_);
  void CancelDataWatcher(DataWatcherInterface* watcher) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_);
  void ThrottleKeepaliveTime(int new_keepalive_time);
  std::string address() const override { return subchannel_->address(); }

 private:
  // Wrapper for ConnectivityStateWatcherInterface
  class WatcherWrapper;

  // Comparator for DataWatcherInterface
  struct DataWatcherLessThan {
    using is_transparent = void;
    bool operator()(const std::unique_ptr<DataWatcherInterface>& p1,
                    const std::unique_ptr<DataWatcherInterface>& p2) const {
      return p1 < p2;
    }
    bool operator()(const std::unique_ptr<DataWatcherInterface>& p1,
                    const DataWatcherInterface* p2) const {
      return p1.get() < p2;
    }
    bool operator()(const DataWatcherInterface* p1,
                    const std::unique_ptr<DataWatcherInterface>& p2) const {
      return p1 < p2.get();
    }
  };

  WeakRefCountedPtr<ClientChannel> client_channel_;
  RefCountedPtr<Subchannel> subchannel_;

  // Maps watchers to their wrappers
  std::map<ConnectivityStateWatcherInterface*, WatcherWrapper*> watcher_map_
      ABSL_GUARDED_BY(*client_channel_->work_serializer_);
  // Set of data watchers
  std::set<std::unique_ptr<DataWatcherInterface>, DataWatcherLessThan>
      data_watchers_ ABSL_GUARDED_BY(*client_channel_->work_serializer_);
};

// WatcherWrapper implementation
class ClientChannel::SubchannelWrapper::WatcherWrapper
    : public Subchannel::ConnectivityStateWatcherInterface {
 public:
  WatcherWrapper(
      std::unique_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
          watcher,
      RefCountedPtr<SubchannelWrapper> subchannel_wrapper)
      : watcher_(std::move(watcher)),
        subchannel_wrapper_(std::move(subchannel_wrapper)) {}

  ~WatcherWrapper() override {
    subchannel_wrapper_.reset(DEBUG_LOCATION, "WatcherWrapper");
  }

  // Called when connectivity state changes
  void OnConnectivityStateChange(grpc_connectivity_state state,
                                 const absl::Status& status) override {
    GRPC_TRACE_LOG(client_channel, INFO)
        << "client_channel=" << subchannel_wrapper_->client_channel_.get()
        << ": connectivity change for subchannel wrapper "
        << subchannel_wrapper_.get() << " subchannel "
        << subchannel_wrapper_->subchannel_.get()
        << "; hopping into work_serializer";
    auto self = RefAsSubclass<WatcherWrapper>();
    subchannel_wrapper_->client_channel_->work_serializer_->Run(
        [self, state, status]() ABSL_EXCLUSIVE_LOCKS_REQUIRED(
            *self->subchannel_wrapper_->client_channel_->work_serializer_) {
          self->ApplyUpdateInControlPlaneWorkSerializer(state, status);
        });
  }

  grpc_pollset_set* interested_parties() override { return nullptr; }

 private:
  // Applies connectivity state update in work serializer
  void ApplyUpdateInControlPlaneWorkSerializer(grpc_connectivity_state state,
                                               const absl::Status& status)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(
          *subchannel_wrapper_->client_channel_->work_serializer_) {
    GRPC_TRACE_LOG(client_channel, INFO)
        << "client_channel=" << subchannel_wrapper_->client_channel_.get()
        << ": processing connectivity change in work serializer for subchannel "
           "wrapper "
        << subchannel_wrapper_.get() << " subchannel "
        << subchannel_wrapper_->subchannel_.get()
        << " watcher=" << watcher_.get()
        << " state=" << ConnectivityStateName(state) << " status=" << status;
    // Handle keepalive throttling if present in status payload
    auto keepalive_throttling = status.GetPayload(kKeepaliveThrottlingKey);
    if (keepalive_throttling.has_value()) {
      int new_keepalive_time = -1;
      if (absl::SimpleAtoi(std::string(keepalive_throttling.value()),
                           &new_keepalive_time)) {
        if (new_keepalive_time >
            subchannel_wrapper_->client_channel_->keepalive_time_) {
          subchannel_wrapper_->client_channel_->keepalive_time_ =
              new_keepalive_time;
          GRPC_TRACE_LOG(client_channel, INFO)
              << "client_channel=" << subchannel_wrapper_->client_channel_.get()
              << ": throttling keepalive time to "
              << subchannel_wrapper_->client_channel_->keepalive_time_;

          // Apply new keepalive time to all subchannel wrappers
          for (auto* subchannel_wrapper :
               subchannel_wrapper_->client_channel_->subchannel_wrappers_) {
            subchannel_wrapper->ThrottleKeepaliveTime(new_keepalive_time);
          }
        }
      } else {
        LOG(ERROR) << "client_channel="
                   << subchannel_wrapper_->client_channel_.get()
                   << ": Illegal keepalive throttling value "
                   << std::string(keepalive_throttling.value());
      }
    }

    // Notify watcher of state change
    watcher_->OnConnectivityStateChange(
        state,
        state == GRPC_CHANNEL_TRANSIENT_FAILURE ? status : absl::OkStatus());
  }

  std::unique_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
      watcher_;
  RefCountedPtr<SubchannelWrapper> subchannel_wrapper_;
};

// SubchannelWrapper implementation
ClientChannel::SubchannelWrapper::SubchannelWrapper(
    WeakRefCountedPtr<ClientChannel> client_channel,
    RefCountedPtr<Subchannel> subchannel)
    : SubchannelInterfaceWithCallDestination(
          GRPC_TRACE_FLAG_ENABLED(client_channel) ? "SubchannelWrapper"
                                                  : nullptr),
      client_channel_(std::move(client_channel)),
      subchannel_(std::move(subchannel)) {
  GRPC_TRACE_LOG(client_channel, INFO)
      << "client_channel=" << client_channel_.get()
      << ": creating subchannel wrapper " << this << " for subchannel "
      << subchannel_.get();
#ifndef NDEBUG
  DCHECK(client_channel_->work_serializer_->RunningInWorkSerializer());
#endif
  // Update channelz if enabled
  if (client_channel_->channelz_node_ != nullptr) {
    auto* subchannel_node = subchannel_->channelz_node();
    if (subchannel_node != nullptr) {
      auto it =
          client_channel_->subchannel_refcount_map_.find(subchannel_.get());
      if (it == client_channel_->subchannel_refcount_map_.end()) {
        subchannel_node->AddParent(client_channel_->channelz_node_);
        it = client_channel_->subchannel_refcount_map_
                 .emplace(subchannel_.get(), 0)
                 .first;
      }
      ++it->second;
    }
  }
  client_channel_->subchannel_wrappers_.insert(this);
}

ClientChannel::SubchannelWrapper::~SubchannelWrapper() {
  GRPC_TRACE_LOG(client_channel, INFO)
      << "client_channel=" << client_channel_.get()
      << ": destroying subchannel wrapper " << this << " for subchannel "
      << subchannel_.get();
}

void ClientChannel::SubchannelWrapper::Orphaned() {
  // Clean up in work serializer
  auto self = WeakRefAsSubclass<SubchannelWrapper>(DEBUG_LOCATION,
                                                   "subchannel map cleanup");
  client_channel_->work_serializer_->Run(
      [self]() ABSL_EXCLUSIVE_LOCKS_REQUIRED(
          *self->client_channel_->work_serializer_) {
        self->client_channel_->subchannel_wrappers_.erase(self.get());
        // Update channelz if enabled
        if (self->client_channel_->channelz_node_ != nullptr) {
          auto* subchannel_node = self->subchannel_->channelz_node();
          if (subchannel_node != nullptr) {
            auto it = self->client_channel_->subchannel_refcount_map_.find(
                self->subchannel_.get());
            CHECK(it != self->client_channel_->subchannel_refcount_map_.end());
            --it->second;
            if (it->second == 0) {
              subchannel_node->RemoveParent(
                  self->client_channel_->channelz_node_);
              self->client_channel_->subchannel_refcount_map_.erase(it);
            }
          }
        }
      });
}

void ClientChannel::SubchannelWrapper::WatchConnectivityState(
    std::unique_ptr<ConnectivityStateWatcherInterface> watcher) {
  auto& watcher_wrapper = watcher_map_[watcher.get()];
  CHECK(watcher_wrapper == nullptr);
  watcher_wrapper = new WatcherWrapper(
      std::move(watcher),
      RefAsSubclass<SubchannelWrapper>(DEBUG_LOCATION, "WatcherWrapper"));
  subchannel_->WatchConnectivityState(
      RefCountedPtr<Subchannel::ConnectivityStateWatcherInterface>(
          watcher_wrapper));
}

void ClientChannel::SubchannelWrapper::CancelConnectivityStateWatch(
    ConnectivityStateWatcherInterface* watcher) {
  auto it = watcher_map_.find(watcher);
  CHECK(it != watcher_map_.end());
  subchannel_->CancelConnectivityStateWatch(it->second);
  watcher_map_.erase(it);
}

void ClientChannel::SubchannelWrapper::AddDataWatcher(
    std::unique_ptr<DataWatcherInterface> watcher) {
  static_cast<InternalSubchannelDataWatcherInterface*>(watcher.get())
      ->SetSubchannel(subchannel_.get());
  CHECK(data_watchers_.insert(std::move(watcher)).second);
}

void ClientChannel::SubchannelWrapper::CancelDataWatcher(
    DataWatcherInterface* watcher) {
  auto it = data_watchers_.find(watcher);
  if (it != data_watchers_.end()) data_watchers_.erase(it);
}

void ClientChannel::SubchannelWrapper::ThrottleKeepaliveTime(
    int new_keepalive_time) {
  subchannel_->ThrottleKeepaliveTime(new_keepalive_time);
}

// ChannelControlHelper implementation for ClientChannel
class ClientChannel::ClientChannelControlHelper
    : public LoadBalancingPolicy::ChannelControlHelper {
 public:
  explicit ClientChannelControlHelper(
      WeakRefCountedPtr<ClientChannel> client_channel)
      : client_channel_(std::move(client_channel)) {}

  ~ClientChannelControlHelper() override {
    client_channel_.reset(DEBUG_LOCATION, "ClientChannelControlHelper");
  }

  // Creates a new subchannel
  RefCountedPtr<SubchannelInterface> CreateSubchannel(
      const grpc_resolved_address& address, const ChannelArgs& per_address_args,
      const ChannelArgs& args) override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*client_channel_->work_serializer_) {
    if (client_channel_->resolver_ == nullptr) return nullptr;
    // Prepare subchannel args
    ChannelArgs subchannel_args = Subchannel::MakeSubchannelArgs(
        args, per_address_args, client_channel_->subchannel_pool_,
        client_channel_->default_authority_);

    // Create subchannel through factory
    RefCountedPtr<Subchannel> subchannel =
        client_channel_->client_channel_factory_->CreateSubchannel(
            address, subchannel_args);
    if (subchannel == nullptr) return nullptr;

    // Apply keepalive throttling
    subchannel->ThrottleKeepaliveTime(client_channel_->keepalive_time_);

    // Wrap subchannel in ClientChannel-specific wrapper
    return MakeRefCounted<SubchannelWrapper>(client_channel_,
                                             std::move(subchannel));
  }

  // Updates channel