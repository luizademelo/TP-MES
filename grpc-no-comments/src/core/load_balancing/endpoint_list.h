
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_ENDPOINT_LIST_H
#define GRPC_SRC_CORE_LOAD_BALANCING_ENDPOINT_LIST_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "absl/functional/function_ref.h"
#include "absl/status/status.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

class EndpointList : public InternallyRefCounted<EndpointList> {
 public:

  class Endpoint : public InternallyRefCounted<Endpoint> {
   public:
    ~Endpoint() override { endpoint_list_.reset(DEBUG_LOCATION, "Endpoint"); }

    void Orphan() override;

    void ResetBackoffLocked();
    void ExitIdleLocked();

    std::optional<grpc_connectivity_state> connectivity_state() const {
      return connectivity_state_;
    }
    RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker() const {
      return picker_;
    }

   protected:

    explicit Endpoint(RefCountedPtr<EndpointList> endpoint_list)
        : endpoint_list_(std::move(endpoint_list)) {}

    absl::Status Init(const EndpointAddresses& addresses,
                      const ChannelArgs& args,
                      std::shared_ptr<WorkSerializer> work_serializer);

    template <typename T>
    T* endpoint_list() const {
      return DownCast<T*>(endpoint_list_.get());
    }

    template <typename T>
    T* policy() const {
      return endpoint_list_->policy<T>();
    }

    size_t Index() const;

   private:
    class Helper;

    virtual void OnStateUpdate(std::optional<grpc_connectivity_state> old_state,
                               grpc_connectivity_state new_state,
                               const absl::Status& status) = 0;

    virtual RefCountedPtr<SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const ChannelArgs& per_address_args, const ChannelArgs& args);

    RefCountedPtr<EndpointList> endpoint_list_;

    OrphanablePtr<LoadBalancingPolicy> child_policy_;
    std::optional<grpc_connectivity_state> connectivity_state_;
    RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker_;
  };

  ~EndpointList() override { policy_.reset(DEBUG_LOCATION, "EndpointList"); }

  void Orphan() override {
    endpoints_.clear();
    Unref();
  }

  size_t size() const { return endpoints_.size(); }

  const std::vector<OrphanablePtr<Endpoint>>& endpoints() const {
    return endpoints_;
  }

  void ResetBackoffLocked();

  void ReportTransientFailure(absl::Status status);

 protected:

  EndpointList(RefCountedPtr<LoadBalancingPolicy> policy,
               std::string resolution_note, const char* tracer)
      : policy_(std::move(policy)),
        resolution_note_(std::move(resolution_note)),
        tracer_(tracer) {}

  void Init(EndpointAddressesIterator* endpoints, const ChannelArgs& args,
            absl::FunctionRef<OrphanablePtr<Endpoint>(
                RefCountedPtr<EndpointList>, const EndpointAddresses&,
                const ChannelArgs&)>
                create_endpoint);

  template <typename T>
  T* policy() const {
    return DownCast<T*>(policy_.get());
  }

  bool AllEndpointsSeenInitialState() const {
    return num_endpoints_seen_initial_state_ == size();
  }

 private:

  virtual LoadBalancingPolicy::ChannelControlHelper* channel_control_helper()
      const = 0;

  RefCountedPtr<LoadBalancingPolicy> policy_;
  std::string resolution_note_;
  const char* tracer_;
  std::vector<OrphanablePtr<Endpoint>> endpoints_;
  size_t num_endpoints_seen_initial_state_ = 0;
};

}

#endif
