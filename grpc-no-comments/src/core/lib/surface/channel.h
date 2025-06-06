
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_H
#define GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <map>
#include <optional>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/call_arena_allocator.h"
#include "src/core/call/call_destination.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/util/cpp_impl_of.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

struct grpc_channel_stack;

namespace grpc_core {

class Transport;

class Channel : public UnstartedCallDestination,
                public CppImplOf<Channel, grpc_channel> {
 public:
  struct RegisteredCall {
    Slice path;
    std::optional<Slice> authority;

    explicit RegisteredCall(const char* method_arg, const char* host_arg);
    RegisteredCall(const RegisteredCall& other);
    RegisteredCall& operator=(const RegisteredCall&) = delete;

    ~RegisteredCall();
  };

  virtual bool IsLame() const = 0;

  virtual grpc_call* CreateCall(grpc_call* parent_call,
                                uint32_t propagation_mask,
                                grpc_completion_queue* cq,
                                grpc_pollset_set* pollset_set_alternative,
                                Slice path, std::optional<Slice> authority,
                                Timestamp deadline, bool registered_method) = 0;

  virtual grpc_event_engine::experimental::EventEngine* event_engine()
      const = 0;

  virtual bool SupportsConnectivityWatcher() const = 0;

  virtual grpc_connectivity_state CheckConnectivityState(
      bool try_to_connect) = 0;

  virtual void WatchConnectivityState(
      grpc_connectivity_state last_observed_state, Timestamp deadline,
      grpc_completion_queue* cq, void* tag) = 0;

  virtual void AddConnectivityWatcher(
      grpc_connectivity_state initial_state,
      OrphanablePtr<AsyncConnectivityStateWatcherInterface> watcher) = 0;
  virtual void RemoveConnectivityWatcher(
      AsyncConnectivityStateWatcherInterface* watcher) = 0;

  virtual void GetInfo(const grpc_channel_info* channel_info) = 0;

  virtual void ResetConnectionBackoff() = 0;

  absl::string_view target() const { return target_; }
  channelz::ChannelNode* channelz_node() const { return channelz_node_.get(); }
  grpc_compression_options compression_options() const {
    return compression_options_;
  }

  RegisteredCall* RegisterCall(const char* method, const char* host);

  int TestOnlyRegisteredCalls() {
    MutexLock lock(&mu_);
    return registration_table_.size();
  }

  virtual void Ping(grpc_completion_queue* cq, void* tag) = 0;

  virtual grpc_channel_stack* channel_stack() const { return nullptr; }
  virtual bool is_client() const { return true; }
  virtual bool is_promising() const { return true; }

  CallArenaAllocator* call_arena_allocator() const {
    return call_arena_allocator_.get();
  }

 protected:
  Channel(std::string target, const ChannelArgs& channel_args);

 private:
  const std::string target_;
  const RefCountedPtr<channelz::ChannelNode> channelz_node_;
  const grpc_compression_options compression_options_;

  Mutex mu_;

  std::map<std::pair<std::string, std::string>, RegisteredCall>
      registration_table_ ABSL_GUARDED_BY(mu_);
  const RefCountedPtr<CallArenaAllocator> call_arena_allocator_;
};

}

inline void grpc_channel_destroy_internal(grpc_channel* channel) {
  grpc_core::Channel::FromC(channel)->Unref();
}

inline grpc_compression_options grpc_channel_compression_options(
    const grpc_channel* channel) {
  return grpc_core::Channel::FromC(channel)->compression_options();
}

inline grpc_core::channelz::ChannelNode* grpc_channel_get_channelz_node(
    grpc_channel* channel) {
  return grpc_core::Channel::FromC(channel)->channelz_node();
}

void grpc_channel_ping(grpc_channel* channel, grpc_completion_queue* cq,
                       void* tag, void* reserved);

#endif
