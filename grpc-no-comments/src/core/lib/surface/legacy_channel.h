
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_LEGACY_CHANNEL_H
#define GRPC_SRC_CORE_LIB_SURFACE_LEGACY_CHANNEL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "src/core/call/call_arena_allocator.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"

namespace grpc_core {

class LegacyChannel final : public Channel {
 public:
  static absl::StatusOr<RefCountedPtr<Channel>> Create(
      std::string target, ChannelArgs args,
      grpc_channel_stack_type channel_stack_type);

  LegacyChannel(bool is_client, std::string target,
                const ChannelArgs& channel_args,
                RefCountedPtr<grpc_channel_stack> channel_stack);

  void Orphaned() override;

  bool IsLame() const override;

  grpc_call* CreateCall(grpc_call* parent_call, uint32_t propagation_mask,
                        grpc_completion_queue* cq,
                        grpc_pollset_set* pollset_set_alternative, Slice path,
                        std::optional<Slice> authority, Timestamp deadline,
                        bool registered_method) override;

  void StartCall(UnstartedCallHandler) override {
    Crash("StartCall() not supported on LegacyChannel");
  }

  grpc_event_engine::experimental::EventEngine* event_engine() const override {
    return channel_stack_->EventEngine();
  }

  bool SupportsConnectivityWatcher() const override;

  grpc_connectivity_state CheckConnectivityState(bool try_to_connect) override;

  void WatchConnectivityState(grpc_connectivity_state last_observed_state,
                              Timestamp deadline, grpc_completion_queue* cq,
                              void* tag) override;

  void AddConnectivityWatcher(
      grpc_connectivity_state initial_state,
      OrphanablePtr<AsyncConnectivityStateWatcherInterface> watcher) override;
  void RemoveConnectivityWatcher(
      AsyncConnectivityStateWatcherInterface* watcher) override;

  void GetInfo(const grpc_channel_info* channel_info) override;

  void ResetConnectionBackoff() override;

  void Ping(grpc_completion_queue* cq, void* tag) override;

  bool is_client() const override { return is_client_; }
  grpc_channel_stack* channel_stack() const override {
    return channel_stack_.get();
  }

 private:
  class StateWatcher;

  ClientChannelFilter* GetClientChannelFilter() const;

  const bool is_client_;
  RefCountedPtr<grpc_channel_stack> channel_stack_;
};

}

#endif
