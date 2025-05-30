
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_H
#define GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice.h>
#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "absl/base/thread_annotations.h"
#include "absl/container/inlined_vector.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

/// Note: All methods with a "Locked" suffix must be called from the

class LoadBalancingPolicy : public InternallyRefCounted<LoadBalancingPolicy> {
 public:

  class CallState {
   public:
    CallState() = default;
    virtual ~CallState() = default;

    virtual void* Alloc(size_t size) = 0;
  };

  class MetadataInterface {
   public:
    virtual ~MetadataInterface() = default;

    virtual std::optional<absl::string_view> Lookup(
        absl::string_view key, std::string* buffer) const = 0;
  };

  class MetadataMutations {
   public:

    void Set(absl::string_view key, absl::string_view value) {
      Set(key, grpc_event_engine::experimental::Slice::FromCopiedString(value));
    }
    void Set(absl::string_view key,
             grpc_event_engine::experimental::Slice value) {
      metadata_.push_back({key, std::move(value)});
    }

   private:
    friend class MetadataMutationHandler;

    absl::InlinedVector<
        std::pair<absl::string_view, grpc_event_engine::experimental::Slice>, 3>
        metadata_;
  };

  struct PickArgs {

    absl::string_view path;

    MetadataInterface* initial_metadata;

    CallState* call_state;
  };

  class BackendMetricAccessor {
   public:
    virtual ~BackendMetricAccessor() = default;

    virtual const BackendMetricData* GetBackendMetricData() = 0;
  };

  class SubchannelCallTrackerInterface {
   public:
    virtual ~SubchannelCallTrackerInterface() = default;

    virtual void Start() = 0;

    struct FinishArgs {
      absl::string_view peer_address;
      absl::Status status;
      MetadataInterface* trailing_metadata;
      BackendMetricAccessor* backend_metric_accessor;
    };
    virtual void Finish(FinishArgs args) = 0;
  };

  struct PickResult {

    struct Complete {

      RefCountedPtr<SubchannelInterface> subchannel;

      std::unique_ptr<SubchannelCallTrackerInterface> subchannel_call_tracker;

      MetadataMutations metadata_mutations;

      grpc_event_engine::experimental::Slice authority_override;

      explicit Complete(
          RefCountedPtr<SubchannelInterface> sc,
          std::unique_ptr<SubchannelCallTrackerInterface> tracker = nullptr,
          MetadataMutations md = MetadataMutations(),
          grpc_event_engine::experimental::Slice authority =
              grpc_event_engine::experimental::Slice())
          : subchannel(std::move(sc)),
            subchannel_call_tracker(std::move(tracker)),
            metadata_mutations(std::move(md)),
            authority_override(std::move(authority)) {}
    };

    struct Queue {};

    struct Fail {
      absl::Status status;

      explicit Fail(absl::Status s) : status(s) {}
    };

    struct Drop {
      absl::Status status;

      explicit Drop(absl::Status s) : status(s) {}
    };

    std::variant<Complete, Queue, Fail, Drop> result = Queue();

    PickResult() = default;

    PickResult(Complete complete) : result(std::move(complete)) {}

    PickResult(Queue queue) : result(queue) {}

    PickResult(Fail fail) : result(std::move(fail)) {}

    PickResult(Drop drop) : result(std::move(drop)) {}
  };

  class SubchannelPicker : public DualRefCounted<SubchannelPicker> {
   public:
    SubchannelPicker();

    virtual PickResult Pick(PickArgs args) = 0;

   protected:
    void Orphaned() override {}
  };

  class ChannelControlHelper {
   public:
    ChannelControlHelper() = default;
    virtual ~ChannelControlHelper() = default;

    virtual RefCountedPtr<SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const ChannelArgs& per_address_args, const ChannelArgs& args) = 0;

    virtual void UpdateState(grpc_connectivity_state state,
                             const absl::Status& status,
                             RefCountedPtr<SubchannelPicker> picker) = 0;

    virtual void RequestReresolution() = 0;

    virtual absl::string_view GetTarget() = 0;

    virtual absl::string_view GetAuthority() = 0;

    virtual RefCountedPtr<grpc_channel_credentials> GetChannelCredentials() = 0;

    virtual RefCountedPtr<grpc_channel_credentials>
    GetUnsafeChannelCredentials() = 0;

    virtual grpc_event_engine::experimental::EventEngine* GetEventEngine() = 0;

    virtual GlobalStatsPluginRegistry::StatsPluginGroup&
    GetStatsPluginGroup() = 0;

    enum TraceSeverity { TRACE_INFO, TRACE_WARNING, TRACE_ERROR };
    virtual void AddTraceEvent(TraceSeverity severity,
                               absl::string_view message) = 0;
  };

  class DelegatingChannelControlHelper;

  template <typename ParentPolicy>
  class ParentOwningDelegatingChannelControlHelper;

  class Config : public RefCounted<Config> {
   public:
    ~Config() override = default;

    virtual absl::string_view name() const = 0;
  };

  struct UpdateArgs {

    absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> addresses;

    RefCountedPtr<Config> config;

    std::string resolution_note;

    ChannelArgs args;
  };

  struct Args {

    std::shared_ptr<WorkSerializer> work_serializer;

    /// Note: LB policies MUST NOT call any method on the helper from

    std::unique_ptr<ChannelControlHelper> channel_control_helper;

    ChannelArgs args;
  };

  explicit LoadBalancingPolicy(Args args, intptr_t initial_refcount = 1);
  ~LoadBalancingPolicy() override;

  LoadBalancingPolicy(const LoadBalancingPolicy&) = delete;
  LoadBalancingPolicy& operator=(const LoadBalancingPolicy&) = delete;

  virtual absl::string_view name() const = 0;

  virtual absl::Status UpdateLocked(UpdateArgs) = 0;

  virtual void ExitIdleLocked() {}

  virtual void ResetBackoffLocked() = 0;

  grpc_pollset_set* interested_parties() const { return interested_parties_; }

  // Note: This must be invoked while holding the work_serializer.
  void Orphan() override;

  class QueuePicker final : public SubchannelPicker {
   public:
    explicit QueuePicker(RefCountedPtr<LoadBalancingPolicy> parent)
        : parent_(std::move(parent)) {}

    ~QueuePicker() override { parent_.reset(DEBUG_LOCATION, "QueuePicker"); }

    PickResult Pick(PickArgs args) override;

   private:
    Mutex mu_;
    RefCountedPtr<LoadBalancingPolicy> parent_ ABSL_GUARDED_BY(&mu_);
  };

  class TransientFailurePicker final : public SubchannelPicker {
   public:
    explicit TransientFailurePicker(absl::Status status) : status_(status) {}

    PickResult Pick(PickArgs ) override {
      return PickResult::Fail(status_);
    }

   private:
    absl::Status status_;
  };

  class DropPicker final : public SubchannelPicker {
   public:
    explicit DropPicker(absl::Status status) : status_(status) {}

    PickResult Pick(PickArgs ) override {
      return PickResult::Drop(status_);
    }

   private:
    absl::Status status_;
  };

 protected:
  std::shared_ptr<WorkSerializer> work_serializer() const {
    return work_serializer_;
  }

  const ChannelArgs& channel_args() const { return channel_args_; }

  // Note: LB policies MUST NOT call any method on the helper from their

  ChannelControlHelper* channel_control_helper() const {
    return channel_control_helper_.get();
  }

  virtual void ShutdownLocked() = 0;

 private:

  std::shared_ptr<WorkSerializer> work_serializer_;

  grpc_pollset_set* interested_parties_;

  std::unique_ptr<ChannelControlHelper> channel_control_helper_;

  ChannelArgs channel_args_;
};

template <>
struct ArenaContextType<LoadBalancingPolicy::SubchannelCallTrackerInterface> {
  static void Destroy(LoadBalancingPolicy::SubchannelCallTrackerInterface*) {}
};

}

#endif
